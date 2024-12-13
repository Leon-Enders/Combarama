#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Core/CombaramaConstants.h"
#include "Core/CoreMinimal.h"
#include "Game.h"
#include "Utility/CombaramaStructs.h"





int main(int argc, char* argv[])
{

    if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize Error: %s", SDL_GetError());
        return 1;
    }


    SDL_Window* Window = SDL_CreateWindow("Comborama",Combarama::ViewportWidth,Combarama::ViewportHeight,0);

    if (!Window) {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* Renderer = SDL_CreateRenderer(Window, NULL);
    
    if (!Renderer)
    {
        SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    App GameApp;
    GameApp.Window = Window;
    GameApp.Renderer = Renderer;
    
    
    Game InstancedGame = Game(GameApp);
    AGame = &InstancedGame;

    InstancedGame.Initialize();
    InstancedGame.StartGame();

    SDL_DestroyWindow(Window);
    SDL_Quit();

    return 0;
}