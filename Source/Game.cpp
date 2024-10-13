#include "Game.h"
#include <iostream>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_filesystem.h>



Game::Game(App& GameApp)
	:
	GameWindow(GameApp.Window),
	GameRenderer(GameApp.Renderer)
{
	const char* BasePath = SDL_GetBasePath();
	ImagePath = std::string(BasePath) + "../../Assets/BackGround.bmp";
}

void Game::StartGame()
{
	IsGameActive = true;
	LoadBackground();
	
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
			Player->AddInput(Event);
			if (Event.key.key == SDLK_SPACE)
			{
				// Do something
			}
		}
	}

	Player->HandleInput();

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

	//TODO: Refactor this into Level
	const SDL_FRect BackGround = { 0.f,0.f,1920.f,1080.f};
	SDL_RenderTexture(GameRenderer, GameBackground, &BackGround, NULL);

	Player->Draw(GameRenderer);

}

void Game::RenderFrame()
{
	SDL_RenderPresent(GameRenderer);
}


void Game::LoadBackground()
{
	
	SDL_Surface* BackgroundSurface = SDL_LoadBMP(ImagePath.c_str());

	if (!BackgroundSurface)
	{
		SDL_Log("Unable to load image: %s", SDL_GetError());
		
	}

	GameBackground = SDL_CreateTextureFromSurface(GameRenderer, BackgroundSurface);
	SDL_DestroySurface(BackgroundSurface); 

	if (!GameBackground)
	{
		SDL_Log("Unable to create texture: %s", SDL_GetError());
	}

}
