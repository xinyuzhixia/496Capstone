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
#include <opencv2/bgsegm.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

class MotionDetector {
  
    Ptr<BackgroundSubtractor> m_bg;
    int detected;
    
public:
    MotionDetector();
    ~MotionDetector();
    void BackgroundSubstraction(Mat &frame, Mat &foreground);
    void BackgroundSubstraction_new(Mat &frame, Mat &foregroundImg, Mat &foregroundMask);
    void MotionDetecting(Mat frame1, Mat frame2, Mat &ThresholdImage);
    bool TrackingMovement(Mat ThresholdImage, Mat &CameraFrame, double &max_area);
    int Getdetected(){return detected;}
    
    
};

#endif /* MotionDetector_hpp */
