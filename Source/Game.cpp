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
#include "Utility/DrawDebugHelpers.h"



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

	InputSystem::Get().QuitDelegate.BindFunction(std::bind(&Game::QuitGame, this));


	DrawDebugHelpers::Get().Initialize(GameRenderer);

	IsGameActive = true;
	LoadBackground();

	Transform PlayerSpawnTransform;
	PlayerSpawnTransform.Position = { 840.f,1000.f };

	auto SpawnedPlayerPtr = GameWorld->SpawnActor<PlayerCharacter>(PlayerSpawnTransform);
	auto PlayerControllerPtr = GameWorld->SpawnGameObject<PlayerController>();

	if (auto sPlayerController = PlayerControllerPtr.lock())
	{
		sPlayerController->PossessCharacter(std::shared_ptr<PlayerCharacter>(SpawnedPlayerPtr));
	}



	AISystem* AISubsystem = GameWorld->GetSubsystem<AISystem>();
	if (AISubsystem)
	{
		AISubsystem->SpawnRandomEnemy();
		AISubsystem->SpawnRandomEnemy();
		AISubsystem->SpawnRandomEnemy();
		AISubsystem->SpawnRandomEnemy();
	}


	//TODO:: Create a level class which gets managed by world to put this code
	Transform ObstacleTransform1;
	Transform ObstacleTransform2;
	Transform ObstacleTransform3;
	Transform ObstacleTransform4;
	Transform ObstacleTransform5;
	Transform ObstacleTransform6;
	Transform ObstacleTransform7;

	ObstacleTransform1.Position = { 0.f,525.f };
	ObstacleTransform2.Position = { 1680.f,525.f };
	ObstacleTransform3.Position = { 840.f,0.f };
	ObstacleTransform4.Position = { 360.f,1000.f };
	ObstacleTransform5.Position = { 840.f,475.f };
	ObstacleTransform6.Position = { 1320.f,1000.f };
	ObstacleTransform7.Position = { 840.f, 1050.f };

	GameWorld->SpawnObstacle(ObstacleTransform1, { 25.f,1050.f }, COLOR_PURPLE);
	GameWorld->SpawnObstacle(ObstacleTransform2, { 25.f,1050.f }, COLOR_PURPLE);
	GameWorld->SpawnObstacle(ObstacleTransform3, { 1680.f,50.f }, COLOR_PURPLE);
	GameWorld->SpawnObstacle(ObstacleTransform4, { 800.f,100.f }, COLOR_PURPLE);
	GameWorld->SpawnObstacle(ObstacleTransform5, { 700.f,50.f }, COLOR_PURPLE);
	GameWorld->SpawnObstacle(ObstacleTransform6, { 800.f,100.f }, COLOR_PURPLE);
	GameWorld->SpawnObstacle(ObstacleTransform7, { 1680.f,25.f }, COLOR_PURPLE);

	StartGameLoop();
}


void Game::StartGameLoop()
{
	while (IsGameActive)
	{
		DeltaTimeMS = static_cast<float>((SDL_GetTicks() - FrameStart));
		DeltaTimeS = DeltaTimeMS / 1000;
		FrameStart = SDL_GetTicks();
		FixedTimeCounter += static_cast<int>(DeltaTimeMS);

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
	LateUpdate();
	Update();
	FixedUpdate();
	Render();
}

void Game::ProcessInput()
{
	InputSystem::Get().HandleInput();
}

void Game::LateUpdate()
{
	GameWorld->LateUpdate(DeltaTimeS);
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
	GameWorld->DrawDebug();
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

