TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES = Event.cpp Fish.cpp test-harness-myprio.cpp Simulation.cpp

HEADERS = $$files(*.h,true)
