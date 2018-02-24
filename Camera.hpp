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
#include "Pedestrian.h"

using namespace cv;
using namespace std;

class Camera{
  
    int m_CID;
    string m_URL;
    bool m_FoundPeople;
    int m_PeopleCount;
    Ptr<MotionDetector> m_MDetector;
    Ptr<PeopleDetector> m_PDetector;
    
public:
    
    Camera(int val, string addr){
        m_CID = val;
        m_URL = addr;
        m_FoundPeople = false;
        m_PeopleCount = 0;
        m_MDetector = new MotionDetector();
        m_PDetector = new PeopleDetector();
    }
    ~Camera();
    
    int GetCameraID(){return m_CID;}
    bool GetOccupancyStatus(){return m_FoundPeople;}
    int GetPeopleCount(){return m_PeopleCount;}
    bool AdjustCameraAngle(int command);
    int RunOccupancyDetection(int Processtime, bool Display);
    int DisplayVideo();
    
};
#endif /* Camera_hpp */
