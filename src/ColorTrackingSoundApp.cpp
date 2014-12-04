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
#include "cinder/params/Params.h"

#include "CinderOpenCV.h"

using namespace ci;
using namespace ci::app;

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
	void keyDown(KeyEvent event);

	void update();
	void draw();

	std::vector<ParticleSystem> pss;
	ParticleFactory pf;
	Tracker t;
	Listener list;
	Vec2f mMousePosition, mPrevPosition;
	params::InterfaceGl		mParams;
	bool mParamsVisible = false;
	bool mTrackerVisible = true;
	bool mParticlesVisible = true;
	int mTotalParticles = 0;
};

void ColorTrackingSoundApp::setup()
{
	gl::color(Color::black());
	setWindowSize(1920, 1080);
	//setWindowSize(1280, 720);
	setFrameRate(30.f);
	mMousePosition = getWindowCenter();
	mPrevPosition = getWindowCenter();

	t.setup();
	ParticleSystem ps1, ps2;
	ps2.mOrientation = -1;
	ps1.setup(); ps2.setup();
	pss.push_back(ps1);
	pss.push_back(ps2);
	list.setup();

	// Setup the parameters
	mParams = params::InterfaceGl("Parameters", Vec2i(200, 150));
	mParams.addParam("Particle ID", &pf.d_particleToCreate, "min=0 max=13 keyIncr=+ keyDecr=-");
	mParams.addParam("CenterX", &t.mOffset.x, "min=-200 max=200 step=5 keyIncr=f keyDecr=s");
	mParams.addParam("CenterY", &t.mOffset.y, "min=-200 max=200 step=5 keyIncr=a keyDecr=e");
	mParams.addParam("mScaleUpX", &t.mScaleUpAdjust.x, "min=0.00 max=2.00 step=0.05 keyIncr=r keyDecr=w");
	mParams.addParam("mScaleUpY", &t.mScaleUpAdjust.y, "min=0.00 max=2.00 step=0.05 keyIncr=t keyDecr=g");
	mParams.addParam("Tracker visible?", &mTrackerVisible, "");
	mParams.addParam("Draw particles?", &mParticlesVisible, "");
	mParams.addSeparator();
	mParams.addParam("Total particles", &mTotalParticles, "readonly=1");
	mParams.maximize();
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

void ColorTrackingSoundApp::keyDown(KeyEvent event)
{
	switch (event.getChar())
	{
	case 'x':
	mParamsVisible = !mParamsVisible;
	break;
	case 'd': //reset to default
		t.mOffset = Vec2f::zero();
		t.mScaleUpAdjust = Vec2f(1.f, 1.f);
	break;
	}
}

void ColorTrackingSoundApp::update()
{
	int particleCount = 0;
	t.update();
	list.update();
	console() << list.getVolume() << std::endl;
	for (int i = 0;i < pss.size(); i++)
	{
		if (t.getBlobCenter(i) != Vec2f::zero() )
			pf.create(getElapsedSeconds(), t.getBlobCenter(i), list, pss[i]);
		pss[i].update(list, t.getBlobCenter(i));
		particleCount += pss[i].mParticles.size();
	}
	mTotalParticles = particleCount;
}

void ColorTrackingSoundApp::draw()
{
	gl::clear(Color(0.f, 0.f, 0.f));
	gl::color(Color::white());
	if (mTrackerVisible)
		t.draw();
	if (mParamsVisible)
		mParams.draw();

	if (mParticlesVisible)
	{
		for (int i = 0; i < pss.size(); i++)
			pss[i].draw(list, t.getBlobCenter(i));
	}
}


CINDER_APP_NATIVE(ColorTrackingSoundApp, RendererGl)
