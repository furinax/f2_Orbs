#include "Listener.h"

using namespace ci;
using namespace ci::app;

Listener::Listener()
{

}

Listener::~Listener()
{
	//mMonitorSpectralNode->disable();
	//mInputDeviceNode->disable();
	//audio::Context::master()->disconnectAllNodes();
}

void Listener::setup()
{
	auto ctx = audio::Context::master();
	
	// The InputDeviceNode is platform-specific, so you create it using a special method on the Context:
	mInputDeviceNode = ctx->createInputDeviceNode();

	// By providing an FFT size double that of the window size, we 'zero-pad' the analysis data, which gives
	// an increase in resolution of the resulting spectrum data.
	auto monitorFormat = audio::MonitorSpectralNode::Format().fftSize(2048).windowSize(1024);
	mMonitorSpectralNode = ctx->makeNode(new audio::MonitorSpectralNode(monitorFormat));

	mInputDeviceNode >> mMonitorSpectralNode;

	// InputDeviceNode (and all InputNode subclasses) need to be enabled()'s to process audio. So does the Context:
	mInputDeviceNode->enable();
	ctx->enable();

	//getWindow()->setTitle(mInputDeviceNode->getDevice()->getName());
}

void Listener::update()
{
	mMagSpectrum = mMonitorSpectralNode->getMagSpectrum();

//	size_t bin = 15;
//	float freq = mMonitorSpectralNode->getFreqForBin(bin);
//	float mag = audio::linearToDecibel(mMagSpectrum[bin]);
}

float Listener::getVolume() const
{
	return ci::constrain( mScale * mMonitorSpectralNode->getVolume(), 0.f, 1.f );
}

float Listener::getBinVolume(const int bin) const
{

	return audio::linearToDecibel(mMagSpectrum[bin]);
}

int Listener::getBinForFrequency(const int freq) const
//binary search to find the frequency
{

	int lowerBound = 0, upperBound = mMonitorSpectralNode->getFftSize();
	while (lowerBound < upperBound)
	{
		float pivot = (upperBound - lowerBound) / 2 + lowerBound;
		float check= mMonitorSpectralNode->getFreqForBin(pivot);
		if (check < freq)
		{
			lowerBound = pivot + 1;
		}
		else if (check > freq)
		{
			upperBound = pivot - 1;
		}
		else if (check == freq)
			return pivot;
	}
	if (upperBound < 0)
		return 0;
	return upperBound;
}