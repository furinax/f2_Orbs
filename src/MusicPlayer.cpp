#include "MusicPlayer.h"

using namespace ci;
using namespace ci::app;

MusicPlayer::MusicPlayer()
{
	
}

void MusicPlayer::start()
{
	audio::SourceFileRef sourceFile = audio::load(loadFile("../assets/sapphire.mp3"), 48000 );
	auto ctx = audio::Context::master();
	mFilePlayer = ctx->makeNode(new audio::FilePlayerNode(sourceFile));

	// add a Gain to reduce the volume
	mGain = ctx->makeNode(new audio::GainNode(.7f));

	// connect and enable the Context
	mFilePlayer >> mGain >> ctx->getOutput();
	ctx->enable();

	mFilePlayer->start();
	mIsStarted = true;
}

MusicPlayer::~MusicPlayer()
{
	if ( mIsStarted )
		mFilePlayer->stop();
}