#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    // Inicializar SDL (video subsystem)
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    // Inicializar SDL2_image solo con soporte PNG
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("IMG_Init Error: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // Crear ventana
    SDL_Window *window = SDL_CreateWindow(
        "My First SDL2 Window",   // título
        SDL_WINDOWPOS_CENTERED,   // posición X
        SDL_WINDOWPOS_CENTERED,   // posición Y
        800,                      // ancho
        600,                      // alto
        SDL_WINDOW_SHOWN          // flags (visible)
    );

    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Crear renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    // Cargar el PNG como textura
    SDL_Surface *surface = IMG_Load("character.png");  // tu archivo PNG
    if (!surface) {
        printf("IMG_Load Error: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);  // ya no necesitamos el surface

    if (!texture) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    
    // Bucle de eventos (para que no se cierre inmediatamente)
    int pos_x = 100;
    int pos_y = 100;
    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN) {  // tecla presionada
                if (event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_ESCAPE) running = 0;
                if (event.key.keysym.sym == SDLK_a) pos_x -= 5;
                if (event.key.keysym.sym == SDLK_d) pos_x += 5;
                if (event.key.keysym.sym == SDLK_w) pos_y -= 5;
                if (event.key.keysym.sym == SDLK_s) pos_y += 5;
            } 
        }
        SDL_Delay(16); // ~60 FPS idle

        // Limpia la pantalla con color negro
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Definir un rectángulo (x, y, w, h)
        SDL_Rect square1 = { pos_x, pos_y, 100, 100 };
        SDL_Rect square2 = { pos_x + 50, pos_y + 50, 100, 100 };

        // Establecer color blanco
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // Dibujar cuadrado relleno
        SDL_RenderFillRect(renderer, &square1);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // azul
        SDL_RenderFillRect(renderer, &square2);

        // Dibujar textura
        SDL_Rect character = { 100, 100, 300, 300 };
        SDL_RenderCopy(renderer, texture, NULL, &character);

        // Mostrar en pantalla
        SDL_RenderPresent(renderer);
    }

    // Liberar recursos
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

/*

install libsdl2-dev
install libsdl2-ttf-dev
install libsdl2-image-dev

gcc main.c -lSDL2
gcc main.c -lSDL2 -lSDL2_image 

*/