#pragma once

#include "../3rdParty/glm/glm.hpp"

using Vector2 = glm::vec2;
using Vector3 = glm::vec3;

namespace Math 
{
	typedef struct Point
	{
		int x;
		int y;
	} Point;

	typedef struct FPoint
	{
		float x;
		float y;
	} FPoint;

	typedef struct Rectangle
	{
		int x, y;
		int w, h;
	} Rectangle;

	typedef struct FRectangle
	{
		float x;
		float y;
		float w;
		float h;
	} FRectangle;


	inline bool isPointInRect(const Point& p, const Rectangle& r)
	{
		return ((p.x >= r.x) && (p.x < (r.x + r.w)) &&
			(p.y >= r.y) && (p.y < (r.y + r.h))) ? true : false;
	}
}