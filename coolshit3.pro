TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
QT += core gui sql

SOURCES += \
        Analytics.cpp \
        Battle.cpp \
        databaseManager.cpp \
        main.cpp

HEADERS += \
    Analytics.h \
    Hero.h \
    enemy.h \
    weapon.h
