//
//  PeopleDetector.hpp
//  test
//
//  Created by Yiqun Cheng on 2018-01-04.
//  Copyright © 2018 Yiqun Cheng. All rights reserved.
//

#ifndef PeopleDetector_hpp
#define PeopleDetector_hpp

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class PeopleDetector{
    
    int m_numofpeople;
    CascadeClassifier m_Cascade;
public:
    PeopleDetector();
    ~PeopleDetector();
    int GetNumofpeople();
    bool PeopleDetecting( Mat &frame );
};


#endif /* PeopleDetector_hpp */
