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
	float getVolume() const;
	float getBinVolume(const int bin) const;
	int getBinForFrequency(const int freq) const;

	ci::audio::InputDeviceNodeRef		mInputDeviceNode;
	ci::audio::MonitorSpectralNodeRef	mMonitorSpectralNode;
	std::vector<float>					mMagSpectrum;
	float mScale=5.f;
};