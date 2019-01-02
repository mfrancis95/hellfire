#include <limits.h>
#include <stdbool.h>
#ifdef TIMED
#include <stdio.h>
#include <time.h>
#endif
#include "renderer.h"

const unsigned palette[37] = {
    0x070707,
    0x1f0707,
    0x2F0F07,
    0x470F07,
    0x571707,
    0x671F07,
    0x771F07,
    0x8F2707,
    0x9F2F07,
    0xAF3F07,
    0xBF4707,
    0xC74707,
    0xDF4F07,
    0xDF5707,
    0xDF5707,
    0xD75F07,
    0xD75F07,
    0xD7670F,
    0xCF6F0F,
    0xCF770F,
    0xCF7F0F,
    0xCF8717,
    0xC78717,
    0xC78F17,
    0xC7971F,
    0xBF9F1F,
    0xBF9F1F,
    0xBFA727,
    0xBFA727,
    0xBFAF2F,
    0xB7AF2F,
    0xB7B72F,
    0xB7B737,
    0xCFCF6F,
    0xDFDF9F,
    0xEFEFC7,
    0xFFFFFF
};

SDL_Window *window;

int main(int argc, char *argv[]) {
    window = SDL_CreateWindow(
        "Hellfire", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960,
        SDL_WINDOW_OPENGL
    );
    initRenderer();
    unsigned long maxRenders = argc > 1 ? atol(argv[1]) : ULONG_MAX;
    unsigned long renders = 0;
    #ifdef TIMED
    unsigned long nanoseconds = 0;
    struct timespec start, end;
    #endif
    SDL_Event event;
    bool quit = false;
    while (!quit && renders < maxRenders) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            }
        }
        #ifdef TIMED
        clock_gettime(CLOCK_MONOTONIC, &start);
        #endif
        render();
        #ifdef TIMED
        clock_gettime(CLOCK_MONOTONIC, &end);
        if (start.tv_nsec < end.tv_nsec) {
            nanoseconds += end.tv_nsec - start.tv_nsec;
            renders++;
        }
        #else
        renders++;
        #endif
        SDL_Delay(16);
    }
    cleanupRenderer();
    SDL_DestroyWindow(window);
    SDL_Quit();
    #ifdef TIMED
    printf("%lu\n", nanoseconds / renders / 1000000);
    #endif
    return 0;
}