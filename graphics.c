#include "common.h"
#include "graphics.h"

SDL_Texture *load_texture(char *filename)
{
	SDL_Texture *txtr;
	txtr = IMG_LoadTexture(renderer, filename);
	return txtr;
}

// load texture from texture array and get path and save in totalPath
void init_textures(char *path, char *file_prefix, int num_txtrs, SDL_Texture **txtr_set) {
	for (int i = 0; i < num_txtrs; i++) {
		char totalPath[100]; 
		sprintf(totalPath, "%s/%s%d.png", path, file_prefix, i);
        printf("%s loaded\n", totalPath);
		txtr_set[i] = load_texture(totalPath);
	}
}

// draw a texture for bombs, numbers, flags
void blit(SDL_Texture *txtr, int x, int y, int center)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(txtr, NULL, NULL, &dest.w, &dest.h);
	// If center != 0, render texture with its center on (x,y), NOT
	// with its top-left corner...
	if (center)
	{
		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;
	}
	SDL_RenderCopy(renderer, txtr, NULL, &dest);
}

// draw all flags on the field
void drawFlags(int x, int y, board *board)
{
    if (board->isFlag[x][y] == FLAGGED)
    {
        blit(board->txtr_flag[0], x * BLOCK_SIZE, y * BLOCK_SIZE, 0);
    }
}

// draw all bombs on the field (show only when player loses)
void drawBombs(int x, int y, board *board)
{
    if (board->isBomb[x][y] == BOMBED && board->isFlag[x][y] != FLAGGED)
    {
        blit(board->txtr_bomb[0], x * BLOCK_SIZE, y * BLOCK_SIZE, 0);
    }
}

// draw all numbers around bombs
void drawNumbers(int x, int y, board *board)
{
    if (board->isRevealed[x][y] == REVEALED && board->isBomb[x][y] != BOMBED && board->isNumbered[x][y] > 0)
    {	
		SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255); // grid color
        blit(board->txtr_numbers[board->isNumbered[x][y]], x * BLOCK_SIZE, y * BLOCK_SIZE, 0);
    }
	else if (board->isRevealed[x][y] == REVEALED && board->isBomb[x][y] != BOMBED && board->isNumbered[x][y] == 0) {
		SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255); // grid color
	}
}

// text drawing for displaying bombs in text with font Orbitron
void drawBombScore(board *board) {
        char str[20];																// string with 20 characters
        sprintf(str, "BOMBS: %d/%d", board->flags, BOMB_AMOUNT);					// put multiple variables in 1 string to show on screen

        TTF_Font *font = TTF_OpenFont("Orbitron.ttf", 32);							// load orbitron as font
        SDL_Color color = {230, 25, 25, 255};										// set font-color
        SDL_Surface *textSurf = TTF_RenderText_Solid(font, str, color);				// save font and color in SDL_Surface
        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurf);// save SDL_surface as a texture

		// draw rectangle on specific place on screen and size
        SDL_Rect textRect = {(SCREEN_WIDTH/2-15), (SCREEN_HEIGHT-50), textSurf->w, textSurf->h}; 
        SDL_RenderDrawRect(renderer, &textRect);									// render rectangle
        SDL_FreeSurface(textSurf);													// remove SDL_surface to free up memory space	

        TTF_CloseFont(font);         												// remove chosen font to free up memory space
	
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);						// copy settings into new object (each new frame)
}

// text drawing for displaying copyright for the memes
void drawCopyright(char text[50], int fontSize, unsigned char red, unsigned char green, unsigned char blue) {
	TTF_Font *font = TTF_OpenFont("Orbitron.ttf", fontSize); 						// load orbitron as font
	SDL_Color color = {red, green, blue, 255};										// set font-color
	SDL_Surface *textSurf = TTF_RenderText_Solid(font, text, color);				// save font and color in SDL_Surface
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurf);	// save SDL_surface as a texture

	SDL_Rect textRect = {10, (SCREEN_HEIGHT-50), textSurf->w, textSurf->h};			// draw rectangle on specific place on screen and size
	SDL_RenderDrawRect(renderer, &textRect);										// render rectangle
	SDL_FreeSurface(textSurf);														// remove SDL_surface to free up memory space											

	TTF_CloseFont(font);         													// remove chosen font to free up memory space

	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);							// copy settings into new object (each new frame)
}