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
    UpdateLocalMatrix();
}

void SceneComponent::SetPosition(const Vector2& InPosition)
{
    ComponentTransform.Position = InPosition;
    UpdateLocalMatrix();

}

void SceneComponent::SetRotation(float InRotation)
{
    ComponentTransform.Rotation = InRotation;
    UpdateLocalMatrix();
}

void SceneComponent::SetScale(const Vector2& InScale)
{
    ComponentTransform.Scale = InScale;
    UpdateLocalMatrix();
}

void SceneComponent::UpdateLocalMatrix()
{
    LocalTransformMatrix = Matrix3x3::Transform(ComponentTransform);
}
