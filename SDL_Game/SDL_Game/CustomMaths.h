#ifndef CUSTOM_MATHS_H
#define CUSTOM_MATHS_H

#include "BasicIncludes.h"
#include <float.h>
#include <cmath>
#include <math.h>
#include <SDL_stdinc.h>

#define PI 3.141592653589793f


inline float degToRad(float degrees)
{
	return degrees * PI / 180;
}

inline float radToDeg(float radians)
{
	return radians * 180 / PI;
}

inline void floatEpsilonCheck(float& num)
{
	if (num <= FLT_EPSILON && num >= -FLT_EPSILON)
	{
		num = 0;
	}
}

struct Vector2
{
	float x;
	float y;

	Vector2(float xpos = 0, float ypos = 0)
	{
		x = xpos;
		y = ypos;
	}

	float Length()
	{
		return sqrt((x * x) + (y * y));
	}

	float LenghtSqrd()
	{
		return (x * x) + (y * y);
	}

	void Truncate(float _upperBound) {
		float sqrLen = LenghtSqrd();

		if (sqrLen > _upperBound * _upperBound)
		{
			double mult = _upperBound / SDL_sqrt(sqrLen);
			this->x *= (float)mult;
			this->y *= (float)mult;
		}
	}

	Vector2 operator+=(const Vector2& vector)
	{
		Vector2 result;

		result.x = this->x += vector.x;
		result.y = this->y += vector.y;

		return result;
	}

	Vector2 operator*=(const Vector2& vector)
	{
		Vector2 result;

		result.x = this->x *= vector.x;
		result.y = this->y *= vector.y;

		return result;
	}

	Vector2 operator+(const Vector2& vector)
	{
		Vector2 result;

		result.x = this->x + vector.x;
		result.y = this->y + vector.y;

		return result;
	}

	Vector2 operator-(const Vector2& vector)
	{
		Vector2 result;

		result.x = this->x - vector.x;
		result.y = this->y - vector.y;

		return result;
	}



	Vector2 operator*(const float& scalar)
	{
		Vector2 result;

		result.x = this->x * scalar;
		result.y = this->y * scalar;

		return result;
	}

	Vector2 operator/(const float& scalar)
	{
		Vector2 result;

		result.x = this->x / scalar;
		result.y = this->y / scalar;

		return result;
	}

	Vector2 Normalise()
	{
		Vector2 temp = Vector2(x, y);

		return temp / Length();
	}
	

	void Normalised()
	{
		Vector2 temp = Vector2(x, y);

		temp =  temp / Length();
		x = temp.x;
		y = temp.y;
	}

	bool IsZero()
	{
		 
		return (x == FLT_EPSILON && y == FLT_EPSILON);
	}

	void Zero()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2 PerpendicularClockwise()
	{
		return Vector2(this->y, -this->x);
	}

	Vector2 PerpendicularAntiClockwise()
	{
		return Vector2(-this->y, this->x);
	}

	static Vector2 Normalized(Vector2 _vec)
	{
		return _vec / _vec.Length();
	}

	static float DotProduct(Vector2 _vec1, Vector2 _vec2)
	{
		float newX = _vec1.x * _vec2.x;
		float newY = _vec1.y * _vec2.y;

		return newX + newY;
	}

	static Vector2 LocalPointToWorld(Vector2 _point, Vector2 _up, Vector2 _right, Vector2 _objPosition) {
		Vector2 worldOffset = _right * _point.x + _up * _point.y;
		return (Vector2)_objPosition + worldOffset;
	}

};



Vector2 operator-(const Vector2& lhs, const Vector2& rhs);

inline Vector2 translateVector2(Vector2 startPos, Vector2 displacementVector) { return startPos + displacementVector; }

/// <summary>
/// Rotate a vector around the origin anti-clockwise by given angle in radians
/// </summary>
/// <param name="position">Position to rotate</param>
/// <param name="angle">Angle in radians</param>
/// <returns>New position after being rotated</returns>
Vector2 rotateVector2(Vector2 position, float angle);


Vector2 rotateVector2(Vector2 position, float angle, bool _clockwise);

/// <summary>
/// Rotates a point around a given pivot anti-clockwise by a given angle in radians
/// </summary>
/// <param name="position">position to rotate</param>
/// <param name="pivot">point to rotate around</param>
/// <param name="angle">angle to rotate in radians</param>
/// <returns></returns>
Vector2 rotateVector2pivot(Vector2 position, Vector2 pivot, float angle);

//given 2 lines in 2d space AB, CD this returns true if an intersection occurs
bool LineIntersection(Vector2 _a, Vector2 _b, Vector2 _c, Vector2 _d);

//given 2 lines in 2d space AB, CD this returns true if an intersection occurs and sets dist to the dist the intersection occurs along AB
bool LineIntersection(Vector2 _a, Vector2 _b, Vector2 _c, Vector2 _d, float &_dist);

//given 2 lines in 2d space AB, CD this returns true if an intersection occurs and sets dist to the dist the intersection occurs along AB. Also sets the 2D vector point to the point of intersection
bool LineIntersection(Vector2 _a, Vector2 _b, Vector2 _c, Vector2 _d, float &_dist, Vector2& _point);


//compares two real numbers. Returns true if they are equal
bool IsEqual(float _a, float _b);

inline Vector2 Vec2_Zero() { return Vector2(0.0f); }

//returns a random double between zero and 1
inline double RandFloat() { return ((rand()) / (RAND_MAX + 1.0)); }

inline double RandInRange(double x, double y)
{
	return x + RandFloat() * (y - x);
}

//class to create and render 2D walls. Defined as the two vectors A - B with a perpendicular normal. 
class Walls2D
{
public:
	Walls2D(){}
	Walls2D(Vector2 _a, Vector2 _b): m_A(_a), m_B(_b) {
		CalculateNormal();
	}	
	Walls2D(Vector2 _a, Vector2 _b, Vector2 _normal): m_A(_a), m_B(_b), m_Normal(_normal){}
	
	Vector2 From() const { return m_A; }
	void SetFrom(Vector2 _pos) { m_A = _pos; CalculateNormal(); }

	Vector2 To() const { return m_B; }
	void SetTo(Vector2 _pos) { m_B = _pos; CalculateNormal(); }

	Vector2 Normal() const { return m_Normal; }
	void SetNormal(Vector2 _normal) { m_Normal = _normal; }

	Vector2 Center() { return (m_A + m_B) / 2.0f; }


protected:
	Vector2 m_A, m_B, m_Normal;
	void CalculateNormal() {
		Vector2 temp = (m_B - m_A).Normalise();
		m_Normal.x = -temp.y;
		m_Normal.y = temp.x;
	}

private:

};



#endif // CUSTOM_MATHS_H

