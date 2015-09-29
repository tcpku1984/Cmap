#-------------------------------------------------
#
# Project created by QtCreator 2015-08-13T09:34:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FastNode
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    block.cpp \
    blocks.cpp \
    constraint.cpp \
    csolve_VPSC.cpp \
    generate-constraints.cpp \
    remove_rectangle_overlap.cpp \
    solve_VPSC.cpp \
    variable.cpp \
    region.cpp

HEADERS  += mainwindow.h \
    block.h \
    blocks.h \
    constraint.h \
    csolve_VPSC.h \
    generate-constraints.h \
    isnan.h \
    placement_SolveVPSC.h \
    remove_rectangle_overlap.h \
    solve_VPSC.h \
    variable.h \
    region.h

FORMS    += mainwindow.ui


