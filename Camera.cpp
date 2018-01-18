//
//  Camera.cpp
//  test
//
//  Created by Yuhan Wei on 2018-01-04.
//  Copyright © 2018 Yuhan Wei. All rights reserved.
//

#include "Camera.hpp"

bool Camera::TurnCameraOn(){
    // TODO
    SetCameraStatus(ON);
    return true;
}
bool Camera::TurnCameraOff(){
    //TODO
    SetCameraStatus(OFF);
    return true;
}

int Camera::RunOccupancyDetection(){
    if(m_CStatus == OFF){
        return -1;
    }
    
    VideoCapture cap;
    bool res = cap.open(m_URL);
    if (!res)  // if not success, exit program
    {
        cout << "Cannot open the video cam" << endl;
        return -2;
    }
    
    SetCameraStatus(RUNNING);
    while(1){
        
        Mat frame1, frame2, ThresholdImage;
        // Capture frame-by-frame
        cap >> frame1;
        cap >> frame2;
        if (frame1.empty() || frame2.empty()) break;
        
        // do motion detection first
       // if (m_MDetector->MotionDetecting(frame1, frame2, ThresholdImage) && m_PDetector->PeopleDetecting(frame1)){
            // if found motion run people detector
           // m_FoundPeople = true;
       // }else{
           // m_FoundPeople = false;
      //  }
        
    }
    
    // When everything done, release the video capture object
    cap.release();

    return 0;
    
}

int Camera::DisplayVideo(){
    
    // should move to Room class
    if(GetCameraStatus() == OFF){
        return -1;
    }
    VideoCapture cap;
    bool res = cap.open(m_URL);
    if (!cap.isOpened())  // if not success, exit program
    {
        cout << "Cannot open the video cam" << endl;
        return -2;
    }
    
    while(1){
        
        Mat frame;
        // Capture frame-by-frame
        cap >> frame;
        
        // If the frame is empty, break immediately
        if (frame.empty())
            break;
        
        // Display the resulting frame
        imshow( "Video", frame );
        
        // Press  ESC on keyboard to exit
        char c=(char)waitKey(25);
        if(c==27)
            break;
    }
    
    // When everything done, release the video capture object
    cap.release();
    
    // Closes all the frames
    destroyAllWindows();
    
    
    return true;
}
