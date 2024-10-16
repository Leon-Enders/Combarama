#pragma once
#include "SDL3/SDL_pixels.h"
#include "../Math/Vector2.h"
#include "RenderComponent.h"
#include <memory>

class Avatar
{
public:
	Avatar(const Vector2& InPosition, float Rotation);

	void SetColor(SDL_FColor BodyColor, SDL_FColor HeadColor);

	RenderComponent* GetRenderComponent()const { return AvatarRenderComponent.get(); }
private:
	
	static constexpr float Radius = 25.f;
	static constexpr float HeadWidth = 25.f;
	static constexpr float HeadHeight = 15.f;

	std::unique_ptr<RenderComponent> AvatarRenderComponent;
};