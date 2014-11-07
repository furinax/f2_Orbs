#pragma once

#include "cinder/app/AppNative.h"
#include <list>

class Interpolator
{
public:
	Interpolator();
	float getDist(const ci::Vec2f point);
	ci::Vec2f getNextPoint();
	ci::Vec2f addPoint(const ci::Vec2f point);
	void draw();

	std::list<ci::Vec2f> d_points;
	int d_maxPoints;
};