#include "Game.h"
#include <iostream>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_filesystem.h>
#include "Subsystem/InputSystem.h"
#include "Subsystem/RenderSystem.h"
#include "Entity/PlayerCharacter.h"
#include "Controller/PlayerController.h"


Game::Game(App& GameApp)
	:
	GameWindow(GameApp.Window),
	GameRenderer(GameApp.Renderer)
{
	const char* BasePath = SDL_GetBasePath();
	ImagePath = std::string(BasePath) + "../../Assets/BackGround.bmp";

	GameWorld = std::make_unique<World>();
	
	
}

void Game::StartGame()
{
	IsGameActive = true;
	LoadBackground();

	Transform PlayerSpawnTransform;
	PlayerSpawnTransform.Position = { 255.f,255.f };

	PlayerCharacter* SpawnedPlayer = GameWorld->SpawnActor<PlayerCharacter>(PlayerSpawnTransform);
	PlayerController* IPlayerController = GameWorld->CreateController<PlayerController>();

	IPlayerController->PossessCharacter(SpawnedPlayer);

	while (IsGameActive)
	{
		DeltaTime = static_cast<float>((SDL_GetTicks() - FrameStart))/1000;
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
	InputSystem::Get().HandleInput();
}

void Game::Update()
{
	GameWorld->Update(DeltaTime);

	//Update Verts to Render
	RenderSystem::Get().Update();
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

	//Draw Verts to Render
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

