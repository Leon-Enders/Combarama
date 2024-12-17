#include "Game.h"
#include <chrono>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_filesystem.h>
#include "Input/InputSystem.h"
#include "GameFramework/World/AISubsystem.h"
#include "Physics/CollisionSystem.h"
#include "GameFramework/GameObject/Character/PlayerCharacter.h"
#include "GameFramework/GameObject/Controller/PlayerController.h"
#include "GameFramework/GameObject/Obstacle.h"
#include "../RenderCore/Misc/ColorHelper.h"
#include "../RenderCore/Misc/DrawDebugHelpers.h"
#include "../Core/Math/Matrix.h"

Game* AGame = nullptr;

Game::Game(App& GameApp)
	:
	GameWindow(GameApp.Window),
	GameRenderer(GameApp.Renderer)
{
	const char* BasePath = SDL_GetBasePath();
	ImagePath = std::string(BasePath) + "../../Engine/Content/BackGround.bmp";

	RS = std::make_unique<RenderSubsystem>(GameRenderer);
	GameWorld = std::make_unique<World>(this);
}

void Game::Initialize()
{
	GameWorld->Initialize();

	auto Identity = TMatrix::Identity();
	auto Scale1 = TMatrix::Scale(3.f);
	auto Scale2 = TMatrix::Scale(5.f);
	auto Translate = TMatrix::Translate({ 50.f,50.f });
	auto DoubleScale = Scale2 * Scale1;
	auto ScaleThenTranslate = Scale2 * Scale1 * Translate;

	Vector3 Test(5.f, 5.f);
	Vector3 TestWithIdentity = DoubleScale * Test;
}

void Game::StartGame()
{

	InputSystem::Get().QuitDelegate.BindFunction(std::bind(&Game::QuitGame, this));


	DrawDebugHelpers::Get().Initialize(GameRenderer);

	IsGameActive = true;
	LoadBackground();

	Transform PlayerSpawnTransform;
	PlayerSpawnTransform.Position = { 50.f,250.f };
	
	auto SpawnedPlayerPtr = GameWorld->SpawnGameObject<PlayerCharacter>(PlayerSpawnTransform);
	auto PlayerControllerPtr = GameWorld->SpawnGameObject<PlayerController>();
	
	if (auto sPlayerController = PlayerControllerPtr.lock())
	{
		sPlayerController->PossessCharacter(std::shared_ptr<PlayerCharacter>(SpawnedPlayerPtr));
	}



	//AISystem* AISubsystem = GameWorld->GetSubsystem<AISystem>();
	//if (AISubsystem)
	//{
	//	AISubsystem->SpawnRandomEnemy();
	//	AISubsystem->SpawnRandomEnemy();
	//	AISubsystem->SpawnRandomEnemy();
	//	AISubsystem->SpawnRandomEnemy();
	//}


	//TODO:: Create a level class which gets managed by world to put this code
	Transform ObstacleTransform1;
	Transform ObstacleTransform2;
	Transform ObstacleTransform3;
	Transform ObstacleTransform4;
	Transform ObstacleTransform5;
	Transform ObstacleTransform6;
	Transform ObstacleTransform7;

	ObstacleTransform1.Position = { 0.f,0.f };
	ObstacleTransform2.Position = { -100.f,200.f };

	GameWorld->SpawnGameObject<Obstacle>(ObstacleTransform1, Vector2(50.f, 100.f), COLOR_PURPLE);
	GameWorld->SpawnGameObject<Obstacle>(ObstacleTransform2, Vector2(50.f, 100.f), COLOR_PURPLE);
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
	FixedUpdate();
	Update();
	LateUpdate();
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
		//CollisionSystem::Get().FixedUpdate(FixedDeltaTimeS);
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

	// Clear BackBuffer
	SDL_SetRenderDrawColor(GameRenderer, 0, 0, 0, 255);
	SDL_RenderClear(GameRenderer);

	//TODO: Refactor this into Level
	SDL_RenderTexture(GameRenderer, GameBackground, &BackGround, NULL);

	//Draw Verts to Render
	RS->Draw();
	//CollisionSystem::Get().Draw(GameRenderer);
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

