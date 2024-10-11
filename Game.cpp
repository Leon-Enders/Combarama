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
		DeltaTime = SDL_GetTicks() - FrameStart;
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

	const bool* keyStates = SDL_GetKeyboardState(NULL);

	UpdateDirection(0, 0);
	
	if (keyStates[SDL_SCANCODE_W]) {
		UpdateDirection(0, -1);
	}
	if (keyStates[SDL_SCANCODE_A]) {
		UpdateDirection(-1, 0);
	}
	if (keyStates[SDL_SCANCODE_S]) {
		UpdateDirection(0, 1);
	}
	if (keyStates[SDL_SCANCODE_D]) {
		UpdateDirection(1, 0);
	}
	
}

void Game::Update()
{
	UpdatePlayer();
}

void Game::Render()
{
	ComposeFrame();
	DrawFrame();
}

void Game::ComposeFrame()
{
	SDL_SetRenderDrawColor(GameRenderer, 0, 0, 0, 0);
	SDL_RenderClear(GameRenderer);
}

void Game::DrawFrame()
{

	SDL_SetRenderDrawColor(GameRenderer, 0, 143, 190, 255);
	SDL_RenderFillRect(GameRenderer, Player.get());
	SDL_RenderPresent(GameRenderer);

}

void Game::SpawnPlayer()
{
	SDL_SetRenderDrawColor(GameRenderer, 0, 143, 190, 255);
	const SDL_FRect PlayerRect = { 255, 255, 64, 64 };
	
	Player = std::make_unique<SDL_FRect>(PlayerRect);

}

void Game::UpdateDirection(int xDir, int yDir)
{
	xCDir = xDir;
	yCDir = yDir;
}

void Game::UpdatePlayer()
{
	xVel = xCDir * DeltaTime * Speed;
	yVel = yCDir * DeltaTime * Speed;


	Player->x += xVel;
	Player->y += yVel;
}
