COMPILER = g++

INC_PATH = Include
SDL_PATH = sdl
SRC_PATH = src

FLAGS = -Wall -g -I$(SDL_PATH)/$(INC_PATH) -L$(SDL_PATH)/lib

EXEC = jogo

LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

FILES = $(wildcard $(SRC_PATH)/*.cpp)

EXECUTAVEL = $(EXEC).exe

all:
	$(COMPILER) $(FLAGS) -o $(EXEC) $(FILES) $(LIBS)

run:
	.\$(EXECUTAVEL)

clean:
	del /q $(EXECUTAVEL)