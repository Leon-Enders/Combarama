#include "Game.h"
#include <iostream>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_filesystem.h>
#include "Subsystem/InputSystem.h"
#include "Subsystem/RenderSystem.h"


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

	TPlayerController = std::make_unique<PlayerController>();
	Player = std::make_unique<PlayerCharacter>(Vector2(255.f, 255.f));
	Player->Initialize();
	TPlayerController->PossessCharacter(Player.get());

	InitializeSubsystems();
	



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

void Game::InitializeSubsystems()
{
	ActiveAISystem.Initialize(Player.get());
}

void Game::HandleGameLoop()
{
	ProcessInput();
	Update();
	Render();
}

void Game::ProcessInput()
{
	InputSystem::Get().HandleInput();
}

void Game::Update()
{
	Player->Update(DeltaTime);
	ActiveAISystem.Update(DeltaTime);
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
	SDL_RenderTexture(GameRenderer, GameBackground, &BackGround, NULL);

	RenderSystem::Get().Draw(GameRenderer);
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

void Game::QuitGame()
{
	IsGameActive = false;
}

