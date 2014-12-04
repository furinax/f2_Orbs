#include "Tracker.h"

Tracker::Tracker()
{
	mOffset = Vec2f::zero();
	mScaleUpAdjust = Vec2f(1.1f, 1.1f);
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
	/* old way
	if (mBlobs.size() <= num )
		return getWindowCenter();
	return adjustScale(fromOcv(mBlobs[num].center)* mScaleUp) + mOffset;*/
	if (mInterpolators.find(num) == mInterpolators.end())
		return Vec2f::zero();
	return mInterpolators.at(num).getFrontPoint();
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
	mScaleUp = Vec2f(mScaleDown, mScaleDown);

	//this is the 2nd algorithm
	cv::SimpleBlobDetector::Params params;
	params.minThreshold = 5;
	params.maxThreshold = 255;
	params.thresholdStep = 5;

	params.minArea = 3; params.maxArea = 500;
	params.minConvexity = 0.1f; params.maxConvexity = 5.f;
	//params.minInertiaRatio = .001f; params.maxInertiaRatio = 1.f;

	params.filterByConvexity = false;
	params.filterByArea = true;
	params.filterByColor = false;
	params.filterByCircularity = false;
	params.filterByInertia = false;
	
	mBlobDetector = new cv::SimpleBlobDetector(params);
	mBlobDetector->create("SimpleBlob");

	Interpolator i0; i0.d_color = Color(1.f, 0.f, 0.f);
	Interpolator i1; i1.d_color = Color(0.5f, 1.f, .5f);

	mInterpolators.insert(std::pair<int, Interpolator>(0, i0));
	mInterpolators.insert(std::pair<int, Interpolator>(1, i1));

}

Vec2f Tracker::adjustScale(Vec2f initialPoint)
{
	return getWindowCenter() + (initialPoint - getWindowCenter()) * mScaleUpAdjust;
}

void Tracker::mouseDown(Vec2f& mousePos)
{
	mOffset = mousePos - getWindowCenter();
}

void Tracker::update()
{
	if (mCapture && mCapture.checkNewFrame()) {
		mImage = mCapture.getSurface();
		mCaptureTex = gl::Texture(mImage);

		cv::Mat inputMat(toOcv(mImage));
		
		cv::cvtColor(inputMat, inputMat, CV_BGR2GRAY);
		cv::resize(inputMat, inputMat, cv::Size(((float)getWindowWidth()) / mScaleDown, ((float)getWindowHeight()) / mScaleDown));
		
		std::vector< cv::KeyPoint >  keyPoints;
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

		if (mBlobs.size() == 2)
		{
			if (mInterpolators[0].getDist(adjustScale(fromOcv(mBlobs[0].center)*mScaleUp)) < mInterpolators[1].getDist(adjustScale(fromOcv(mBlobs[0].center)*mScaleUp)))
			{
				mInterpolators[0].addPoint(adjustScale(fromOcv(mBlobs[0].center)*mScaleUp));
				mInterpolators[0].d_interpolationCount = 0;
				mInterpolators[1].addPoint(adjustScale(fromOcv(mBlobs[1].center)*mScaleUp));
				mInterpolators[1].d_interpolationCount = 0;
			}
			else
			{
				mInterpolators[0].addPoint(adjustScale(fromOcv(mBlobs[1].center)*mScaleUp));
				mInterpolators[0].d_interpolationCount = 0;
				mInterpolators[1].addPoint(adjustScale(fromOcv(mBlobs[0].center)*mScaleUp));
				mInterpolators[1].d_interpolationCount = 0;
			}
		}
		else if (mBlobs.size() == 1)
		{
			if (mInterpolators[0].d_interpolationCount == 0
				|| mInterpolators[0].getDist(adjustScale(fromOcv(mBlobs[0].center)*mScaleUp)) < mInterpolators[1].getDist(adjustScale(fromOcv(mBlobs[0].center)*mScaleUp)))
			{
				mInterpolators[0].addPoint(adjustScale(fromOcv(mBlobs[0].center)*mScaleUp));
				mInterpolators[0].d_interpolationCount = 0;
				mInterpolators[1].getNextPoint();
			}
			else
			{
				mInterpolators[0].getNextPoint();
				mInterpolators[1].addPoint(adjustScale(fromOcv(mBlobs[0].center)*mScaleUp));
				mInterpolators[1].d_interpolationCount = 0;
			}
		}
		else
		{
			mInterpolators[0].getNextPoint();
			mInterpolators[1].getNextPoint();
		}
	}
	else
	{
		console() << "WARNING: skipped a frame: " << getElapsedFrames() << std::endl;
	}
}

void Tracker::draw()
{
	if (mCaptureTex) {
		gl::pushMatrices();
		gl::translate(mOffset);
		gl::draw(mCaptureTex);

		gl::color(Color::white());

		for (int i = 0; i < mBlobs.size(); i++)
		{
			Vec2f center = adjustScale(fromOcv(mBlobs[i].center)*mScaleUp);
			glBegin(GL_POINTS);
			glVertex2f(center);
			glEnd();
			glLineWidth(1.f);
			gl::drawStrokedCircle(center, mBlobs[i].radius);
		}

		//mInterpolators.begin()->second.draw();
		for (std::map<int, Interpolator>::iterator itor = mInterpolators.begin(); itor != mInterpolators.end(); itor++ )
			itor->second.draw();

		gl::popMatrices();
		
		//draw a circle at the center to show offset
		gl::color(1.f, 0, 0);
		glBegin(GL_POINTS);
		glVertex2f(mOffset + getWindowCenter());
		glEnd();
		gl::drawStrokedCircle(mOffset + getWindowCenter(), 5.f);
	}
}