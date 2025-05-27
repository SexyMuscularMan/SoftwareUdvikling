TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
QT += core gui sql

SOURCES += \
        Battle.cpp \
        databaseManager.cpp \
        main.cpp

HEADERS += \
    Hero.h \
    enemy.h \
    weapon.h
