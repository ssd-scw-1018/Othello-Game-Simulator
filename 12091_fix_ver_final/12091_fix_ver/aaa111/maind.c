#include "all_var.h"

int main() {

    init_initall();

    while (!quit) {

        show_timer();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                bottondown();
            }
            else if (event.type == SDL_MOUSEMOTION) {
                bottonmove();
            }
        }
        renderimage();
    }
    closeall();
    return 0;
}