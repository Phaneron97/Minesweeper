#include "logic.h"
#include "sound.h"

void game_init(board *b)
{
    IMG_Init(IMG_INIT_PNG);                                      // load textures
    init_textures("gfx", "flag", 1, b->txtr_flag);               // flag texture
    init_textures("gfx", "bomb", 1, b->txtr_bomb);               // bomb texture
    init_textures("gfx/numbers", "number_", 9, b->txtr_numbers); // number textures
    init_sound();                                                // load sound
    TTF_Init();                                                  // load font
}

void generateBoard(board *board)
{
    // set amount of bombs and flags
    board->bombs = BOMB_AMOUNT;
    board->flags = BOMB_AMOUNT;
    printf("Board generated!\n");
    srand((unsigned)time(NULL));

    // generate bombs on random locations in field
    while (board->bombs > 0)
    {
        int randX = rand() % AMOUNT_BLOCK_WIDTH;
        int randY = rand() % AMOUNT_BLOCK_HEIGHT;

        if (board->isBomb[randX][randY] == NOTBOMBED && board->isRevealed[randX][randY] != REVEALED)
        {
            // place bomb, reduce amount of bombs to generate by 1
            board->isBomb[randX][randY] = BOMBED;
            board->bombs--;

            // count bombs in adjacent blocks
            checkOutOfBounds(randX, randY, board);
        }
    }
    printf("%d bombs placed!\n", BOMB_AMOUNT);
    board->bombs = BOMB_AMOUNT;
}

void checkOutOfBounds(int x, int y, board *board)
{
    // Check all blocks around the generated block is out of bounds (out of array)
    addCheckOutOfBounds(x, y - 1, board);     // North
    addCheckOutOfBounds(x, y + 1, board);     // South
    addCheckOutOfBounds(x + 1, y, board);     // West
    addCheckOutOfBounds(x - 1, y, board);     // East
    addCheckOutOfBounds(x - 1, y - 1, board); // North-East
    addCheckOutOfBounds(x - 1, y + 1, board); // North-West
    addCheckOutOfBounds(x + 1, y - 1, board); // South-East
    addCheckOutOfBounds(x + 1, y + 1, board); // South-West
}

void addCheckOutOfBounds(int x, int y, board *board)
{
    // Check if the checked block is out of bounds. If so, stop generating
    if ((x < 0) || (y < 0))
        return;
    if ((x >= AMOUNT_BLOCK_WIDTH) || (y >= AMOUNT_BLOCK_HEIGHT))
        return;
    board->isNumbered[x][y]++;
}

void reveal(int x, int y, board *board) // Flood fill algorithm (sort of)
{
    if ((x < 0) || (y < 0)) // if x or y is out of array then return
        return;
    if ((x >= AMOUNT_BLOCK_WIDTH) || (y >= AMOUNT_BLOCK_HEIGHT)) // if x or y is out of array then return
        return;
    if (board->isRevealed[x][y] != REVEALED && board->isBomb[x][y] != BOMBED)
    {
        board->isRevealed[x][y] = REVEALED; // reveal clicked block

        // Check if board is generated
        if (board->generated != 1)
        {
            generateBoard(board);
            board->generated = 1;
        }

        if (board->isNumbered[x][y] == 0)
        {
            // reveal blocks around clicked block ONLY IF requirements are met
            reveal(x, y - 1, board);
            reveal(x, y + 1, board);
            reveal(x + 1, y, board);
            reveal(x - 1, y, board);
            reveal(x - 1, y - 1, board);
            reveal(x - 1, y + 1, board);
            reveal(x + 1, y - 1, board);
            reveal(x + 1, y + 1, board);
        }
    }
    board->isRevealed[x][y] = REVEALED;
}

void process_input(mouse *m, board *board)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (board->lose != 1 && board->win != 1)
        {
            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    // Calculate clicked field
                    m->x = event.button.x / BLOCK_SIZE;
                    m->y = event.button.y / BLOCK_SIZE;

                    // Revealing flagged field is impossible
                    if (board->isFlag[m->x][m->y] == FLAGGED)
                        return;

                    // Reveal clicked location regardless of current state
                    reveal(m->x, m->y, board);

                    // If clicked field is bombed, user is now dead (rip)
                    if (board->isBomb[m->x][m->y] == BOMBED)
                    {
                        printf("Boom!\n");
                        play_sound(biem);
                        board->lose = 1;
                    }

                    // If field is !bombed, printf state
                    else
                    {
                        printf("revealed x%d y%d\n", m->x, m->y);
                    }
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    // Calculate click location
                    m->x = event.button.x / BLOCK_SIZE;
                    m->y = event.button.y / BLOCK_SIZE;

                    // Place flag on unrevealed and unflagged block
                    if (board->bombs > 0 && board->isRevealed[m->x][m->y] != REVEALED && board->flags > 0 && board->isFlag[m->x][m->y] != FLAGGED)
                    {
                        // Mark field as flagged when a flag is placed and flags minus 1
                        printf("flagged x%d y%d\n", m->x, m->y);
                        board->isFlag[m->x][m->y] = FLAGGED;
                        board->flags--;

                        // If field is bombed and flagged then bombs minus 1 
                        if (board->isFlag[m->x][m->y] == FLAGGED && board->isBomb[m->x][m->y] == BOMBED)
                        {
                            board->bombs--;
                            if (board->bombs <= 0)
                            {
                                printf("You won!\n");
                                play_sound(won);
                                board->win = 1;
                            }
                        }
                    }

                    // Remove flag on flagged block
                    else if (board->isFlag[m->x][m->y] == FLAGGED && board->bombs > 0 && board->isRevealed[m->x][m->y] != REVEALED)
                    {
                        printf("removed flag x%d y%d\n", m->x, m->y);
                        // If flag is removed from bombed block then bombs++
                        if (board->isBomb[m->x][m->y] == BOMBED)
                        {
                            board->bombs++;
                        }
                        // status flag is removed from clicked block, +1 flags
                        board->isFlag[m->x][m->y]--;
                        board->flags++;
                    }
                }
                break;
            default:
                break;
            }
        }
        switch (event.type)
        {
        case SDL_QUIT:
            proper_shutdown();
            exit(0);
            printf("shutting down\n");
            break;
        default:
            break;
        }
    }
}

void proper_shutdown(void)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit(); // Quit fonts
    SDL_Quit(); 
}