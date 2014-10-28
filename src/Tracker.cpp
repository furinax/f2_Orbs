#include "Tracker.h"

Tracker::Tracker()
{
	
}

Tracker::~Tracker()
{
	delete mBlobDetector;
	mImage.reset();
}

void Tracker::setup()
{
	try {
		mCapture = Capture(getWindowWidth(), getWindowHeight());
		mCapture.start();
	}
	catch (...) {
		console() << "Failed to initialize capture" << std::endl;
	}

	mScaling = 2.5f;

	//this is the 2nd algorithm
	cv::SimpleBlobDetector::Params params;
	params.minThreshold = 5;
	params.maxThreshold = 255;
	params.thresholdStep = 5;

	params.minArea = 2;
	params.minConvexity = 0.3;
	params.minInertiaRatio = 0.01;

	params.maxArea = 500;
	params.maxConvexity = 10;

	params.filterByColor = false;
	params.filterByCircularity = false;
	
	mBlobDetector = new cv::SimpleBlobDetector(params);
	mBlobDetector->create("SimpleBlob");
}

void Tracker::mouseDown(Vec2i& mousePos)
{

}

void Tracker::update()
{
	if (mCapture && mCapture.checkNewFrame()) {
		mImage = mCapture.getSurface();
		mCaptureTex = gl::Texture(mImage);

		cv::Mat inputMat(toOcv(mImage));

		cv::resize(inputMat, inputMat, cv::Size(getWindowWidth() / mScaling, getWindowHeight() / mScaling));

		vector< cv::KeyPoint >  keyPoints;
		mBlobDetector->detect(inputMat, keyPoints);

		mCenters = vector<cv::Point2f>(keyPoints.size());
		mRadius = vector<float>(keyPoints.size());
		for (int i = 0; i < keyPoints.size(); i++)
		{
			mCenters.push_back(keyPoints[i].pt);
			mRadius.push_back(keyPoints[i].size);
		}
	}
	else
	{
		console() << "WARNING: skipped a frame";
	}
}

void Tracker::draw()
{
	if (mCaptureTex) {
		gl::draw(mCaptureTex);

		gl::color(Color::white());

		for (int i = 0; i < mCenters.size(); i++)
		{
			Vec2f center = fromOcv(mCenters[i])*mScaling;
			gl::begin(GL_POINTS);
			gl::vertex(center);
			gl::end();

			gl::drawStrokedCircle(center, mRadius[i] * mScaling);
		}
	}
}