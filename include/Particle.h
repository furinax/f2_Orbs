#pragma once

#include "cinder/gl/gl.h"
#include "cinder/Vector.h"

class Particle{
public:
    
    Particle( const ci::Vec2f& position, float radius, float mass, float drag );
    
    void update();
    void draw( bool whiteout );
    
    ci::Vec2f position, prevPosition;
    ci::Vec2f forces;
    float mRadiusAnchor, mRadius;
    float mass;
    float drag;
	int mAge = 0, mLifespan = 100;
	bool mIsDead = false;
	ci::ColorA mColor;
};