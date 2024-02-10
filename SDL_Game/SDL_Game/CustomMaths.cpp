#include "CustomMaths.h"



bool IsEqual(float _a, float _b)
{
	if (fabs(_a - _b) < 1E-12)
	{
		return true;
	}

	return false;
}



Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	Vector2 result(lhs);

	result.x -= rhs.x;
	result.y -= rhs.y;

	return result;
}

Vector2 rotateVector2(Vector2 position, float angle)
{
	Vector2 result;

	result.x = (position.x * cos(angle)) - (position.y * sin(angle));
	result.y = (position.x * sin(angle)) + (position.y * cos(angle));

	floatEpsilonCheck(result.x);
	floatEpsilonCheck(result.y);

	return result;
}

Vector2 rotateVector2(Vector2 position, float angle, bool _clockwise) {
	Vector2 temp;
	if (_clockwise)
	{
		temp.x = position.x * cosf(angle) + position.y * sinf(angle);
		temp.x = -1 * (position.x * sinf(angle)) + position.y * cosf(angle);
	}
	else
	{
		temp.x = position.x * cosf(angle) - position.y * sinf(angle);
		temp.x = (position.x * sinf(angle)) + position.y * cosf(angle);
	}
	return temp;
}

Vector2 rotateVector2pivot(Vector2 position, Vector2 pivot, float angle)
{
	Vector2 rotPosition = position - pivot;

	Vector2 result = rotateVector2(rotPosition, angle);

	result = result + pivot;

	return result;
}

bool LineIntersection(Vector2 _a, Vector2 _b, Vector2 _c, Vector2 _d)
{
	float rTop = (_a.y - _c.y) * (_d.x-_c.x) - (_a.x-_c.x) * (_d.y-_c.y);
	float sTop = (_a.y - _c.y) * (_b.x-_a.x) - (_a.x-_c.x) * (_b.y-_a.y);

	float bot = (_b.x - _a.x) * (_d.y-_c.y) - (_b.y-_a.y) * (_d.x-_c.x);
	
	if (bot == 0)//parallel
	{
		return false;
	}
	float r = rTop / bot;
	float s = sTop / bot;

	if ((r>0)&& (r<1) &&(s>0)&&(s<1))
	{
		//line intersects
		return true;
	}

	//lines do not intersect
	return false;
}

bool LineIntersection(Vector2 _a, Vector2 _b, Vector2 _c, Vector2 _d, float& _dist)
{
	float rTop = (_a.y - _c.y) * (_d.x - _c.x) - (_a.x - _c.x) * (_d.y - _c.y);
	float sTop = (_a.y - _c.y) * (_b.x - _a.x) - (_a.x - _c.x) * (_b.y - _a.y);

	float bot = (_b.x - _a.x) * (_d.y - _c.y) - (_b.y - _a.y) * (_d.x - _c.x);

	if (bot == 0)//parallel
	{
		//if (IsEqual(rTop,0) && IsEqual(sTop,0))
		//{
		//	return true;
		//}
		return false;
	}
	float r = rTop / bot;
	float s = sTop / bot;

	if ((r > 0) && (r < 1) && (s > 0) && (s < 1))
	{
		_dist = (_b - _a).Length() * r;
		return true;
	}
	else
	{
		_dist = 0;
		return false;
	}
}

bool LineIntersection(Vector2 _a, Vector2 _b, Vector2 _c, Vector2 _d, float& _dist, Vector2& _point)
{

	float rTop = (_a.y - _c.y) * (_d.x - _c.x) - (_a.x - _c.x) * (_d.y - _c.y);
	float rBot = (_b.x - _a.x) * (_d.y - _c.y) - (_b.y - _a.y) * (_d.x - _c.x);

	float sTop = (_a.y - _c.y) * (_b.x - _a.x) - (_a.x - _c.x) * (_b.y - _a.y);
	float sBot = (_b.x - _a.x) * (_d.y - _c.y) - (_b.y - _a.y) * (_d.x - _c.x);

	if ((rBot == 0) || (sBot == 0 ) )
	{
		//lines are parallel
		return false;
	}
	float r = rTop / rBot;
	float s = sTop / sBot;

	if ((r>0) && (r <1) && (s>0) && (s<1))
	{
		_dist = (_b - _a).Length() * r;
		_point =   (_b - _a) *  r +_a;
		return true;
	}
	else
	{
		_dist = 0;
		return false;
	}

}

