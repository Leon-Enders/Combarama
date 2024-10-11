#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>
#include <iostream>
#include "Game.h"
#include "CombaramaStructs.h"


int main(int argc, char* argv[])
{

    if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }


    SDL_Window* Window = SDL_CreateWindow("Comborama",1280,720,0);

    if (!Window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* Renderer = SDL_CreateRenderer(Window, "GameRenderer");

    if (!Renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }



    App GameApp;
    GameApp.Window = Window;
    GameApp.Renderer = Renderer;


    Game NewGame = Game(GameApp);
    NewGame.StartGame();


    SDL_DestroyWindow(Window);
    SDL_Quit();

    return 0;
}