#include "cinder/app/AppNative.h"

#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Surface.h"
#include "cinder/ImageIo.h"
#include "cinder/cairo/Cairo.h"
#include "cinder/Capture.h"
#include "cinder/params/Params.h"
#include "ParticleSystem.h"
#include "cinder/Rand.h"
#include "Tracker.h"
#include "Listener.h"

#include "CinderOpenCV.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ColorTrackingSoundApp : public AppNative {
public:
	void setup();
	void mouseDown(MouseEvent event);
	void mouseUp(MouseEvent event);
	void mouseMove(MouseEvent event);
	void mouseDrag(MouseEvent event);

	void update();
	void draw();

	ParticleSystem ps;
	Tracker t;
	Listener list;
	Vec2f mMousePosition, mPrevPosition;

	float MAX_PARTICLE_RADIUS = 25.f, MIN_PARTICLE_RADIUS = 2.f;
};

void ColorTrackingSoundApp::setup()
{
	gl::color(Color::black());
	setWindowSize(800, 600);
	mMousePosition = getWindowCenter();
	mPrevPosition = getWindowCenter();

	t.setup();
	ps.setup();
	list.setup();

}

void ColorTrackingSoundApp::mouseUp(MouseEvent event)
{
	mPrevPosition = mMousePosition;
	mMousePosition = event.getPos();
}
void ColorTrackingSoundApp::mouseDown(MouseEvent event)
{
	mPrevPosition = mMousePosition;
	mMousePosition = event.getPos();
}
void ColorTrackingSoundApp::mouseDrag(MouseEvent event)
{
	mPrevPosition = mMousePosition;
	mMousePosition = event.getPos();
}

void ColorTrackingSoundApp::mouseMove(MouseEvent event)
{
	mPrevPosition = mMousePosition;
	mMousePosition = event.getPos();
	for (std::vector<Particle*>::iterator it = ps.mParticles.begin(); it != ps.mParticles.end(); ++it) {
		Vec2f repulsionForce = (*it)->position - event.getPos();
		repulsionForce = repulsionForce.normalized() * math<float>::max(0.f, 100.f - repulsionForce.length());
		(*it)->forces += repulsionForce;
	}
}

void ColorTrackingSoundApp::update()
{
	t.update();
	list.update();

	for (int i = 0; i < t.mCenters.size(); i++)
	{
		Particle* particle = new Particle(fromOcv(t.mCenters[i] * t.mScaling), ci::constrain(MAX_PARTICLE_RADIUS * list.getVolume() * 5.f, MIN_PARTICLE_RADIUS, MAX_PARTICLE_RADIUS), Rand::randFloat(1.f, 10.f), 0.5);
		ps.addParticle(particle);
	}
	ps.update();
}

void ColorTrackingSoundApp::draw()
{
	gl::clear(Color(0.f, 0.f, 0.f));
	gl::color(Color::white());
	t.draw();
	// Draw the interface
	//ps.draw();
}


CINDER_APP_NATIVE(ColorTrackingSoundApp, RendererGl)
