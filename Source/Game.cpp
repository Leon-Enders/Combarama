#include "Game.h"
#include <chrono>
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
#include "Utility/ColorHelper.h"



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


	//TODO:: Create a level class which gets managed by world to put this code
	Transform ObstacleTransform1;
	Transform ObstacleTransform2;
	Transform ObstacleTransform3;
	Transform ObstacleTransform4;
	ObstacleTransform1.Position = { 0.f,360.f };
	ObstacleTransform2.Position = { 1280.f,360.f };
	ObstacleTransform3.Position = { 640.f,0.f };
	ObstacleTransform4.Position = { 640.f,720.f };

	GameWorld->SpawnObstacle(ObstacleTransform1, { 50.f,720.f }, COLOR_PURPLE);
	GameWorld->SpawnObstacle(ObstacleTransform2, { 50.f,720.f }, COLOR_PURPLE);
	GameWorld->SpawnObstacle(ObstacleTransform3, { 1280.f,50.f }, COLOR_PURPLE);
	GameWorld->SpawnObstacle(ObstacleTransform4, { 1280.f,50.f }, COLOR_PURPLE);


	StartGameLoop();
}


void Game::StartGameLoop()
{
	while (IsGameActive)
	{
		DeltaTimeMS = static_cast<float>((SDL_GetTicks() - FrameStart));
		DeltaTimeS = DeltaTimeMS / 1000;
		FrameStart = SDL_GetTicks();
		FixedTimeCounter += DeltaTimeMS;

		GameLoop();

		FrameTime = SDL_GetTicks() - FrameStart;

		if (FrameDelay > FrameTime)
		{
			SDL_Delay(FrameDelay - static_cast<Uint32>(FrameTime));
		}
	}
}

void Game::GameLoop()
{
	ProcessInput();
	Update();
	FixedUpdate();
	Render();
}

void Game::ProcessInput()
{
	InputSystem::Get().HandleInput();
}


void Game::Update()
{
	GameWorld->Update(DeltaTimeS);
	
}

void Game::FixedUpdate()
{
	while (FixedTimeCounter >= FixedDeltaTimeMS)
	{
		GameWorld->FixedUpdate(FixedDeltaTimeS);
		CollisionSystem::Get().Update(FixedDeltaTimeS);
		FixedTimeCounter -= FixedDeltaTimeMS;
	}
}

void Game::Render()
{
	ComposeFrame();
	RenderFrame();
}

void Game::ComposeFrame()
{
	//Update Verts to Render
	RenderSystem::Get().Update();

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

