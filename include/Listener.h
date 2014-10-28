#pragma once

#include "cinder/app/AppNative.h"

#include "cinder/audio/MonitorNode.h"
#include "cinder/audio/Utilities.h"
#include "cinder/Vector.h"

class Listener
{
public:
	Listener();
	~Listener();
	void setup();
	void update();
	float getVolume();

	ci::audio::InputDeviceNodeRef		mInputDeviceNode;
	ci::audio::MonitorSpectralNodeRef	mMonitorSpectralNode;
	std::vector<float>					mMagSpectrum;
};