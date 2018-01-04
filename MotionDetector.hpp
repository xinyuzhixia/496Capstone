//
//  MotionDetector.hpp
//  test
//
//  Created by Yuhan Wei on 2018-01-03.
//  Copyright © 2018 Yuhan Wei. All rights reserved.
//
#ifndef MotionDetector_hpp
#define MotionDetector_hpp

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

class MotionDetector {
  
    int m_ID;
    Ptr<BackgroundSubtractor> m_bg;
    
public:
    MotionDetector(int val);
    ~MotionDetector();
    void BackgroundSubstraction(Mat &frame, Mat &foreground);
    int MotionDetecting(Mat frame1, Mat frame2, Mat &ThresholdImage);
    bool TrackingMovement(Mat ThresholdImage, Mat &CameraFrame);
    
    
    
};

#endif /* MotionDetector_hpp */
