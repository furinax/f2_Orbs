#include "CatmullRom.h"
#include <iterator>

using namespace ci;

namespace {
	static const float ITER = 20.f;
}

void CatmullRom::draw(const std::list<Vec2f>& input)
{
	typedef std::list<Vec2f>::const_iterator points_iter_t;

	if (input.empty())
		return;

	float x1, x2, x3, x4, y1, y2, y3, y4;
	bool firstPoint = false, secondPoint = false;
	for (points_iter_t pointIter = input.begin(); pointIter != input.end();)
	{

		x1 = pointIter->x;
		y1 = pointIter->y;

		if (std::next(pointIter) == input.end()) // have we reached the end?
			break;

		if (!firstPoint && pointIter == input.begin())
		{
			firstPoint = true;
			x2 = pointIter->x;
			y2 = pointIter->y;
		}
		else
		{
			secondPoint = true;
			pointIter++;
			x2 = pointIter->x;
			y2 = pointIter->y;
		}
		pointIter++;
		if (pointIter == input.end())
			break;
		x3 = pointIter->x;
		y3 = pointIter->y;
		pointIter++;
		if (pointIter == input.end()){
			x4 = x3;
			y4 = y3;
		}
		else{
			x4 = pointIter->x;
			y4 = pointIter->y;
		}

		pointIter--; // go back to just past where we started
		pointIter--;
		if (pointIter != input.begin())
			pointIter--;

		drawCatmullRom(x1, y1, x2, y2, x3, y3, x4, y4); //call our helper function to do the actual drawing

		if (secondPoint)
			pointIter++;
	}
}

void CatmullRom::draw(const std::list<ci::Vec2f>& input, float width, float taper, ColorA color)
{
	typedef std::list<Vec2f>::const_iterator points_iter_t;

	if (input.empty())
		return;

	float x1, x2, x3, x4, y1, y2, y3, y4;
	bool firstPoint = false, secondPoint = false;

	for (points_iter_t pointIter = input.begin(); pointIter != input.end();)
	{
		glLineWidth(width);
		gl::color(color);
		x1 = pointIter->x;
		y1 = pointIter->y;

		if (std::next(pointIter) == input.end()) // have we reached the end?
			break;

		if (!firstPoint && pointIter == input.begin())
		{
			firstPoint = true;
			x2 = pointIter->x;
			y2 = pointIter->y;
		}
		else
		{
			secondPoint = true;
			pointIter++;
			x2 = pointIter->x;
			y2 = pointIter->y;
		}
		pointIter++;
		if (pointIter == input.end())
			break;
		x3 = pointIter->x;
		y3 = pointIter->y;
		pointIter++;
		if (pointIter == input.end()){
			x4 = x3;
			y4 = y3;
		}
		else{
			x4 = pointIter->x;
			y4 = pointIter->y;
		}

		pointIter--; // go back to just past where we started
		pointIter--;
		if (pointIter != input.begin())
			pointIter--;

		drawCatmullRom(x1, y1, x2, y2, x3, y3, x4, y4); //call our helper function to do the actual drawing

		if (secondPoint)
			pointIter++;

		color.a *= taper;
		width *= taper;
	}
}
void CatmullRom::drawCatmullRom(float _x1, float _y1, float _x2, float _y2, float _x3, float _y3,
	float _x4, float _y4)
{
	float x, y; //our out points
	float t = 1.0f; // weighted value var
	float t2, t3; // t squared, t cubed
	float step = t / ITER;

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= ITER; i++){

		t2 = t * t;
		t3 = t2 * t;

		// the catmull rom magic
		x = 0.5f * ((2.0f * _x2) + (-_x1 + _x3) * t +
			(2.0f * _x1 - 5.0f * _x2 + 4 * _x3 - _x4) * t2 +
			(-_x1 + 3.0f * _x2 - 3.0f * _x3 + _x4) * t3);
		y = 0.5f * ((2.0f * _y2) + (-_y1 + _y3) * t +
			(2.0f * _y1 - 5.0f * _y2 + 4 * _y3 - _y4) * t2 +
			(-_y1 + 3.0f * _y2 - 3.0f * _y3 + _y4) * t3);

		glVertex2f(x, y);

		t -= step; // decrement t
	}

	glEnd();
}