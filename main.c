#include "common.h"
#include "graphics.h"
#include "logic.h"
#include "sound.h"

mouse m = {
    .x = 0, 
    .y = 0
};

board b = {
    .bombs = 0,
    .flags = 0,
    .isBomb = {{0}},
    .isFlag = {{0}},
    .isRevealed = {{0}},
    .txtr_bomb = {0},
    .txtr_flag = {0},
    .txtr_numbers = {0},
    .win = 0,
    .lose = 0,
    .revealed = 0,
    .generated = 0
};

int main() { 
    unsigned int window_flags = 0;
    unsigned int renderer_flags = SDL_RENDERER_ACCELERATED;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

    window = SDL_CreateWindow("Minesweeper", 
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, 
    SCREEN_HEIGHT, window_flags);
    if (window == NULL)
	{
		printf("Failed to create window -- Error: %s\n",
			SDL_GetError());
		exit(1);
	}

    renderer = SDL_CreateRenderer(window, -1, renderer_flags);
    if (renderer == NULL)
	{
		printf("Failed to create renderer -- Error: %s\n",
			SDL_GetError());
		exit(1);   
    }     
    
    game_init(&b); // Load textures, sounds, text

    // main game
    while(1) {
        SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255); // Background color
        SDL_RenderClear(renderer);
        process_input(&m, &b);  

        drawBombScore(&b);
        drawCopyright("Made by: Christian Wanschers", 10, 50, 50, 50);

        for (int x = 0; x < AMOUNT_BLOCK_WIDTH; x++) {
            for (int y = 0; y < AMOUNT_BLOCK_HEIGHT; y++) {
                SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // Grid color
                
                // draw numbers, flags and bombs on screen in fields
                drawNumbers(x, y, &b);
                drawFlags(x, y, &b); 
                if (b.lose == 1) {
                    drawBombs(x, y, &b);
                }

                SDL_Rect vakje = {x*BLOCK_SIZE, y*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE}; // SDL array
                SDL_RenderDrawRect(renderer, &vakje); // draw SDL array
            }
        }

        SDL_RenderPresent(renderer);
		SDL_Delay(16); // Pause for 16 ms results in 60 fps (1000 / 16 = 60)
    }

    return 0;
}

