#pragma once

#include <list>
#include "cinder/gl/gl.h"

class CatmullRom
{
public:
	static void draw(const std::list<ci::Vec2f>& input);
	static void draw(const std::list<ci::Vec2f>& input, float width, float taper, ci::ColorA color );

private:
	CatmullRom();
	static void drawCatmullRom(float _x1, float _y1, float _x2, float _y2, float _x3, float _y3,
		float _x4, float _y4);
};