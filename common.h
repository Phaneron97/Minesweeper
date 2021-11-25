#ifndef COMMON_H
#define COMMON_H

    #include <stdio.h>
    #include <SDL2/SDL.h> // SDL lib
    #include <SDL2/SDL_image.h> // for IMG_Init and IMG_LoadTexture
    #include <SDL2/SDL_mixer.h> // sound
    #include <SDL2/SDL_ttf.h> // fonts
    #include <math.h> // for atan() function
    #include <time.h> // for srand() function

    #define BLOCK_SIZE          32 // size in pixels

    #define AMOUNT_BLOCK_WIDTH  16 // blocks on X
    #define AMOUNT_BLOCK_HEIGHT 16 // block on Y
    #define BOMB_AMOUNT         30 // amount of bombs

    #define SCREEN_WIDTH		(BLOCK_SIZE * AMOUNT_BLOCK_WIDTH) // calc screenwidth in pixels
    #define SCREEN_HEIGHT		(50 + BLOCK_SIZE * AMOUNT_BLOCK_HEIGHT) // calc screenheight in pixels

    typedef struct _mouse_ {
        int x;
        int y;
    } mouse;

    typedef enum _boxState_ {        
        REVEALED = 1,
        NOTREVEALED = 0,
    } boxState;

    typedef enum _bombState_ {
        BOMBED = 1,
        NOTBOMBED = 0,        
    } bombState;

    typedef enum _flagState_ {
        FLAGGED = 1,
        NOTFLAGGED = 0,
    } flagState;

    typedef struct _board_ {
        int bombs;
        int flags;
        int generated;
        boxState isRevealed[AMOUNT_BLOCK_WIDTH][AMOUNT_BLOCK_HEIGHT];
        bombState isBomb[AMOUNT_BLOCK_WIDTH][AMOUNT_BLOCK_HEIGHT];
        flagState isFlag[AMOUNT_BLOCK_WIDTH][AMOUNT_BLOCK_HEIGHT];    
        int isNumbered[AMOUNT_BLOCK_WIDTH][AMOUNT_BLOCK_HEIGHT];    
        SDL_Texture *txtr_flag[1];
        SDL_Texture *txtr_bomb[1];
        SDL_Texture *txtr_numbers[8];
        int lose;
        int win;
        int revealed;
    } board;

#endif // !COMMON_H