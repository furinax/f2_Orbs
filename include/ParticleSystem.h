#pragma once

#include "Particle.h"
#include "cinder/Vector.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/app/AppNative.h"

class ParticleSystem{
public:
	ParticleSystem();
    ~ParticleSystem();
    
	void setup();
    void update();
    void draw();
    
    void addParticle( Particle *particle );
    void destroyParticle( Particle *particle );
    
	std::vector<Particle*> mParticles;
	ci::gl::Fbo mFboBlurred, mFboTemporary, mFbo;
	ci::gl::GlslProg blurShader;
};