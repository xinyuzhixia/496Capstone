#-------------------------------------------------
#
# Project created by QtCreator 2018-01-06T15:52:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RRApplication
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    userloginpage.cpp \
    adminloginpage.cpp \
    room.cpp \
    Camera.cpp \
    MotionDetector.cpp \
    PeopleDetector.cpp \
    addroom.cpp \
    removeroom.cpp \
    bookroom.cpp \
    checkstatus.cpp \
    anglebutton.cpp


HEADERS += \
        mainwindow.h \
    userloginpage.h \
    adminloginpage.h \
    room.h \
    Camera.hpp \
    MotionDetector.hpp \
    PeopleDetector.hpp \
    common.h \
    addroom.h \
    removeroom.h \
    bookroom.h \
    checkstatus.h \
    anglebutton.h



FORMS += \
        mainwindow.ui \
    userloginpage.ui \
    adminloginpage.ui \
    adminconfigureroom.ui \
    anglebutton.ui

RESOURCES += \
    userinfo.qrc






INCLUDEPATH += /usr/local/include
INCLUDEPATH += /Users/Nancy/Documents/opencv-3.3.1/include
#LIBS += -L/usr/local/lib/
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_calib3d.3.3.1.dylib"
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_core.3.3.1.dylib"
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_dnn.3.3.1.dylib"
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_features2d.3.3.1.dylib"
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_flann.3.3.1.dylib"
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_highgui.3.3.1.dylib"
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_imgcodecs.3.3.1.dylib"
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_imgproc.3.3.1.dylib"
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_ml.3.3.1.dylib"
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_imgcodecs.3.3.1.dylib"
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_objdetect.3.3.1.dylib"
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_videoio.3.3.1.dylib"
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_videostab.3.3.1.dylib"
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_shape.3.3.1.dylib"
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_photo.3.3.1.dylib"
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_video.3.3.1.dylib"
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_stitching.3.3.1.dylib"
LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_superres.3.3.1.dylib"
#LIBS += "/Users/Nancy/Documents/opencv-3.3.1/build/lib/libopencv_stitching.3.3.1.dylib"

#QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig
#PKGCONFIG += opencv
