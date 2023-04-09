#include <stdio.h>
#include "Game.h"

int main(int argc, char** argv){
    static Game& game = Game::GetInstance();
    game.Run();
    return 0;
}