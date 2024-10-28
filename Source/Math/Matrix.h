#pragma once
#include <cmath>
#include "SDL3/SDL_rect.h"
#include "Transform.h"



struct Matrix3x3 {
    float m[3][3];

    
    Matrix3x3()
    {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                m[i][j] = (i == j) ? 1.f : 0.f;
    }

    
    Matrix3x3(float m00, float m01, float m02,
        float m10, float m11, float m12,
        float m20, float m21, float m22)
    {
        m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
        m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
        m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
    }

    
    SDL_FPoint operator*(const SDL_FPoint& p) const 
    {
        float x = m[0][0] * p.x + m[0][1] * p.y + m[0][2];
        float y = m[1][0] * p.x + m[1][1] * p.y + m[1][2];
        return SDL_FPoint{ x, y };
    }

    Vector2 MultiplyVector2(const Vector2& Point) const
    {
        float x = m[0][0] * Point.X + m[0][1] * Point.Y + m[0][2];
        float y = m[1][0] * Point.X + m[1][1] * Point.Y + m[1][2];
        return Vector2{ x, y };
    }
    
    static Matrix3x3 Translation(const Vector2& InTranslation) 
    {
        return Matrix3x3(
            1, 0, InTranslation.X,
            0, 1, InTranslation.Y,
            0, 0, 1);
    }

    
    static Matrix3x3 Scaling(const Vector2& InScale) 
    {
        return Matrix3x3(
            InScale.X, 0, 0,
            0, InScale.Y, 0,
            0, 0, 1);
    }

    
    static Matrix3x3 Rotation(float Angle)
    {
        float cosA = cos(Angle);
        float sinA = sin(Angle);

        return Matrix3x3(
            cosA, -sinA, 0,
            sinA, cosA, 0,
            0, 0, 1);
    }

    static Matrix3x3 Transform(const Transform& InTransform)
    {
        
        Matrix3x3 ScaleMatrix = Scaling(InTransform.Scale);
        Matrix3x3 RotationMatrix = Rotation(InTransform.Rotation);
        Matrix3x3 TranslationMatrix = Translation(InTransform.Position);

        
        return TranslationMatrix * RotationMatrix * ScaleMatrix;
    }

    
    Matrix3x3 operator*(const Matrix3x3& other) const
    {
        Matrix3x3 Result;
        for (int i = 0; i < 3; ++i) 
        {
            for (int j = 0; j < 3; ++j) 
            {
                Result.m[i][j] =
                    m[i][0] * other.m[0][j] +
                    m[i][1] * other.m[1][j] +
                    m[i][2] * other.m[2][j];
            }
        }
        return Result;
    }
};