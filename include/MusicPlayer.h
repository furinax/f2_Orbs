#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/audio/Source.h"
#include "cinder/audio/Context.h"
#include "cinder/audio/GainNode.h"
#include "cinder/audio/SamplePlayerNode.h"

class MusicPlayer
{
public:
	MusicPlayer();
	void start();
	~MusicPlayer();
	std::shared_ptr<ci::audio::FilePlayerNode> mFilePlayer;
	bool mIsStarted = false;
	ci::audio::GainNodeRef				mGain;
};