#pragma once
#include <memory>
#include <vector>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_events.h>
#include "CombaramaStructs.h"
#include "Actor.h"




class Game
{
public:
	Game(App& GameApp);

	void StartGame();
	

	//GameLoop
	void HandleGameLoop();
	void ProcessInput();
	void Update();
	void Render();


	//Renderer
	void ComposeFrame();
	void RenderFrame();	


	//Test
	void SpawnActor();

private:

	SDL_Window* GameWindow = nullptr;
	SDL_Renderer* GameRenderer = nullptr;

	bool IsGameActive = false;

	Uint64 FrameStart = 0;
	Uint64 FrameTime = 0;
	float DeltaTime = 0;


	static constexpr int FPS = 60;
	static constexpr int FrameDelay = 1000 / FPS;

	std::unique_ptr<Actor> Player = nullptr;

	//std::vector<std::unique_ptr<Actor>> Actors;

};