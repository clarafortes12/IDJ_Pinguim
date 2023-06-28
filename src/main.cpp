#include <stdio.h>
#include "Game.h"
#include "TitleState.h"

#include <string.h>
#include <iostream.h>

using namespace std;

int main(int argc, char** argv){
    Game& game = Game::GetInstance();
    TitleState* state = new TitleState();
    game.Push(state);
    game.Run();

    return 0;
}