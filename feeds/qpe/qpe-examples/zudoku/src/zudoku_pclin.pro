TEMPLATE	= app
LANGUAGE	= C++
CONFIG		+= qt thread warn_on release
HEADERS		+= src/mainwindow.h src/zudokuengine.h
SOURCES		+= src/mainwindow.cpp src/zudokuengine.cpp src/main.cpp
TARGET      = zudoku_pclin
DEFINES		+= 
INCLUDEPATH	+= . src ui /usr/include/qt3
