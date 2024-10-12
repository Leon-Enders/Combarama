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

	Player = std::make_unique<Actor>(Vector2(255.f, 255.f));



	while (IsGameActive)
	{
		DeltaTime = static_cast<float>(SDL_GetTicks() - FrameStart);
		FrameStart = SDL_GetTicks();

		HandleGameLoop();

		FrameTime = SDL_GetTicks() - FrameStart;

		if (FrameDelay > FrameTime)
		{
			SDL_Delay(FrameDelay - static_cast<Uint32>(FrameTime));
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
	SDL_Event Event;
	while (SDL_PollEvent(&Event))
	{
		if (Event.type == SDL_EVENT_QUIT)
		{
			IsGameActive = false;
		}
		if (Event.type == SDL_EVENT_KEY_DOWN)
		{
			if (Event.key.key == SDLK_SPACE)
			{
				SpawnActor();
			}
		}
	}

	const bool* keyStates = SDL_GetKeyboardState(NULL);

	Vector2 NextVelocity = { 0,0 };
	
	if (keyStates[SDL_SCANCODE_W]) {
		NextVelocity.Y = -1;
	}
	if (keyStates[SDL_SCANCODE_S]) {
		NextVelocity.Y = 1;
	}
	if (keyStates[SDL_SCANCODE_A]) {
		NextVelocity.X = -1;
	}
	if (keyStates[SDL_SCANCODE_D]) {
		NextVelocity.X = 1;
	}
	


	Player->UpdateVelocity(NextVelocity.Normalize());
}

void Game::Update()
{
	Player->Update(DeltaTime);
}

void Game::Render()
{
	ComposeFrame();
	RenderFrame();
}

void Game::ComposeFrame()
{
	// Clear BackBuffer
	SDL_SetRenderDrawColor(GameRenderer, 0, 0, 0, 255);
	SDL_RenderClear(GameRenderer);

	// Draw Player
	Player->Draw(GameRenderer);

	// Draw all Spawned Actors
	//for (const auto& SpawnedActor : Actors)
	//{
	//	SpawnedActor->Draw(GameRenderer);
	//}
}

void Game::RenderFrame()
{
	SDL_RenderPresent(GameRenderer);
}

void Game::SpawnActor()
{
	//Actors.push_back(std::make_unique<Actor>(Vector2(255.f, 255.f)));
}
