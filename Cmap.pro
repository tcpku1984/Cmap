#-------------------------------------------------
#
# Project created by QtCreator 2015-06-15T12:48:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cmap
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    region.cpp \
    treemap.cpp \
    block.cpp \
    blocks.cpp \
    constraint.cpp \
    generate-constraints.cpp \
    remove_rectangle_overlap.cpp \
    solve_VPSC.cpp \
    variable.cpp \
    areateam.cpp \
    rectholder.cpp

HEADERS  += widget.h \
    region.h \
    treemap.h \
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
    areateam.h \
    rectholder.h

FORMS    += widget.ui \
    treemap.ui
