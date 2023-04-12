COMPILER = g++

INC_PATH = Include
SDL_PATH = sdl
SRC_PATH = src
CPP_PATH = cpp

FLAGS = -Wall -g -I$(SDL_PATH)/$(INC_PATH) -L$(SDL_PATH)/lib

EXEC = jogo

LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

MAIN = $(wildcard $(SRC_PATH)/*.cpp)

FILES = $(wildcard $(SRC_PATH)/$(CPP_PATH)/*.cpp)

EXECUTAVEL = $(EXEC).exe

all:
	$(COMPILER) $(FLAGS) -o $(EXEC) $(MAIN) $(FILES) $(LIBS)

run:
	.\$(EXECUTAVEL)

clean:
	del /q $(EXECUTAVEL)