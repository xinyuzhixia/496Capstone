#include "room.h"

room::room()
{

}
room::room(int roomnumber,string cameraurl)
{
     camera = new Camera(roomnumber,cameraurl);
     m_roomid = roomnumber;
     for (int i = 0; i < 24 ;i++){
         time[i].m_starthour = i;
         time[i].m_status = true;
     }


}room::~room(){

}
int room::getroomnumber(){

    return m_roomid;
}
bool room::getavailability(int starthour){

    return time[starthour].m_status;

}
bool room::updateavailability(int starthour, bool status){

    time[starthour].m_status = status;
    return true;

}
bool room::setroomnumber(int roomnuber){
    m_roomid = roomnuber;
    return true;
}
string room::getcameraurl(){
    return camera->geturl();
}
