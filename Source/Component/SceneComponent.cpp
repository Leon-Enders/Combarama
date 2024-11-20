#include "SceneComponent.h"



SceneComponent::~SceneComponent()
{
}

void SceneComponent::Initialize(Actor* InOwner)
{
    ActorComponent::Initialize(InOwner);
}

void SceneComponent::Update(float DeltaTime)
{
    ActorComponent::Update(DeltaTime);

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
    LocalTransformMatrix = Matrix3x3::Transform(ComponentTransform);
}

void SceneComponent::SetPosition(const Vector2& InPosition)
{
    ComponentTransform.Position = InPosition;
    LocalTransformMatrix = Matrix3x3::Transform(ComponentTransform);

}

void SceneComponent::SetRotation(float InRotation)
{
    ComponentTransform.Rotation = InRotation;
    LocalTransformMatrix = Matrix3x3::Transform(ComponentTransform);
}

void SceneComponent::SetScale(const Vector2& InScale)
{
    ComponentTransform.Scale = InScale;
    LocalTransformMatrix = Matrix3x3::Transform(ComponentTransform);
}
