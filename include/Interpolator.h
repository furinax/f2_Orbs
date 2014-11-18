#pragma once

#include "cinder/app/AppNative.h"
#include <list>

class Interpolator
{
public:
	Interpolator();
	float getDist(const ci::Vec2f point);
	bool getNextPoint();
	ci::Vec2f getFrontPoint(); //returns Vec2f::zero() if there is no front point
	void addPoint(const ci::Vec2f point);
	void draw();
	void drawCatmullRom(float _x1, float _y1, float _x2, float _y2, float _x3, float _y3,
		float _x4, float _y4);

	std::list<ci::Vec2f> d_points;
	int d_maxPoints;
	int d_interpolationCount = 0;
	ci::Color d_color;
};