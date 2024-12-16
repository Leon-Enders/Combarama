#include "SceneComponent.h"


SceneComponent::SceneComponent(Actor* Owner)
    :
    ActorComponent(Owner)
{
}

SceneComponent::~SceneComponent()
{
}

void SceneComponent::Initialize()
{
}

const Transform& SceneComponent::GetTransform() const
{
    return LocalTransform;
}

const Vector2& SceneComponent::GetPosition() const
{
    return LocalTransform.Position;
}

const float SceneComponent::GetRotation() const
{
    return LocalTransform.Rotation;
}

const Vector2& SceneComponent::GetScale() const
{
    return LocalTransform.Scale;
}

const Vector2 SceneComponent::GetForwardVector() const
{
    return LocalTransform.GetForwardVector();
}


void SceneComponent::SetTransform(const Transform& InTransform)
{
    LocalTransform = InTransform;
}

void SceneComponent::SetPosition(const Vector2& InPosition)
{
    LocalTransform.Position = InPosition;

}

void SceneComponent::SetRotation(float InRotation)
{
    LocalTransform.Rotation = InRotation;
}

void SceneComponent::SetScale(const Vector2& InScale)
{
    LocalTransform.Scale = InScale;
}

void SceneComponent::AttachToComponent(const SceneComponent* Component)
{
    //TODO: Handle Scene Graph setup
    ParentComponent = Component;
}

const TMatrix SceneComponent::GetLocalMatrix() const
{
    return TMatrix::TransformToMatrix(LocalTransform);
}

const TMatrix SceneComponent::GetWorldMatrix() const
{
    TMatrix LocalMatrix = GetLocalMatrix();
    if (!ParentComponent)
    {
        return LocalMatrix;
    }

    return ParentComponent->GetWorldMatrix() * LocalMatrix;
}

const Transform SceneComponent::GetWorldTransform() const
{
    //TODO: Create a system so you dont have to decompose the world matrix each time the world transform gets accessed
    if (!ParentComponent)
    {
        return LocalTransform;
    }

    return GetWorldMatrix().Decompose();
}


