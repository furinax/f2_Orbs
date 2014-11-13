#include "Interpolator.h"
#include <iterator>
#include "cinder/gl/gl.h"
#include "cinder/PolyLine.h"

using namespace ci;
using namespace std;
using namespace ci::app;

namespace {
	static const float MAX_VEL = 50.f;
	static const int MAX_INTERPOLATIONS = 3;
	static const float ITER = 20.f;
}

Interpolator::Interpolator()
{
	d_color = Color::white();
	d_maxPoints = 10;
}

float Interpolator::getDist(const ci::Vec2f point)
{
	if (d_points.empty())
		return 0.f;
	return d_points.front().distance(point);
}

void Interpolator::addPoint(const ci::Vec2f point)
{
	if (d_interpolationCount > MAX_INTERPOLATIONS)
	{
		if (!d_points.empty() )
			d_points.pop_back();
		return;
	}

	d_points.push_front(point);
	if (d_points.size() > d_maxPoints)
		d_points.pop_back();
}

bool Interpolator::getNextPoint()
{
	typedef list<Vec2f>::iterator points_iter_t;

	d_interpolationCount++;

	if (d_points.empty())
		return false;

	Vec2f nextPoint =  *d_points.begin();
	Vec2f acc = Vec2f::zero();
	Vec2f vel = Vec2f::zero();

	if (d_points.size() > 1)
	{
		vel = *(d_points.begin()) - *(std::next(d_points.begin()));
		vel.x = ci::constrain(vel.x, -MAX_VEL, MAX_VEL);
		vel.y = ci::constrain(vel.y, -MAX_VEL, MAX_VEL);

		//curl towards the center for now
		acc = *(d_points.begin()) - getWindowCenter();
		acc.safeNormalize();
		acc *= -.5f*vel.length();
	}

	vel += acc;
	addPoint(nextPoint + vel);
	return true;
}

void Interpolator::draw()
{
	typedef list<Vec2f>::iterator points_iter_t;

	if (d_points.empty())
		return;

	gl::color(d_color);
	float x1, x2, x3, x4, y1, y2, y3, y4;
	bool firstPoint = false, secondPoint = false;
	for (points_iter_t pointIter = d_points.begin(); pointIter != d_points.end();)
	{
		
		x1 = pointIter->x;
		y1 = pointIter->y;
		
		if (std::next(pointIter) == d_points.end()) // have we reached the end?
			break;

		if (!firstPoint && pointIter == d_points.begin())
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
		if (pointIter == d_points.end())
			break;
		x3 = pointIter->x;
		y3 = pointIter->y;
		pointIter++;
		if (pointIter == d_points.end()){
			x4 = x3;
			y4 = y3;
		}
		else{
			x4 = pointIter->x;
			y4 = pointIter->y;
		}

		pointIter--; // go back to just past where we started
		pointIter--;
		if (pointIter != d_points.begin())
			pointIter--;

		drawCatmullRom(x1, y1, x2, y2, x3, y3, x4, y4); //call our helper function to do the actual drawing

		if (secondPoint)
			pointIter++;
	}
	/*
	glBegin(GL_LINES);
	for (points_iter_t itor = d_points.begin(); itor != d_points.end(); itor++)
	{
		if (std::next(itor) != d_points.end())
		{
			glVertex2f(*itor);
			glVertex2f(*std::next(itor));
		}
	}
	glEnd();*/
}

void Interpolator::drawCatmullRom(float _x1, float _y1, float _x2, float _y2, float _x3, float _y3,
	float _x4, float _y4){

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