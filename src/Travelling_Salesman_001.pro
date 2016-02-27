# -------------------------------------------------
# Project created by QtCreator 2010-05-11T17:17:13
# -------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Travelling_Salesman_001
TEMPLATE = app
SOURCES += main.cpp \
    widget.cpp \
    tsp_population.cpp \
    tsp_individuum.cpp \
    graphic.cpp \
    tsp_control.cpp \
    tsp_locations.cpp \
    tsp_thread.cpp \
    tsp_workerthread.cpp \
    benchmark.cpp
HEADERS += widget.h \
    random.h \
    tsp_population.h \
    tsp_individuum.h \
    graphic.h \
    tsp_control.h \
    tsp_locations.h \
    tsp_thread.h \
    tsp_workerthread.h \
    timer.h \
    benchmark.h \
    MersenneTwister.h
FORMS += \
    widget.ui

QMAKE_CXXFLAGS += -O3

Debug: QMAKE_CXXFLAGS += -g -gstabs

# INCLUDEPATH += e:\Dateien\Programmierung\libs\boost_1_45_0
# LIBS += E:\Dateien\Programmierung\libs\boost_1_45_0\bin.v2\libs\date_time\build\gcc-mingw-4.5.2\debug\link-static\threading-multilib\boost_date_time-mgw45-mt-d-1_45.a
