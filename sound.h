#ifndef SOUND_H
#define SOUND_H

    #include "common.h"

    Mix_Chunk *biem;
    Mix_Chunk *won;

    void init_sound();
    void play_sound(Mix_Chunk *beautifulSound);

#endif // !SOUND_H
