#pragma once
#include <SDL3/SDL.h>
#include "CombaramaStructs.h"




class Game
{
public:
	Game(App& GameApp);



	void StartGame();

	void HandleGameLoop();

	void ProcessInput();
	void Update();
	void Render();



private:

	SDL_Window* GameWindow = nullptr;
	SDL_Renderer* GameRenderer = nullptr;


	SDL_Event Event = SDL_Event();

	bool IsGameActive = false;



	Uint64 FrameStart = 0;
	int FrameTime = 0;

	static constexpr int FPS = 60;
	static constexpr int FrameDelay = 1000 / FPS;
};