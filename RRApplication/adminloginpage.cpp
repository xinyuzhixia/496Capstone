#include "adminloginpage.h"
#include "ui_adminloginpage.h"
#include "common.h"
adminloginpage::adminloginpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminloginpage)
{
    ui->setupUi(this);

}

adminloginpage::~adminloginpage()
{
    delete ui;
}



void adminloginpage::on_videostream_clicked()
{
// int temp = DoMotionDetection();
    Allroom[0].getcamera()->DisplayVideo();

}
int adminloginpage::DoMotionDetection(){
    VideoCapture cap;
    MotionDetector test;
  //  string url =  "http://192.168.0.102:15156/videostream.cgi?loginuse=admin&loginpas=1234";
  //  string Testvideo = "/Users/Nancy/Documents/496/testvideo/TwoPeopleWalking.mov";
    string Testvideo = "http://192.168.0.102:15156/videostream.cgi?loginuse=admin&loginpas=1234";
      bool res = cap.open(Testvideo);
      if (!cap.isOpened())  // if not success, exit program
      {
          if (!res){
              cout << "false" <<endl;}
          cout << "Cannot open the video cam" << endl;
          return -1;
      }

      int cout_frames = 0;
      double area_sum = 0;

      while (1)
      {
          Mat frame1;
          Mat frame2;
          Mat ThresholdImage;
          Mat contours;
          Mat foregroundImg;
          Mat foregroundMask;

          cout_frames ++;

          bool bSuccess = cap.read(frame1);

           test.BackgroundSubstraction_new(frame1, foregroundImg, foregroundMask);

          if (!bSuccess) //if not success, break loop
          {
              cout << "Cannot read a frame from video stream" << endl;
              break;
          }


         // video.write(foregroundImg);


          //bool dete;
          double area_frame = 0;
          test.TrackingMovement(foregroundMask, frame1, area_frame);
          //imshow("Final Threshold", ThresholdImage);
          imshow("foreground mask", frame1);
          waitKey(10);
          //imshow("foreground image", foregroundImg);
          if (waitKey(30) == 27) {//wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop

              cout << "esc key is pressed by user" << endl;
              break;
          }


      }
      //video.release();[]
      cap.release();
      destroyAllWindows();
      cout << "Processed " << cout_frames << " frames with " << test.Getdetected() << " frames detected motions! " << endl;


      return 0;

}



void adminloginpage::on_addroom_clicked()
{
    //addremoveroom dialog;
   // dialog.show();
    addroom* dialog = new addroom();
       dialog->setModal(true);
       int result = dialog->exec();
        qDebug()<<"result"<<result;
       if (result == 1){
            QStringList info = dialog->getinfo();
            int roomid = info[0].toInt();
            std::string cameraip = info[1].toStdString() ;
            std::string cameraport = info[2].toStdString() ;
            std::string camerausername = info[3].toStdString() ;
            std::string camerapwd = info[4].toStdString();
            //"http://192.168.0.102:15156/videostream.cgi?loginuse=admin&loginpas=1234"
            std::string cameraurl="http://"+cameraip+":"+cameraport+"/videostream.cgi?loginuse="+camerausername+"&loginpas="+camerapwd;
            room newroom(roomid,cameraurl);
            //std::thread currt(&Camera:: RunOccupancyDetection, newroom.getcamera(),10000, false);
            Allroom.push_back(newroom);
            Allthread.push_back(std::thread(&Camera:: RunOccupancyDetection, newroom.getcamera(),10000, false));

       }


}

void adminloginpage::on_removeroom_clicked()
{
  //  std::cout<<Allroom[0].getroomnumber();
    removeroom* dialog = new removeroom();
    dialog->setModal(true);
    int result = dialog->exec();
    if (result == 1){
        int roomid = dialog->getinfo().toInt();
        for (int i  = 0 ; i < Allroom.size();i++){
            if (Allroom[i].getroomnumber() == roomid){
                Allroom.erase(Allroom.begin()+i);
                break;
            }
        }
    }
   // std::cout<<Allroom.size()<<Allroom[0].getroomnumber();

}

void adminloginpage::on_logout_clicked()
{
    close();
}

void adminloginpage::on_cameraconfigure_clicked()
{
    anglebutton angle;
    angle.setModal(true);
    angle.exec();
}
