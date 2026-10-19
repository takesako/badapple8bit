#include <stdio.h>
#include <sys/time.h>
#include <sys/select.h>
#include <unistd.h>
#include "lib_pav.h"

double now(void) {
    struct timeval t; gettimeofday(&t,NULL);
    return t.tv_sec+t.tv_usec/1000000.0;
}

void vsync(double t) {
    double s=t-now();
    if(s<=0)return;
    struct timeval v={(long)s,(long)((s-(long)s)*1000000)};
    select(0,NULL,NULL,NULL,&v);
}

void sound(const char *file) {
    if(fork()==0) { execlp("afplay","afplay",file,NULL); _exit(1); }
}

void draw(PavDecoder *d) {
    int x,y,a,b,fg=-1,bg=-1;
    printf("\033[H");
    for(y=0;y<d->height;y+=2) {
        for(x=0;x<d->width;x++) {
            a=d->pixel[y*d->width+x];
            b=d->pixel[(y+(y+1<d->height))*d->width+x];
            if(a!=fg) {
                unsigned char *p=d->palette[a];
                printf("\033[38;2;%u;%u;%um",p[0],p[1],p[2]); fg=a;
            }
            if(b!=bg) {
                unsigned char *p=d->palette[b];
                printf("\033[48;2;%u;%u;%um",p[0],p[1],p[2]); bg=b;
            }
            printf("▀");
        }
        printf("\033[0m\n"); fg=bg=-1;
    }
    fflush(stdout);
}

int main(int argc,char **argv) {
    PavDecoder *d; double start; int r;
    static char buf[1024*1024];
    if(argc<2||argc>3) {
        printf("Usage: %s video.pav [sound.wav]\n",argv[0]);
        return 1;
    }
    d=pav_decoder_open(argv[1]);
    if(!d||pav_decoder_next(d)!=1)return 1;
    setvbuf(stdout,buf,_IOFBF,sizeof(buf));
    printf("\033[?1049h\033[?25l\033[?7l\033[2J");
    start=now();
    if(argc==3)sound(argv[2]);
    do {
        vsync(start+(double)(d->frame_index-1)/d->fps);
        draw(d);
    } while((r=pav_decoder_next(d))==1);
    printf("\033[0m\033[?7h\033[?25h\033[?1049l");
    pav_decoder_close(d);
    return r<0;
}
