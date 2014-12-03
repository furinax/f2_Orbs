#include "Interpolator.h"
#include <iterator>
#include "cinder/gl/gl.h"
#include "CatmullRom.h"

using namespace ci;
using namespace ci::app;

namespace {
	static const float MAX_VEL = 50.f;
	static const int MAX_INTERPOLATIONS = 3;
	
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
	typedef std::list<Vec2f>::iterator points_iter_t;

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

Vec2f Interpolator::getFrontPoint()
{
	if (d_interpolationCount > MAX_INTERPOLATIONS || d_points.empty() )
		return getWindowCenter();
	return d_points.front();
}

void Interpolator::draw()
{
	gl::color(d_color);
	CatmullRom::draw(d_points);	
}