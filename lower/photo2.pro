######################################################################
# Automatically generated by qmake (2.01a) ?? 5? 8 00:20:09 2014
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .


#***所有外加文件均需在此处加入，并且先qmake，再make***
HEADERS += dlinklist.h qt1.h communication.h  \                                   #添加.h头文件
    login.h \
    mythread.h\
    ui_qt1.h\
    ui_login.h
FORMS += qt1.ui \                                                                             #添加.ui文件
    login.ui
SOURCES += dlinklist.c main.cpp qt1.cpp camera.cpp yuv2rgb.cpp communication.c  \ #添加.c、.cpp源文件
    login.cpp \
    mythread.cpp
