#ifndef GRAPHICS_H
#define GRAPHICS_H

    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Texture *load_texture(char *filename);

    void sound();
    void init_textures(char *path, char *file_prefix, int num_txtrs, SDL_Texture **txtr_set);
    void blit(SDL_Texture *txtr, int x, int y, int center);
    void drawFlags(int x, int y, board *board);
    void drawBombs(int x, int y, board *board);
    void drawNumbers(int x, int y, board *board);
    void drawBombScore(board *board);
    void drawCopyright(char text[50], int fontSize, unsigned char red, unsigned char green, unsigned char blue);

#endif // !GRAPHICS_H