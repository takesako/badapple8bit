#include "lib_pav.h"

int main(int argc, char **argv) {
    if (argc != 7) {
        fprintf(stderr, "Usage: %s sheet.png video.pav W H COLORS FPS\n", argv[0]);
        return 1;
    }
    if (!pav_encode_png(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]),
                        atoi(argv[5]), atoi(argv[6]))) {
        fprintf(stderr, "PAV encode failed\n");
        return 1;
    }
    return 0;
}
