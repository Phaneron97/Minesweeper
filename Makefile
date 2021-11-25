.PHONY: all build clean # files with this name are ignored

CC 			= gcc # compiler
TARGET		= main # output executable
cflags 		= -std=c99 -Wall -Wextra -Wconversion -Wpedantic # flags
sdlFlag 	= `sdl2-config --cflags --libs` -lSDL2_image -lm -lSDL2_mixer -lSDL2_ttf # libraries
SOURCES 	= main.c graphics.c logic.c sound.c # files 
OBJS 		= $(SOURCES:.c=.o)

build: all

all: $(OBJS) # when 'make' 'make all' is typed
	$(CC) $(cflags) $(SOURCES) -o $(TARGET) $(sdlFlag)

clean: # when 'make clean' is typed delete all .o files
	rm *.o