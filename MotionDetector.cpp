//
//  MotionDetector.cpp
//  test
//
//  Created by Yuhan Wei on 2018-01-03.
//  Copyright © 2018 Yuhan Wei. All rights reserved.
//
#include "MotionDetector.hpp"
const static int SENSITIVITY_VALUE = 40;
const static int BLUR_SIZE = 10;

MotionDetector::MotionDetector(int val){
    m_ID = val;
    m_bg = createBackgroundSubtractorMOG2(10, 16, false);
}
MotionDetector::~MotionDetector(){
    
}
void MotionDetector::BackgroundSubstraction(Mat &frame, Mat &foreground){
    Mat background;
    Mat GrayImage;
    cvtColor(frame, GrayImage, CV_BGR2GRAY);
    //m_bg->operator()(frame,fore);
    m_bg->apply(GrayImage, foreground);
    m_bg->getBackgroundImage(background);
    vector<vector<Point>> contours;
    medianBlur(foreground, foreground, 5);
    
    Mat dilateElement = getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2), cv::Point(-1, -1));
    morphologyEx(foreground, foreground, CV_MOP_OPEN, dilateElement);
    morphologyEx(foreground, foreground, CV_MOP_CLOSE, dilateElement);
    
    threshold(foreground, foreground, SENSITIVITY_VALUE, 255,THRESH_BINARY);
    //blur(foreground, foreground,Size(BLUR_SIZE, BLUR_SIZE));
   
    //dilate(foreground, foreground, dilateElement, cv::Point(-1, -1), 2);
    
    
    /*
    erode(foreground,foreground,cv::Mat());
    dilate(foreground,foreground,cv::Mat());
    findContours(foreground,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
    drawContours(frame,contours,-1,cv::Scalar(0,0,255),2);
    */
}

int MotionDetector::MotionDetecting(Mat frame1, Mat frame2, Mat &ThresholdImage){
    if (frame1.empty() || frame1.empty()) return 0;
    
    Mat GrayScaleImage1, GrayScaleImage2;
    Mat DifferenceImage, FirstThresholdImage;

    cvtColor( frame1, GrayScaleImage1, CV_BGR2GRAY );
    cvtColor( frame2, GrayScaleImage2, CV_BGR2GRAY );
    absdiff(GrayScaleImage1,GrayScaleImage2, DifferenceImage);
    threshold(DifferenceImage, FirstThresholdImage, SENSITIVITY_VALUE ,255, THRESH_BINARY);
    
    blur(FirstThresholdImage, FirstThresholdImage, Size(BLUR_SIZE, BLUR_SIZE));
    threshold(FirstThresholdImage, ThresholdImage, SENSITIVITY_VALUE ,255, THRESH_BINARY);
    
    return 0;
    
}

bool MotionDetector::TrackingMovement(Mat ThresholdImage, Mat &CameraFrame){
    bool MovementDetected;
    Mat temp;
    ThresholdImage.copyTo(temp);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Rect BoundingRectangle;
    RNG rng(12345);
    
    findContours(temp, contours,hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    if(contours.size()>0) MovementDetected = true;
    else MovementDetected = false;
    
    if(MovementDetected){
        drawContours(CameraFrame,contours,-1,cv::Scalar(0,0,255),2);
        
        for(auto it = contours.begin(); it!= contours.end(); it++){
            
            BoundingRectangle = boundingRect(*it);
            Point pt1, pt2;
            pt1.x = BoundingRectangle.x;
            pt1.y = BoundingRectangle.y;
            pt2.x = BoundingRectangle.x + BoundingRectangle.width;
            pt2.y = BoundingRectangle.y + BoundingRectangle.height;

           
            Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
            //rectangle( CameraFrame, pt1,pt2, color, 2, 8, 0 );
        }
       // vector<vector<Point>> largestContour;
       //largestContour.push_back(contours.at(contours.size() -1));
       //BoundingRectangle = boundingRect(largestContour.at(0));
        
        //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        //rectangle( CameraFrame, BoundingRectangle.tl(), BoundingRectangle.br(), color, 2, 8, 0 );
    }
    
    return MovementDetected;
}
