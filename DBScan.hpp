//
//  DBScan.hpp
//  test
//
//  Created by Yuhan Wei on 2018-02-01.
//  Copyright © 2018 Yuhan Wei. All rights reserved.
//

#ifndef DBScan_hpp
#define DBScan_hpp

#include <stdio.h>
#include "opencv2/opencv.hpp"
#include <vector>
#include <map>
#include <sstream>

using namespace cv;
using namespace std;
template <class T>

inline std::string to_string (const T& t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

class DBScan
{
public:
    std::map<int, int> labels;
    vector<Rect>& data;
    int C;
    double eps;
    int mnpts;
    double* dp;
    //memoization table in case of complex dist functions
    #define DP(i,j) dp[(data.size()*i)+j]
    DBScan(vector<Rect>& _data,double _eps,int _mnpts);
    void run();
    void expandCluster(int p,vector<int> neighbours);
    bool isVisited(int i);
    vector<int> regionQuery(int p);
    double dist2d(Point2d a,Point2d b);
    double distanceFunc(int ai,int bi);
    vector<vector<Rect> > getGroups();
    
};

    cv::Scalar HSVtoRGBcvScalar(int H, int S, int V) ;
#endif /* DBScan_hpp */
