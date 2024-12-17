#pragma once
#include "SceneComponent.h"
#include "../../../RenderCore/Drawable.h"
#include "../../../RenderCore/CoordinateTransformer.h"



class CameraComponent : public SceneComponent
{
public:

	CameraComponent(Actor* Owner);
	~CameraComponent();

	virtual void Initialize();

	void Draw(Drawable InDrawable)const;
private:

	CoordinateTransformer& CT;
};