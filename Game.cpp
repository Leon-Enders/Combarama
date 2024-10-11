#include "Game.h"
#include <iostream>
#include <SDL3/SDL_timer.h>

Game::Game(SDL_Window* Window)
	:
	GameWindow(Window)
{

	

}

void Game::StartGame()
{
	IsGameActive = true;

	while (IsGameActive)
	{
		HandleGameLoop();
	}
	
}

void Game::HandleGameLoop()
{
	ProcessInput();
	Update();
	Render();
}

void Game::ProcessInput()
{
	while (SDL_PollEvent(&Event))
	{
		if (Event.type == SDL_EVENT_QUIT)
		{
			IsGameActive = false;
		}
	}
}

void Game::Update()
{
	SDL_Log("Update!");
}

void Game::Render()
{
	SDL_Log("Render!");
}
