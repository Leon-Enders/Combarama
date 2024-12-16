#pragma once
#include <cmath>
#include "SDL3/SDL_rect.h"
#include "Vector3.h"



class TMatrix
{
public:

	Vector2 operator*(const Vector2& rhs)const
	{
		return Vector2(*this * Vector3(rhs));
	}

	Vector3 operator*(const Vector3& rhs)const
	{
		Vector3 OutVector;

		OutVector.X = Cells[0][0] * rhs.X + Cells[0][1] * rhs.Y + Cells[0][2];
		OutVector.Y = Cells[1][0] * rhs.X + Cells[1][1] * rhs.Y + Cells[1][2];
		OutVector.W = Cells[2][0] * rhs.X + Cells[2][1] * rhs.Y + Cells[2][2];

		return OutVector;
	}

	SDL_FPoint operator*(const SDL_FPoint& rhs)const
	{
		SDL_FPoint OutPoint;

		OutPoint.x = Cells[0][0] * rhs.x + Cells[0][1] * rhs.y + Cells[0][2];
		OutPoint.y = Cells[1][0] * rhs.x + Cells[1][1] * rhs.y + Cells[1][2];
		

		return OutPoint;
	}

	TMatrix operator*(const TMatrix& rhs)const
	{
		TMatrix OutMatrix;
		for (int row_left = 0; row_left < 3; row_left++)
		{
			for (int col_right = 0; col_right < 3; col_right++)
			{
				for (int i = 0; i < 3; i++)
				{	
					OutMatrix.Cells[row_left][col_right] += Cells[row_left][i] * rhs.Cells[i][col_right];
				}
			}
		}
		return OutMatrix;
	}

	Transform operator*(const Transform& rhs)
	{
		Transform OutTransform;

		OutTransform.Position = *this * rhs.Position;
		OutTransform.Rotation += rhs.Rotation;
		OutTransform.Scale *= rhs.Scale;

		return OutTransform;
	}

	static TMatrix TransformToMatrix(const Transform& Transformation)
	{
		return TMatrix::Translate(Transformation.Position) *
			TMatrix::Scale(Transformation.Scale.X) *
			TMatrix::Rotate(Transformation.Rotation);
	}

	//Create ScaleMatrix
	static TMatrix Scale(const float Scale)
	{
		// Use ApplyMatrix to Vec2 here, and simply Use Identity scaled by the scale
		return {
			Scale,0.f,0.f,
			0.f,Scale,0.f,
			0.f,0.f,1.f
		};
	}


	static TMatrix Identity()
	{
		return Scale(1.f);
	}

	static TMatrix FlipY()
	{
		return {
			1.f,0.f,0.f,
			0.f,-1.f,0.f,
			0.f,0.f,1.f
		};
	}

	
	static TMatrix Rotate(const float Theta)
	{
		const auto sinT = std::sin(Theta);
		const auto cosT = std::cos(Theta);

		return {
		cosT, -sinT,0.f,
		sinT,cosT,0.f,
		0.f,0.f,1.f
		};
	}
	
	static TMatrix Translate(const Vector2& Translation)
	{
		return{
			1.f,0.f,Translation.X,
			0.f,1.f,Translation.Y,
			0.f,0.f,1.f
		};
	}
	float Cells[3][3] = {0};
};