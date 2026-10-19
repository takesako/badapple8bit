#include "fami_mml.h"
int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input.mml output.wav\n", argv[0]);
        return 1;
    }
    mml_file2wav(argv[1], argv[2]);
    return 0;
}
