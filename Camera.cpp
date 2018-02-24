//
//  Camera.cpp
//  test
//
//  Created by Yuhan Wei on 2018-01-04.
//  Copyright © 2018 Yuhan Wei. All rights reserved.
//
#include <time.h>
#include <unistd.h>
#include "Camera.hpp"


Camera::~Camera(){
    
}
bool Camera::AdjustCameraAngle(int rotate){
   
    string addr = m_URL;
    size_t pos = addr.find("videostream.cgi?");
    size_t username_pos = addr.find("loginuse=");
    size_t mid = addr.find("&");
    size_t password_pos = addr.find("loginpas=");
    
    string ip = addr.substr(0, pos);
    string username = addr.substr(username_pos, mid - username_pos);
    string password = addr.substr(password_pos);
    
    
    string command = ip + "decoder_control.cgi?" + username + "\\&" + password + "\\&command=" + to_string(rotate) + "\\&onestep=0";
    string op = string("curl -0 ").append(command);
    system(op.c_str());
    // stop
    // rotate + 1
    sleep(1);
    command = ip + "decoder_control.cgi?" + username + "\\&" + password + "\\&command=" + to_string(rotate + 1) + "\\&onestep=0";
    op = string("curl -0 ").append(command);
    system(op.c_str());
    
    
    return true;
}


int Camera::RunOccupancyDetection(int Processtime, bool Display ){
    
    VideoCapture cap;
    bool res = cap.open(m_URL);
    if (!res)  // if not success, exit program
    {
        cout << "Cannot open the camera" << endl;
        return -2;
    }
    int Frame_interval = 30;
    
    int timeLeft = Processtime;
    time_t end, timeTaken;
    time_t start = time(0);
    
    while(timeLeft > 0){
       
        Mat frame1, ThresholdImage;
        // Capture frame-by-frame
        cap >> frame1;
        
        if (frame1.empty()) break;
       
        // do motion detection first
        Mat foregroundImg;
        Mat foregroundMask;
        
       if (m_MDetector->BackgroundSubstraction_new(frame1, foregroundImg, foregroundMask)){
           //count_motion ++;
            // display
           if (Display){
               putText(frame1, " Detected Motion ! ", cvPoint(30,30),
                       FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);}

            m_PeopleCount = m_PDetector->DnnDetector(frame1);
           if(m_PeopleCount > 0) m_FoundPeople = true;
           else m_FoundPeople = false;
           
            if (Display){
                putText(frame1, " Detected " + to_string(m_PeopleCount) + " People ! ", cvPoint(30,70),
                        FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
            }
           
       }else{
           if(Display){
           putText(frame1, " Does not detect Motion ! ", cvPoint(30,30),
                   FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);}
           m_FoundPeople = false;
       }
        if(Display){
            
            imshow("foreground mask", frame1);
            waitKey(10);
            if (waitKey(30) == 27) {//wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
                cout << "esc key is pressed by user" << endl;
                break;
            }
        }
        end = time(0);
        timeTaken = end - start;
        timeLeft = Processtime - timeTaken;
    }
    
    destroyAllWindows();
    cap.release();

    return 0;
}


int Camera::DisplayVideo(){
    
    // should move to Room class
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
