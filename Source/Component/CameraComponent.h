#pragma once
#include "SceneComponent.h"
#include "../Render/Drawable.h"
#include "../Render/CoordinateTransformer.h"



class CameraComponent : public SceneComponent
{
public:
	~CameraComponent();

	
	void Draw(Drawable InDrawable)const;

private:

	CoordinateTransformer& WorldCoordinateTransformer;
};