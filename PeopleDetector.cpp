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
using namespace dnn;

const static string DEFAULTCLASSIFIER = "/Users/Yuhan/Documents/opencv/project/test/HS.xml";
const static string protoPath = "/Users/Yuhan/Documents/opencv/real-time-object-detection/MobileNetSSD_deploy.prototxt.txt";
const static string modelPath = "/Users/Yuhan/Documents/opencv/real-time-object-detection/MobileNetSSD_deploy.caffemodel";

const char* classNames[] = {
    "__background__",
    "aeroplane", "bicycle", "bird", "boat",
    "bottle", "bus", "car", "cat", "chair",
    "cow", "diningtable", "dog", "horse",
    "motorbike", "person", "pottedplant",
    "sheep", "sofa", "train", "tvmonitor"
};
const size_t inWidth = 300;
const size_t inHeight = 300;
const float inScaleFactor = 0.007843f;
const float meanVal = 127.5;
const float confidenceThreshold = 0.5;

PeopleDetector::PeopleDetector(){
//    if (!m_Cascade.load(DEFAULTCLASSIFIER)){
//        cout << "XML file load error!" << endl;
//    }
    
    net = readNetFromCaffe(protoPath, modelPath);
}

PeopleDetector::~PeopleDetector(){
}

int PeopleDetector:: DnnDetector(Mat &frame){
    int people_count = 0;
    
    if (frame.channels() == 4)
        cvtColor(frame, frame, COLOR_BGRA2BGR);
    
    //! [Prepare blob]
    Mat inputBlob = blobFromImage(frame, inScaleFactor,
                                  Size(inWidth, inHeight),
                                  Scalar(meanVal, meanVal, meanVal),
                                  false, false); //Convert Mat to batch of images
    //! [Prepare blob]
    
    //! [Set input blob]
    net.setInput(inputBlob); //set the network input
    //! [Set input blob]
    
    //! [Make forward pass]
    Mat detection = net.forward(); //compute output
    //! [Make forward pass]
    
    vector<double> layersTimings;
    double freq = getTickFrequency() / 1000;
    double time = net.getPerfProfile(layersTimings) / freq;
    
    Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
    
    for(int i = 0; i < detectionMat.rows; i++)
    {
        float confidence = detectionMat.at<float>(i, 2);
        
        if(confidence > confidenceThreshold)
        {
            size_t objectClass = (size_t)(detectionMat.at<float>(i, 1));
            
            int left = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
            int top = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
            int right = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
            int bottom = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);
            
            
            String label = format("%s: %.2f", classNames[objectClass], confidence);
            if (label.find("person") != std::string::npos){
                people_count ++;
            }else continue;
            rectangle(frame, Point(left, top), Point(right, bottom), Scalar(0, 255, 0));
            int baseLine = 0;
            Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
            top = max(top, labelSize.height);
            rectangle(frame, Point(left, top - labelSize.height),
                      Point(left + labelSize.width, top + baseLine),
                      Scalar(255, 255, 255), FILLED);
            putText(frame, label, Point(left, top),
                    FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0));
        }
    }
    
    return people_count;

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

void Hog_detectAndDraw(const HOGDescriptor &hog, Mat &img)
{
    vector<Rect> found, found_filtered;
    
    // Run the detector with default parameters. to get a higher hit-rate
    // (and more false alarms, respectively), decrease the hitThreshold and
    // groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
    hog.detectMultiScale(img, found, 0, Size(4,4), Size(8,8), 1.05);
    
    
    for(size_t i = 0; i < found.size(); i++ )
    {
        Rect r = found[i];
        
        size_t j;
        // Do not add small detections inside a bigger detection.
        for ( j = 0; j < found.size(); j++ )
            if ( j != i && (r & found[j]) == r )
                break;
        
        if ( j == found.size() )
            found_filtered.push_back(r);
    }
    
    for (size_t i = 0; i < found_filtered.size(); i++)
    {
        Rect r = found_filtered[i];
        
        // The HOG detector returns slightly larger rectangles than the real objects,
        // so we slightly shrink the rectangles to get a nicer output.
        r.x += cvRound(r.width*0.1);
        r.width = cvRound(r.width*0.8);
        r.y += cvRound(r.height*0.07);
        r.height = cvRound(r.height*0.8);
        rectangle(img, r.tl(), r.br(), cv::Scalar(0,255,0), 3);
    }
    
    //imshow("people detector", img);
    //waitKey(10);
    
}
