#include "mainwindow.h"
#include <QApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/video/tracking.hpp"

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <ctime>
#include "room.h"
#include "common.h"
using namespace std;
using namespace cv;
std::vector<thread> Allthread;
std::vector <room>Allroom;

int main(int argc, char *argv[])
{/*
    // prepare video input
    VideoCapture cap("/Users/Nancy/Documents/496/testvideo/afterMotionDetection.avi");

    // prepare video output
    VideoWriter outputVideo;

    outputVideo.open("video4.wmv", CV_FOURCC('W', 'M', 'V', '2'), cap.get(CV_CAP_PROP_FPS), Size(640, 480), true);

    // prepare cascadeClassifier
    CascadeClassifier detectorBody;
    CascadeClassifier detectorUpper;
    // !! Put your cascade or opencv cascede into project folder !!
   string cascadeName1 = "/Users/Nancy/Documents/496/cascadG.xml";
   // string cascadeName2 = "/Users/Nancy/Documents/opencv-3.3.1/data/haarcascades/haarcascade_upperbody.xml";

    // Load cascade into CascadeClassifier
    //bool loaded1 = detectorBody.load(cascadeName1);
    bool loaded3 = detectorUpper.load(cascadeName1);

    int framecount = 0,occupycount = 0,falsedetc = 0;



    // Basic video input loop
    for (;;)
    {

        bool Is = cap.grab();
        if (Is == false) {

            cout << "Video Capture Fail" << endl;
            break;
        }
        else {
            // Just for measure time
            const clock_t begin_time = clock();
            framecount++;
            // Store results in these 2 vectors
            vector<Rect> human;
            vector<Rect> upperBody;

            // prepare 2 Mat container
            Mat img;
            Mat original;

            // capture frame from video file
            cap.retrieve(img, CV_CAP_OPENNI_BGR_IMAGE);
            // Resize image if you want with same size as your VideoWriter
            resize(img, img, Size(640, 480));
            // Store original colored image
            img.copyTo(original);
            // color to gray image
            cvtColor(img, img, CV_BGR2GRAY);

            // detect people, more remarks in performace section
            //detectorBody.detectMultiScale(img, human, 1.1, 2, 0 | 1, Size(40,70), Size(80, 300));
            detectorUpper.detectMultiScale(img, upperBody, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(80,80));



            // Draw results from detectorBody into original colored image



            // Draw results from detectorUpper into original colored image
            if (upperBody.size() > 0) {
                 occupycount++;
                for (int gg = 0; gg < upperBody.size(); gg++) {
                    falsedetc++;
                    rectangle(original, upperBody[gg].tl(), upperBody[gg].br(),  Scalar(255,0,0), 2, 8, 0);

                }
            }
            // measure time as current - begin_time
            clock_t diff = clock() - begin_time;
            // convert time into string
            char buffer[126];
            sprintf(buffer, "%d",diff);
            // display TIME ms on original image
            putText(original, buffer, Point(100, 20), 1, 2, Scalar(255, 255, 255), 2, 8, 0);
            putText(original, "ms" , Point(150, 20), 1, 2, Scalar(255, 255, 255), 2, 8, 0);
            // draw results
            namedWindow("prew", WINDOW_AUTOSIZE);
            imshow("prew", original);
            // make video output
            outputVideo << original;

            int key1 = waitKey(20);

        }
    }
    cout << "total frame: "<<framecount<<" occupycount: "<<occupycount<<" falsedetect: "<<falsedetc<<endl;
*/
   // room tmp(1,"2134");
    //Allroom.push_back(tmp);
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    a.exec();
    /*string url = Allroom[0].getcameraurl();
    std::cout<<url;*/
    for(auto& th : Allthread) th.join();
    return 0;
}
