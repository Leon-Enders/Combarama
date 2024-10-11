#pragma once
#include <SDL3/SDL.h>


class Game
{
public:
	Game(SDL_Window* Window);
	


	void StartGame();

	void HandleGameLoop();

	void ProcessInput();
	void Update();
	void Render();



private:

	SDL_Window* GameWindow = nullptr;
	SDL_Event Event = SDL_Event();

	bool IsGameActive = false;
};