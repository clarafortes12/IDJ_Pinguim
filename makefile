COMPILER = g++

SDL_INC_PATH = Include
SDL_PATH = sdl
SRC_PATH = src
CPP_PATH = libs
INC_PATH = include
OBJ_PATH = obj

FLAGS = -std=c++11 -Wall -pedantic -Wextra -Wno-unused-parameter -Werror=init-self

DFLAGS = -ggdb -O0 -DDEBUG

INC_PATHS = -I$(SDL_PATH)/$(SDL_INC_PATH) -I$(INC_PATH)

EXEC = jogo

LIBS = -L$(SDL_PATH)/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

MAIN = $(wildcard $(SRC_PATH)/*.cpp)

FILES = $(wildcard $(SRC_PATH)/$(CPP_PATH)/*.cpp)

EXECUTAVEL = $(EXEC).exe

all:
	$(COMPILER) $(FLAGS) $(INC_PATHS) -o $(EXEC) $(MAIN) $(FILES) $(LIBS)
debug:
	$(COMPILER) $(FLAGS) $(DFLAGS) $(INC_PATHS) -o $(EXEC) $(MAIN) $(FILES) $(LIBS)
run:
	.\$(EXECUTAVEL)