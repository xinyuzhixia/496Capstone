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

const static string DEFAULTCLASSIFIER = "/Users/Yuhan/Documents/opencv/project/test/HS.xml";

PeopleDetector::PeopleDetector(){
    if (!m_Cascade.load(DEFAULTCLASSIFIER)){
        cout << "XML file load error!" << endl;
    }
    
    m_numofpeople = 0;
}

PeopleDetector::~PeopleDetector(){
}

int PeopleDetector::GetNumofpeople(){
    return m_numofpeople;
}

bool PeopleDetector::PeopleDetecting( Mat &frame ){
    //cout << "invoke people " << endl;
    putText(frame, " Running People Detector ! ", cvPoint(30,50), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
    
    std::vector<Rect> faces;
    Mat frame_gray;
    
    cvtColor(frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    
    //-- Detect faces
    m_Cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(100, 100) );
   
    for( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
        Mat faceROI = frame_gray( faces[i] );
    }
    
    
    //-- Show what you got
    //imshow( window_name, frame );
    //waitKey(10);
    if (faces.size() > 0){
        return true;
    }
    else{
        return false;
    }
}
