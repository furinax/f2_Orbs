#include "Tracker.h"

Tracker::Tracker()
{
	
}

Tracker::~Tracker()
{
	delete mBlobDetector;
	mImage.reset();
}

int Tracker::numBlobs()
{
	return mBlobs.size();
}

Vec2f Tracker::getBlobCenter(const int num)
{
	if (mBlobs.size() <= num )
		return getWindowCenter();
	return fromOcv(mBlobs[num].center * mScaleUp);
}

void Tracker::setup()
{
	try {
		mCapture = Capture(
			getWindowWidth() < WEBCAM_MAX_WIDTH ? getWindowWidth() : WEBCAM_MAX_WIDTH,
			getWindowHeight() < WEBCAM_MAX_HEIGHT ? getWindowHeight() : WEBCAM_MAX_HEIGHT );
		mCapture.start();
	}
	catch (...) {
		console() << "Failed to initialize capture" << std::endl;
	}

	mScaleDown = 2.5f;
	mScaleUp = mScaleDown;// *(static_cast<float>(getWindowWidth()) / static_cast<float>(mCapture.getWidth()));

	//this is the 2nd algorithm
	cv::SimpleBlobDetector::Params params;
	params.minThreshold = 50;
	params.maxThreshold = 255;
	params.thresholdStep = 5;

	params.minArea = 2; params.maxArea = 500;
	params.minConvexity = 0.3; params.maxConvexity = 1;
	params.minInertiaRatio = .01f;

	params.filterByConvexity = true;
	params.filterByArea = true;
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

		cv::resize(inputMat, inputMat, cv::Size( ((float)getWindowWidth()) / mScaleDown, ((float)getWindowHeight()) / mScaleDown));

		vector< cv::KeyPoint >  keyPoints;
		mBlobDetector->detect(inputMat, keyPoints);



		mBlobs.clear();
		mBlobs.reserve(keyPoints.size());
		for (int i = 0; i < keyPoints.size(); i++)
		{
			myBlob m;
			m.center = keyPoints[i].pt;
			m.radius = keyPoints[i].size;
			mBlobs.push_back(m);
		}

		if (mBlobs.size() > maxBlobs)
		{
			std::partial_sort(mBlobs.begin(), mBlobs.begin() + maxBlobs, mBlobs.end());
			mBlobs.resize(maxBlobs);
		}
	}
	else
	{
		console() << "WARNING: skipped a frame: " << getElapsedFrames() << endl;
	}
}

void Tracker::draw()
{
	if (mCaptureTex) {
		gl::draw(mCaptureTex);

		gl::color(Color::white());

		for (int i = 0; i < mBlobs.size(); i++)
		{
			Vec2f center = fromOcv(mBlobs[i].center)*mScaleUp;
			gl::begin(GL_POINTS);
			gl::vertex(center);
			gl::end();
			gl::lineWidth(1.f);
			gl::drawStrokedCircle(center, mBlobs[i].radius);
		}
	}
}