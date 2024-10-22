#pragma once
#include <cmath>
#include "SDL3/SDL_rect.h"



struct Matrix3x3 {
    float m[3][3];

    // Default constructor initializes to identity matrix
    Matrix3x3() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                m[i][j] = (i == j) ? 1 : 0;
    }

    // Constructor for specific values
    Matrix3x3(float m00, float m01, float m02,
        float m10, float m11, float m12,
        float m20, float m21, float m22) {
        m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
        m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
        m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
    }

    // Multiply matrix by SDL_FPoint
    SDL_FPoint operator*(const SDL_FPoint& p) const {
        float x = m[0][0] * p.x + m[0][1] * p.y + m[0][2];
        float y = m[1][0] * p.x + m[1][1] * p.y + m[1][2];
        return SDL_FPoint{ x, y };
    }

    // Translation
    static Matrix3x3 translation(float tx, float ty) {
        return Matrix3x3(1, 0, tx,
            0, 1, ty,
            0, 0, 1);
    }

    // Scaling
    static Matrix3x3 scaling(float sx, float sy) {
        return Matrix3x3(sx, 0, 0,
            0, sy, 0,
            0, 0, 1);
    }

    // Rotation
    static Matrix3x3 rotation(float angle) {
        float rad = angle; // Convert degrees to radians
        float cosA = cos(angle);
        float sinA = sin(angle);
        return Matrix3x3(cosA, -sinA, 0,
            sinA, cosA, 0,
            0, 0, 1);
    }
    };