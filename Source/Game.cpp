#include "Game.h"
#include <iostream>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_filesystem.h>
#include "System/InputSystem.h"
#include "System/RenderSystem.h"
#include "System/WorldSubsystem/AISystem.h"
#include "System/CollisionSystem.h"
#include "Entity/PlayerCharacter.h"
#include "Controller/PlayerController.h"
#include <chrono>


Game::Game(App& GameApp)
	:
	GameWindow(GameApp.Window),
	GameRenderer(GameApp.Renderer)
{
	const char* BasePath = SDL_GetBasePath();
	ImagePath = std::string(BasePath) + "../../Assets/BackGround.bmp";

	GameWorld = std::make_unique<World>();
	GameWorld->Initialize();
	
	
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


	AISystem* AISubsystem = GameWorld->GetSubsystem<AISystem>();
	if (AISubsystem)
	{
		AISubsystem->SpawnRandomEnemy();
		AISubsystem->SpawnRandomEnemy();
	}

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
		//SDL_Log("Frametime: %i", FrameTime);
	}
}


void Game::HandleGameLoop()
{
	auto starti = std::chrono::high_resolution_clock::now();
	ProcessInput();
	auto endi = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float, std::milli> frameTimei = endi - starti;

	SDL_Log("ProcessInputTime: %f", frameTimei.count());
	

	auto start = std::chrono::high_resolution_clock::now();
	Update();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float, std::milli> frameTime = end - start;

	//SDL_Log("UpdateTime: %f",frameTime.count());

	auto startr = std::chrono::high_resolution_clock::now();
	Render();
	auto endr = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float, std::milli> frameTimer = endr - startr;

	//SDL_Log("RenderTime: %f", frameTimer.count());
	
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

	CollisionSystem::Get().Update();
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
	CollisionSystem::Get().Draw(GameRenderer);
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

