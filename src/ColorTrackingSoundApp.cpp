#include "cinder/app/AppNative.h"

#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Surface.h"
#include "cinder/ImageIo.h"
#include "cinder/cairo/Cairo.h"
#include "cinder/Capture.h"
#include "cinder/params/Params.h"
#include "ParticleSystem.h"
#include "ParticleFactory.h"
#include "cinder/Rand.h"
#include "Tracker.h"
#include "Listener.h"

#include "CinderOpenCV.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace {
	ColorA Orange(1, .5, 0, 1.f);

}

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
	ParticleFactory pf;
	Tracker t;
	Listener list;
	Vec2f mMousePosition, mPrevPosition;
};

void ColorTrackingSoundApp::setup()
{
	gl::color(Color::black());
	setWindowSize(1280, 720);
	setFrameRate(30.f);
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
}

void ColorTrackingSoundApp::update()
{
	t.update();
	list.update();
	
	for (int i = 0; i < t.numBlobs(); i++)
	{
		pf.create(getElapsedSeconds(), t.getBlobCenter(i), list, ps);
	}
	ps.update(list, t.getBlobCenter(0));
}

void ColorTrackingSoundApp::draw()
{
	gl::clear(Color(0.f, 0.f, 0.f));
	gl::color(Color::white());
	t.draw();
	// Draw the interface
	//ps.draw(list, t.getBlobCenter(0));
}


CINDER_APP_NATIVE(ColorTrackingSoundApp, RendererGl)
