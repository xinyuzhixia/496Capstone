#ifndef ROOM_H
#define ROOM_H
#include "Camera.hpp"
struct availability {
    int m_starthour;
    bool m_status;
};

class room
{
private:
    int m_roomid;
    Camera* camera;
    availability time[24];
public:
    room();
    room(int roomnumber,string cameraurl);
    int getroomnumber();
    bool getavailability(int starthour);
    bool updateavailability(int starthour,bool status);
    bool setroomnumber(int number);
    Camera* getcamera(){return camera;}
    std::string getcameraurl();
    ~room();
};

#endif // ROOM_H
