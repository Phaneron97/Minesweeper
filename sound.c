#include "sound.h"

void init_sound() {
	// start SDL with audio support
	if(SDL_Init(SDL_INIT_AUDIO)==-1) {
		printf("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}
	// open 44.1KHz, signed 16bit, system byte order,
	//      stereo audio, using 1024 byte chunks
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}
	Mix_Volume(1,MIX_MAX_VOLUME/2); // sets volume
	Mix_AllocateChannels(64); // allows more sounds to be played at once

	biem = Mix_LoadWAV("sfx/biem.wav");
	if(!biem) {
		printf("Mix_LoadWAV: %s\n", Mix_GetError());
		// handle error
	}

    won = Mix_LoadWAV("sfx/won.wav");
	if(!won) {
		printf("Mix_LoadWAV: %s\n", Mix_GetError());
		// handle error
	}
}

void play_sound(Mix_Chunk *beautifulSound) {
    if (Mix_PlayChannel(-1, beautifulSound, 0) == -1)
    {
        printf("Mix_PlayChannel: %s\n", Mix_GetError());
    }
}