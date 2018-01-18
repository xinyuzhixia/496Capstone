//
//  Camera.hpp
//  test
//
//  Created by Yuhan Wei on 2018-01-04.
//  Copyright © 2018 Yuhan Wei. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

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

#include "MotionDetector.hpp"
#include "PeopleDetector.hpp"

using namespace cv;
using namespace std;

enum CStatus{
    OFF,
    RUNNING,
    ON
};

class Camera{
  
    int m_CID;
    CStatus m_CStatus;
    string m_URL;
    bool m_FoundPeople;
    Ptr<MotionDetector> m_MDetector;
    Ptr<PeopleDetector> m_PDetector;
    
public:
    
    Camera(int val, string addr){
        m_CID = val;
        m_CStatus = OFF;
        m_URL = addr;
        m_FoundPeople = false;
        m_MDetector = new MotionDetector();
        m_PDetector = new PeopleDetector();
    }
    ~Camera();
    
    int GetCameraID(){return m_CID;}
    CStatus GetCameraStatus(){return m_CStatus;}
    bool GetFoundPeople(){return m_FoundPeople;}
    void SetCameraStatus(CStatus status) {m_CStatus = status;}
    
    bool TurnCameraOn();
    bool TurnCameraOff();
    
    int RunOccupancyDetection();
    int DisplayVideo();
    
};
#endif /* Camera_hpp */
