//
//  MotionDetector.cpp
//  test
//
//  Created by Yuhan Wei on 2018-01-03.
//  Copyright © 2018 Yuhan Wei. All rights reserved.
//
#include "MotionDetector.hpp"
#include "DBScan.hpp"
const static int SENSITIVITY_VALUE = 1;
const static int BLUR_SIZE = 10;
const static int CONTOUR_SIZE = 100;

struct Dist {
    bool operator()(const Point& a, const Point &b) {
        return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)) < 100;
    }
};

MotionDetector::MotionDetector(){
      m_bg = createBackgroundSubtractorMOG2(700, 20, true);
   // m_bg = createBackgroundSubtractorMOG().dynamicCast<BackgroundSubtractor>();
   // m_bg =new BackgroundSubtractorMOG();
    detected = 0;
}

MotionDetector::~MotionDetector(){
    
}

bool MotionDetector::BackgroundSubstraction_new(Mat &frame, Mat &foregroundImg,Mat &foregroundMask){
    
    Mat img;
    //Mat foregroundMask;
    Mat backgroundImage;
    
    if( foregroundMask.empty() ){
        foregroundMask.create(frame.size(), frame.type());
    }
    
    m_bg->apply(frame, foregroundMask, true ? -1 : 0);
    //Get background image
    m_bg->getBackgroundImage(backgroundImage);

    
    // smooth the mask to reduce noise in image
    GaussianBlur(foregroundMask, foregroundMask, Size(33,33), 5,5);
    
    // threshold mask to saturate at black and white values
    threshold(foregroundMask, foregroundMask, 15,255,THRESH_BINARY);
   // cv.drawContours(foregroundMask, contours, -1, (255),1)
    foregroundImg = Scalar::all(0);
    // Copy source image to foreground image only in area with white mask
    frame.copyTo(foregroundImg, foregroundMask);
    
    double area_frame = 0.0;
    return TrackingMovement (foregroundMask, frame, area_frame);
    
}

void MotionDetector::BackgroundSubstraction(Mat &frame, Mat &foreground){
    Mat background;
    Mat tempImage;
    Mat GrayImage;
    cvtColor(frame, GrayImage, CV_BGR2GRAY);
    //m_bg->operator()(frame,fore);
    m_bg->apply(GrayImage, foreground);
    
    /*m_bg->getBackgroundImage(background);
    vector<vector<Point>> contours;
    medianBlur(foreground, foreground, 5);
    
    Mat dilateElement = getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2), cv::Point(-1, -1));
    morphologyEx(foreground, foreground, CV_MOP_OPEN, dilateElement);
    morphologyEx(foreground, foreground, CV_MOP_CLOSE, dilateElement);*/
    
    //threshold(tempImage, foreground, SENSITIVITY_VALUE, 255,THRESH_BINARY);
    //blur(foreground, foreground,Size(BLUR_SIZE, BLUR_SIZE));
    //dilate(foreground, foreground, dilateElement, cv::Point(-1, -1), 2);
    
    
    /*
    erode(foreground,foreground,cv::Mat());
    dilate(foreground,foreground,cv::Mat());
    findContours(foreground,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
    drawContours(frame,contours,-1,cv::Scalar(0,0,255),2);
    */
    
}

void MotionDetector::MotionDetecting(Mat frame1, Mat frame2, Mat &ThresholdImage){
    bool MovementDetected;
    
    Mat GrayScaleImage1, GrayScaleImage2;
    Mat DifferenceImage, FirstThresholdImage;

    cvtColor( frame1, GrayScaleImage1, CV_BGR2GRAY );
    cvtColor( frame2, GrayScaleImage2, CV_BGR2GRAY );
    absdiff(GrayScaleImage1,GrayScaleImage2, DifferenceImage);
    threshold(DifferenceImage, FirstThresholdImage, SENSITIVITY_VALUE ,255, THRESH_BINARY);
    
    blur(FirstThresholdImage, FirstThresholdImage, Size(BLUR_SIZE, BLUR_SIZE));
    threshold(FirstThresholdImage, ThresholdImage, SENSITIVITY_VALUE ,255, THRESH_BINARY);
    
    
    
}

bool MotionDetector::TrackingMovement(Mat ThresholdImage, Mat &CameraFrame, double &final_area){
    bool MovementDetected;
    Mat temp;
    ThresholdImage.copyTo(temp);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Rect BoundingRectangle;
    RNG rng(12345);
    
    findContours(temp, contours,hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    
    if(contours.size()>0) {MovementDetected = true;
        //detected ++;
       //cout << "Detected Motion!" << endl;
    }
    else {
        MovementDetected = false;
        final_area = 0.0;
       // cout << "No Motion Found!" << endl;
    }
    
    Point max_center;
    size_t max_index;
    if(MovementDetected){
        
        double max_area = 0;
        // find the max contour
        vector<Point2f> mc( contours.size() );
        for(size_t i = 1; i < contours.size(); i++){
           
            Moments mo = moments(contours[i]);
            mc[i] = Point(mo.m10/mo.m00 , mo.m01/mo.m00);
        
            double area = contourArea(contours[i]);
            //cout << "area: " << area << " ";
            
            if(area >= max_area) {
                max_area = area;
                max_index = i;
                max_center = mc[i];
            }
            
            // remove contour if its area is smaller than CONTOUR_SIZE
            if(area < CONTOUR_SIZE) {
                contours.erase(contours.begin() + i);
                continue;
                
            }
        }
        
//        vector<int> labels;
//        int ncluster = partition(mc, labels, Dist());
//        cout << "Found cluster: " << ncluster  << " with points: " <<mc.size() << endl;

        if(max_area < CONTOUR_SIZE) {
            //detected --;
            //cout << "no motion found" << endl;
        }else{
            detected ++;
            // draw all contour
//
//            for(size_t i = 1; i < contours.size(); i++){
//
//                if ( i == max_index)
//                    circle( CameraFrame, max_center, 4, Scalar(0,0,255), -1, 8, 0 );
//                else
//                    circle( CameraFrame, mc[i], 4, Scalar(0,255,255), -1, 8, 0 );
//                //drawContours(CameraFrame,contours,(int) i,cv::Scalar(0,0,255),2);
//
//                BoundingRectangle = boundingRect(contours[i]);
//                Point pt1, pt2;
//                pt1.x = BoundingRectangle.x;
//                pt1.y = BoundingRectangle.y;
//                pt2.x = BoundingRectangle.x + BoundingRectangle.width;
//                pt2.y = BoundingRectangle.y + BoundingRectangle.height;
//
//
//                Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
//                rectangle(CameraFrame, pt1,pt2, color, 2, 8, 0 );
//            }
            //cout << "detected motion" << endl;
        }
        final_area = max_area;
       //cout << "max area: " << max_area <<endl;
       // vector<vector<Point>> largestContour;
       //largestContour.push_back(contours.at(contours.size() -1));
       //BoundingRectangle = boundingRect(largestContour.at(0));
        
        //Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        //rectangle( CameraFrame, BoundingRectangle.tl(), BoundingRectangle.br(), color, 2, 8, 0 );
    }
    
    return MovementDetected;
}
bool MotionDetector::TrackingMovement_withDB(Mat ThresholdImage, Mat &CameraFrame, double &final_area){
    bool MovementDetected;
    Mat temp;
    ThresholdImage.copyTo(temp);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Rect BoundingRectangle;
    RNG rng(12345);
    
    findContours(temp, contours,hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    
    if(contours.size()>0) {MovementDetected = true;
        //detected ++;
        //cout << "Detected Motion!" << endl;
    }
    else {
        MovementDetected = false;
        final_area = 0.0;
        // cout << "No Motion Found!" << endl;
    }
    
    Point max_center;
    size_t max_index;
    if(MovementDetected){
        
        double max_area = 0;
        // find the max contour
        vector<Rect> boxes;
        for(size_t i = 0; i < contours.size(); i++)
        {
            
        }
        vector<Point2f> mc( contours.size() );
        for(size_t i = 1; i < contours.size(); i++){
            
            Moments mo = moments(contours[i]);
            mc[i] = Point(mo.m10/mo.m00 , mo.m01/mo.m00);
            double area = contourArea(contours[i]);
            //cout << "area: " << area << " ";
            
            if(area >= max_area) {
                max_area = area;
                max_index = i;
                max_center = mc[i];
            }
            
            // remove contour if its area is smaller than CONTOUR_SIZE
            if(area < CONTOUR_SIZE) {
                contours.erase(contours.begin() + i);
                continue;
                
            }
            Rect r = boundingRect(contours[i]);
            boxes.push_back(r);
        
        }
        
        DBScan dbscan(boxes,30,2);
        dbscan.run();
        
        Mat grouped = Mat::zeros(temp.size(),CV_8UC3);
        vector<Scalar> colors;
        RNG rng(3);
        
        for(int i=0;i<=dbscan.C;i++)
        {
            colors.push_back(HSVtoRGBcvScalar(rng(255),255,255));
        }
        
        for(int i=0;i<dbscan.data.size();i++)
        {
            Scalar color;
            if(dbscan.labels[i]==-1)
            {
                color=Scalar(128,128,128);
            }else
            {
                int label=dbscan.labels[i];
                color=colors[label];
            }
            putText(CameraFrame,to_string(dbscan.labels[i]),dbscan.data[i].tl(),    FONT_HERSHEY_COMPLEX,.5,color,1);
            drawContours(CameraFrame,contours,i,color,-1);
        }
        
    }
        
    
    return MovementDetected;
}
