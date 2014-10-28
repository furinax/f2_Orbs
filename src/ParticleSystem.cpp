#include "ParticleSystem.h"

using namespace ci;
using namespace ci::app;
using namespace std;

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem(){
    for( std::vector<Particle*>::iterator it = mParticles.begin(); it != mParticles.end(); ++it ){
        delete *it;
    }
    mParticles.clear();
}

void ParticleSystem::setup()
{
	gl::Fbo::Format format;
	format.enableMipmapping(false);
	format.setCoverageSamples(16);
	format.setSamples(4);

	mFbo = gl::Fbo(getWindowWidth(), getWindowHeight(), format); mFbo.getTexture().setFlipped(true);
	mFboBlurred = gl::Fbo(getWindowWidth(), getWindowHeight(), format); mFboBlurred.getTexture().setFlipped(true);
	mFboTemporary = gl::Fbo(getWindowWidth(), getWindowHeight(), format);

	blurShader = gl::GlslProg(loadFile("../assets/blur_vert.glsl"),
		loadFile("../assets/blur_frag.glsl"));
}

void ParticleSystem::update(){
	for (std::vector<Particle*>::iterator it = mParticles.begin(); it != mParticles.end();){
		if ((*it)->mIsDead) {
			it = mParticles.erase(it);
		}
		else {
			(*it)->update();
			++it;
		}
    }
}

void ParticleSystem::draw(){
	//gl::clear(Color(0, 0, 0));
	mFboBlurred.bindFramebuffer();
	gl::enableAlphaBlending();

	ColorA fade(0, 0, 0, .1f);
	Rectf rect(0, 0, getWindowWidth(), getWindowHeight());
	gl::color(fade);
	gl::drawSolidRect(rect);

	gl::disableAlphaBlending();

    for( std::vector<Particle*>::iterator it = mParticles.begin(); it != mParticles.end(); ++it ){
        (*it)->draw(false);
    }
	
	mFboBlurred.unbindFramebuffer();

	mFbo.bindFramebuffer();
	gl::draw(mFboBlurred.getTexture(), getWindowBounds());
	mFbo.unbindFramebuffer();

	blurShader.bind();
	blurShader.uniform("tex0", 0); // use mFboBlurred, see lower
	blurShader.uniform("sampleOffset", Vec2f(1.5f / 800.0f, 0.0f));
	
	mFboTemporary.bindFramebuffer();
	gl::clear(Color::black());
	mFboBlurred.bindTexture(0); // use rendered scene as texture
	gl::pushMatrices();
	gl::setMatricesWindow(getWindowWidth(), getWindowHeight(), false);
	gl::drawSolidRect(mFboBlurred.getBounds());
	gl::popMatrices();
	mFboBlurred.unbindTexture();
	mFboTemporary.unbindFramebuffer();

	blurShader.uniform("sampleOffset", Vec2f(0.0f, 1.5f / 600.0f));

	mFboBlurred.bindFramebuffer();
	gl::clear(Color::black());
	mFboTemporary.bindTexture(0); // use horizontally blurred scene as texture
	gl::pushMatrices();
	gl::setMatricesWindow(getWindowWidth(), getWindowHeight(), false);
	gl::drawSolidRect(mFboTemporary.getBounds());
	gl::popMatrices();
	mFboTemporary.unbindTexture();
	mFboBlurred.unbindFramebuffer();

	blurShader.unbind();

	gl::enableAdditiveBlending();
	gl::draw(mFboBlurred.getTexture(), getWindowBounds());
	//gl::draw(mFboBlurred.getTexture(), getWindowBounds());
	//gl::draw(mFboBlurred.getTexture(), getWindowBounds());
	
	for (std::vector<Particle*>::iterator it = mParticles.begin(); it != mParticles.end(); ++it){
		(*it)->draw( true );
	}

	gl::disableAlphaBlending();
}

void ParticleSystem::addParticle( Particle *particle ){
    mParticles.push_back( particle );
}

void ParticleSystem::destroyParticle( Particle *particle ){
    std::vector<Particle*>::iterator it = std::find( mParticles.begin(), mParticles.end(), particle );
    delete *it;
    mParticles.erase( it );
}


