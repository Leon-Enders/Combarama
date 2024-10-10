#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_pen.h>
#include <iostream>

int main(int argc, char* argv[])
{

    
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }


    SDL_Window* window = SDL_CreateWindow("Comborama",1280,720,0);

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }


    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


 
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); 
    SDL_RenderClear(renderer);

   
    SDL_FRect rect;
    rect.x = 200;
    rect.y = -150;
    rect.w = 50;
    rect.h = 50;

  


    bool running = true;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
           
            SDL_RenderPresent(renderer);


            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
            SDL_RenderClear(renderer);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}