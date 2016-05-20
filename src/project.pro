TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
LIBS += -lsimlib -lm
QMAKE_CXXFLAGS += -Wall -Wextra -pedantic

SOURCES += main.cpp \
    train.cpp \
    dispatcher.cpp \
    track.cpp \
    generator.cpp \
    globals.cpp \
    mycalendar.cpp \
    inouttrack.cpp

HEADERS += \
    train.h \
    dispatcher.h \
    track.h \
    generator.h \
    globals.h \
    mycalendar.h \
    inouttrack.h
