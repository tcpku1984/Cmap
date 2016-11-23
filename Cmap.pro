#-------------------------------------------------
#
# Project created by QtCreator 2015-06-15T12:48:06
#
#-------------------------------------------------

QT       += core gui
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cmap
TEMPLATE = app


SOURCES += main.cpp\
    block.cpp \
    blocks.cpp \
    constraint.cpp \
    generate-constraints.cpp \
    remove_rectangle_overlap.cpp \
    solve_VPSC.cpp \
    variable.cpp \
    TC_datacolor.cpp \
    TC_areateam.cpp \
    TC_areatreemap.cpp \
    TC_rectholder.cpp \
    TC_region.cpp \
    TC_regionfile.cpp \
    TC_treemap.cpp \
    TC_widget.cpp \
    TC_statistics.cpp \
    linechart.cpp

HEADERS  += \
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
    TC_datacolor.h \
    TC_areateam.h \
    TC_areatreemap.h \
    TC_treemap.h \
    TC_widget.h \
    TC_rectholder.h \
    TC_region.h \
    TC_regionfile.h \
    TC_statistics.h \
    linechart.h

FORMS    += widget.ui \
    treemap.ui \
    areatreemap.ui \
    TC_statistics.ui \
    linechart.ui
