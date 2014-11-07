#include "Interpolator.h"
#include <iterator>
#include "cinder/gl/gl.h"

using namespace ci;
using namespace std;
using namespace ci::app;

Interpolator::Interpolator()
{
	d_maxPoints = 3;
}

float Interpolator::getDist(const ci::Vec2f point)
{
	if (d_points.empty())
		return 0.f;
	return d_points.back().distance(point);
}

ci::Vec2f Interpolator::addPoint(const ci::Vec2f point)
{
	d_points.push_front(point);
	if (d_points.size() > d_maxPoints)
		d_points.pop_back();
}

ci::Vec2f Interpolator::getNextPoint()
{
	typedef list<Vec2f>::iterator points_iter_t;

	if (d_points.empty())
		return getWindowCenter();

	Vec2f nextPoint = (d_points.empty() ? getWindowCenter() : *d_points.begin());
	Vec2f acc = Vec2f::zero();
	Vec2f vel = Vec2f::zero();

	if (d_points.size() > 1)
	{
		vel = *(d_points.begin()) - *(std::next(d_points.begin()));
	}

	if (d_points.size() > 2)
	{
		acc = (vel + (*(std::next(d_points.begin())) + *(std::next(std::next(d_points.begin()))))) / 2.f;
	}

	vel += acc;
	addPoint(nextPoint + vel);
	return nextPoint + vel;
}

void Interpolator::draw()
{
	typedef list<Vec2f>::iterator points_iter_t;

	if (d_points.empty())
		return ;

	Vec2f nextPoint = (d_points.empty() ? getWindowCenter() : *d_points.begin());
	Vec2f acc = Vec2f::zero();
	Vec2f vel = Vec2f::zero();

	if (d_points.size() > 1)
	{
		vel = *(d_points.begin()) - *(std::next(d_points.begin()));
	}

	if (d_points.size() > 2)
	{
		acc = (vel + (*(std::next(d_points.begin())) + *(std::next(std::next(d_points.begin()))))) / 2.f;
	}

	vel += acc;

	gl::color(Color::white());
	gl::begin(GL_LINES);
	glVertex2f(*d_points.begin());
	glVertex2f(*d_points.begin() + vel);
	gl::end();
}