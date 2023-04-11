#include <stdio.h>
#include "Game.h"

#include <string.h>
#include <iostream.h>

using namespace std;

int main(int argc, char** argv){
    static Game& game = Game::GetInstance();
    game.Run();
    return 0;
}