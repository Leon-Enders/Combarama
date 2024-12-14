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
    return ComponentTransform;
}

const Vector2& SceneComponent::GetPosition() const
{
    return ComponentTransform.Position;
}

const float SceneComponent::GetRotation() const
{
    return ComponentTransform.Rotation;
}

const Vector2& SceneComponent::GetScale() const
{
    return ComponentTransform.Scale;
}

const Vector2 SceneComponent::GetForwardVector() const
{
    return ComponentTransform.GetForwardVector();
}


void SceneComponent::SetTransform(const Transform& InTransform)
{
    ComponentTransform = InTransform;
}

void SceneComponent::SetPosition(const Vector2& InPosition)
{
    ComponentTransform.Position = InPosition;

}

void SceneComponent::SetRotation(float InRotation)
{
    ComponentTransform.Rotation = InRotation;
}

void SceneComponent::SetScale(const Vector2& InScale)
{
    ComponentTransform.Scale = InScale;
}

void SceneComponent::AttachToComponent(const SceneComponent* Component)
{
    //TODO: Handle Scene Graph setup
    ParentComponent = Component;
}

const Transform& SceneComponent::GetWorldTransform() const
{
  //TODO: Change when Scene Graph gets implemented. Transforms get returned and added together with their matrices
    if (!ParentComponent)
    {
       return ComponentTransform;
    }
    
    return ParentComponent->GetWorldTransform();
}
