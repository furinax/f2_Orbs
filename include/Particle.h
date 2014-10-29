#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"

class Particle{
public:
    
    Particle( const ci::Vec2f& position, float radius );
    
    void update();
	void draw(bool overlay);
    
    ci::Vec2f position, prevPosition, anchorPosition;
	ci::Vec2f mVel, mAcc;
    float mRadiusAnchor, mRadius, mDrag;
	int mAge = 0, mLifespan = 20;
	bool mIsDead = false;
	ci::ColorA mColor, mOverlayColor;

	//float VEL_THRESHOLD = 25.f; //threshold of vel to determine when to draw a line
};