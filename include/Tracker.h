#pragma once

#include "cinder/Vector.h"
#include "cinder/app/AppNative.h"

#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Surface.h"
#include "cinder/ImageIo.h"
#include "cinder/cairo/Cairo.h"
#include "cinder/Capture.h"
#include "CinderOpenCV.h"
#include "Interpolator.h"
#include <map>

using namespace ci;
using namespace ci::app;

struct myBlob {
	cv::Point2f center;
	float radius;
	bool operator<(myBlob other) const
	{
		return radius > other.radius;
	}
};

class Tracker
{
public:
	Tracker();
	~Tracker();
	void setup();
	void update();
	void draw();
	void mouseDown(Vec2f &mousePos);
	int numBlobs();
	Vec2f getBlobCenter(const int num);
	Vec2f adjustScale(Vec2f initialPoint);

	Surface8u   mImage;
	Capture     mCapture;
	gl::Texture mCaptureTex;
	std::vector<myBlob> mBlobs;
	int mMaxCenters;
	float mScaleDown;
	Vec2f mScaleUp, mScaleUpAdjust;
	cv::SimpleBlobDetector *mBlobDetector;
	std::map<int, Interpolator> mInterpolators;

	const int WEBCAM_MAX_WIDTH = 1280, WEBCAM_MAX_HEIGHT = 720;
	int maxBlobs = 2;
	Vec2i mOffset;
};