#pragma once

class SDL_Renderer;

class RenderComponent
{
public:
	RenderComponent() = default;

	void Draw(SDL_Renderer* GameRenderer);

private:

};