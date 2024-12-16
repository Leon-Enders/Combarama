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

const TMatrix SceneComponent::GetWorldTransformation() const
{
    TMatrix LocalTransformation = TMatrix::TransformToMatrix(LocalTransform);

    if (!ParentComponent)
    {
        return LocalTransformation;
    }

    return ParentComponent->GetWorldTransformation() * LocalTransformation;
}

const Transform SceneComponent::GetWorldTransform() const
{
    if (!ParentComponent)
    {
        return LocalTransform;
    }
    TMatrix LocalTransformation = TMatrix::TransformToMatrix(LocalTransform);

    return LocalTransformation * ParentComponent->GetWorldTransform();
}


