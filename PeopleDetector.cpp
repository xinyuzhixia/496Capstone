//
//  PeopleDetector.cpp
//  test
//
//  Created by Yiqun Cheng on 2018-01-04.
//  Copyright © 2018 Yiqun Cheng. All rights reserved.
//

#include "PeopleDetector.hpp"
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

PeopleDetector::PeopleDetector(){
    numofpeople = 0;
    return;
}

PeopleDetector::~PeopleDetector(){
}

int PeopleDetector::getNumofpeople(){
    return numofpeople;
}

void PeopleDetector::detectAndDisplay( Mat frame, CascadeClassifier test_cascade)
{
    string window_name = "Test_Face";
    std::vector<Rect> faces;
    Mat frame_gray;
    
    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    
    //-- Detect faces
    test_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    for( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
        Mat faceROI = frame_gray( faces[i] );
    }
    numofpeople = faces.size();
    //-- Show what you got
    imshow( window_name, frame );
    waitKey(10);
}

bool PeopleDetector::detectPeople( Mat frame ){
    CascadeClassifier test_cascade;
    string window_name = "Test_Face";
    imshow(window_name,frame);
    string test_cascade_name = "/Users/DaQunZi/Downloads/HS.xml";
    if (!test_cascade.load(test_cascade_name)){
        cout << "load error!" << endl;
        return -1;
    }
    detectAndDisplay(frame, test_cascade);
    //-- Show what you got
    imshow( window_name, frame );
    waitKey(10);
    if (getNumofpeople() > 0){
        return true;
    }
    else{
        return false;
    }
}