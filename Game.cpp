#include "Game.h"
#include <iostream>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_log.h>



Game::Game(App& GameApp)
	:
	GameWindow(GameApp.Window),
	GameRenderer(GameApp.Renderer)
{

	

}

void Game::StartGame()
{
	IsGameActive = true;

	SpawnPlayer();

	while (IsGameActive)
	{
		FrameStart = SDL_GetTicks();

		HandleGameLoop();

		FrameTime = SDL_GetTicks() - FrameStart;

		if (FrameDelay > FrameTime)
		{
			SDL_Delay(FrameDelay - FrameTime);
		}
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
	ComposeFrame();
	DrawFrame();
}

void Game::ComposeFrame()
{
	
}

void Game::DrawFrame()
{

	SDL_RenderFillRect(GameRenderer, &*Player.get());
	SDL_RenderPresent(GameRenderer);

}

void Game::SpawnPlayer()
{
	SDL_SetRenderDrawColor(GameRenderer, 0, 143, 190, 255);
	const SDL_FRect PlayerRect = { 255, 255, 64, 64 };
	
	Player = std::make_unique<SDL_FRect>(PlayerRect);

}
