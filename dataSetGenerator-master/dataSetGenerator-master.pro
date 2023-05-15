#-------------------------------------------------
#
# Project created by QtCreator 2023-02-16T08:43:28
#
#-------------------------------------------------

QT       += core gui printsupport datavisualization

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dataSetGenerator-master
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    core.cpp \
    gui.cpp \
    geoblock.cpp \
    map.cpp \
    geogenerator.cpp \
    mainwindow.cpp \
    visualinfowidget.cpp \
    areadrawwidget.cpp \
    painterimage.cpp \
    paintermapimage.cpp \
    optmapgeneratorwindow.cpp \
    calcqfunction.cpp \
    ray.cpp \
    optqfunwindow.cpp \
    rls.cpp \
    optrlswindow.cpp \
    painterdatanetimage.cpp \
    optdatanetwindow.cpp \
    qcustomplot.cpp \
    optbuilddatasetwindow.cpp \
    builderdataset.cpp \
    designer.cpp \
    trackparametras.cpp \
    buildertraildrones.cpp \
    neuronnetworkwindow.cpp \
    optdronewindow.cpp \
    drone.cpp \
    trainernetwork.cpp \
    managerrls.cpp \
    map3dwindow.cpp \
    visualmap3d.cpp \
    surfacegraph.cpp \
    custominputhandler.cpp \
    highlightseries.cpp \
    topographicseries.cpp \
    runwindow.cpp \
    volumetric.cpp

HEADERS  += \
    core.h \
    gui.h \
    geoblock.h \
    map.h \
    geogenerator.h \
    mainwindow.h \
    visualinfowidget.h \
    areadrawwidget.h \
    painterimage.h \
    paintermapimage.h \
    optmapgeneratorwindow.h \
    calcqfunction.h \
    ray.h \
    optqfunwindow.h \
    rls.h \
    optrlswindow.h \
    painterdatanetimage.h \
    optdatanetwindow.h \
    qcustomplot.h \
    optbuilddatasetwindow.h \
    builderdataset.h \
    designer.h \
    trackparametras.h \
    buildertraildrones.h \
    neuronnetworkwindow.h \
    optdronewindow.h \
    drone.h \
    trainernetwork.h \
    managerrls.h \
    map3dwindow.h \
    visualmap3d.h \
    surfacegraph.h \
    custominputhandler.h \
    highlightseries.h \
    topographicseries.h \
    runwindow.h \
    volumetric.h

FORMS    += mainwindow.ui \
    visualinfowidget.ui \
    optmapgeneratorwindow.ui \
    optqfunwindow.ui \
    optrlswindow.ui \
    optdatanetwindow.ui \
    optbuilddatasetwindow.ui \
    neuronnetworkwindow.ui \
    optdronewindow.ui \
    map3dwindow.ui

DISTFILES += \
    resurs/earchIcon.png \
    resurs/imgIcon.png \
    resurs/mapIcon.png \
    resurs/netIcon.png \
    resurs/qFunIcon.png \
    resurs/rlsIcon.png \
    neuronModel/commands.txt \
    neuronModel/READ ME.txt \
    neuronModel/buildTrain.py \
    neuronModel/cnn.py \
    neuronModel/model.py \
    neuronModel/t.py \
    neuronModel/testARGV.py \
    neuronModel/usedNet.py

RESOURCES += \
    res.qrc
