#-------------------------------------------------
#
# Project created by QtCreator 2023-02-16T08:43:28
#
#-------------------------------------------------

QT       += core gui printsupport opengl sql

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

LIBS += -lOpengl32 -lglu32

SOURCES += main.cpp\
    core.cpp \
    backend/ray.cpp \
    GUI/designer.cpp \
    GUI/gui.cpp \
    GUI/mainwindow.cpp \
    GUI/runwindow.cpp \
    GUI/visualinfowidget.cpp \
    GUI/drawArea/areadrawwidget.cpp \
    GUI/plotwidget.cpp \
    GUI/3DVisualization/mapopenglwidget.cpp \
    GUI/3DVisualization/map3dviswindow.cpp \
    GUI/algorithmPredict/glyph.cpp \
    GUI/algorithmPredict/setalgpredictwindow.cpp \
    GUI/algorithmPredict/compospredfunctionarea.cpp \
    GUI/algorithmPredict/glyphpoint.cpp \
    GUI/algorithmPredict/matchfunglyph.cpp \
    GUI/algorithmPredict/operationglyph.cpp \
    GUI/algorithmPredict/matchoperglyph.cpp \
    GUI/algorithmPredict/lineglyph.cpp \
    GUI/algorithmPredict/glyphcomposer.cpp \
    GUI/algorithmPredict/labelglyph.cpp \
    GUI/drawArea/mapareamainwindow.cpp \
    GUI/drawArea/scrollmapwidget.cpp \
    GUI/multiplewindow.cpp \
    backend/GIS/geogenerator.cpp \
    backend/GIS/paintermapimage.cpp \
    backend/GIS/gis.cpp \
    GUI/processtmpwidget.cpp \
    backend/GIS/coords.cpp \
    backend/GIS/mapdata.cpp \
    backend/tracerlight.cpp \
    GUI/drawArea/Tools/drawareatool.cpp \
    GUI/drawArea/Tools/tooldefault.cpp \
    GUI/drawArea/Tools/tooleditmap.cpp \
    GUI/drawArea/Tools/toolmovemap.cpp \
    GUI/drawArea/Tools/toolpredict.cpp \
    GUI/drawArea/Tools/toolpredrect.cpp \
    GUI/drawArea/Tools/toolpredtrail.cpp \
    GUI/drawArea/Tools/toolruler.cpp \
    GUI/drawArea/Tools/toolsetrls.cpp \
    GUI/drawArea/Tools/toolsquareter.cpp \
    GUI/drawArea/Tools/toolvismap.cpp \
    GUI/drawArea/Tools/toolzoommap.cpp \
    GUI/drawArea/DecktopItems/minimapwidget.cpp \
    GUI/drawArea/DecktopItems/scrollitem.cpp \
    GUI/drawArea/DecktopItems/coordsinfoform.cpp \
    backend/RLS/managerrls.cpp \
    backend/RLS/rls.cpp \
    backend/Trail/trail.cpp \
    GUI/drawArea/zoomcontrollerwidget.cpp \
    backend/RLS/labelrls.cpp \
    GUI/hellowindow.cpp \
    GUI/mainswitcherwindow.cpp \
    backend/MapFile/mapfile.cpp \
    GUI/manrlswindow.cpp \
    GUI/createprojectwindow.cpp \
    backend/RLS/radar.cpp \
    backend/Trail/buildertrail.cpp

HEADERS  += \
    core.h \
    backend/buildertraildrones.h \
    backend/managerrls.h \
    backend/ray.h \
    backend/rls.h \
    GUI/designer.h \
    GUI/gui.h \
    GUI/mainwindow.h \
    GUI/runwindow.h \
    GUI/visualinfowidget.h \
    GUI/drawArea/areadrawwidget.h \
    GUI/drawArea/drawareatool.h \
    GUI/drawArea/toolsetrls.h \
    GUI/drawArea/tooldefault.h \
    GUI/drawArea/toolmovemap.h \
    GUI/drawArea/toolzoommap.h \
    GUI/drawArea/toolpredrect.h \
    GUI/drawArea/toolpredtrail.h \
    GUI/drawArea/toolvismap.h \
    GUI/drawArea/tooleditmap.h \
    backend/trail.h \
    GUI/plotwidget.h \
    GUI/drawArea/drawtask.h \
    GUI/drawArea/toolruler.h \
    GUI/drawArea/toolsquareter.h \
    GUI/3DVisualization/mapopenglwidget.h \
    GUI/drawArea/toolpredict.h \
    GUI/3DVisualization/map3dviswindow.h \
    GUI/algorithmPredict/glyph.h \
    GUI/algorithmPredict/setalgpredictwindow.h \
    GUI/algorithmPredict/compospredfunctionarea.h \
    GUI/algorithmPredict/glyphpoint.h \
    GUI/algorithmPredict/matchfunglyph.h \
    GUI/algorithmPredict/operationglyph.h \
    GUI/algorithmPredict/matchoperglyph.h \
    GUI/algorithmPredict/lineglyph.h \
    GUI/algorithmPredict/glyphcomposer.h \
    GUI/algorithmPredict/labelglyph.h \
    GUI/drawArea/mapareamainwindow.h \
    GUI/drawArea/scrollmapwidget.h \
    GUI/multiplewindow.h \
    backend/GIS/geogenerator.h \
    backend/GIS/paintermapimage.h \
    backend/GIS/gis.h \
    GUI/processtmpwidget.h \
    backend/GIS/gisinformer.h \
    backend/GIS/coords.h \
    backend/GIS/heightmeter.h \
    backend/GIS/mapdata.h \
    backend/tracerlight.h \
    GUI/drawArea/Tools/drawareatool.h \
    GUI/drawArea/Tools/tooldefault.h \
    GUI/drawArea/Tools/tooleditmap.h \
    GUI/drawArea/Tools/toolmovemap.h \
    GUI/drawArea/Tools/toolpredict.h \
    GUI/drawArea/Tools/toolpredrect.h \
    GUI/drawArea/Tools/toolpredtrail.h \
    GUI/drawArea/Tools/toolruler.h \
    GUI/drawArea/Tools/toolsetrls.h \
    GUI/drawArea/Tools/toolsquareter.h \
    GUI/drawArea/Tools/toolvismap.h \
    GUI/drawArea/Tools/toolzoommap.h \
    GUI/drawArea/DecktopItems/minimapwidget.h \
    GUI/drawArea/DecktopItems/scrolldirector.h \
    GUI/drawArea/DecktopItems/scrollitem.h \
    GUI/drawArea/DecktopItems/coordsinfoform.h \
    backend/RLS/managerrls.h \
    backend/RLS/rls.h \
    backend/Trail/trail.h \
    GUI/drawArea/zoomcontrollerwidget.h \
    backend/RLS/informerrls.h \
    backend/RLS/labelrls.h \
    GUI/hellowindow.h \
    GUI/mainswitcherwindow.h \
    backend/mapfile.h \
    backend/MapFile/mapfile.h \
    backend/MapFile/datamapgis.h \
    backend/MapFile/datamaprls.h \
    GUI/manrlswindow.h \
    GUI/createprojectwindow.h \
    backend/RLS/radar.h \
    backend/Trail/buildertrail.h

FORMS    += GUI/UI/mainwindow.ui \
    GUI/3DVisualization/map3dviswindow.ui \
    GUI/algorithmPredict/setalgpredictwindow.ui \
    GUI/drawArea/mapareamainwindow.ui \
    GUI/drawArea/DecktopItems/coordsinfoform.ui \
    GUI/drawArea/zoomcontrollerwidget.ui \
    GUI/hellowindow.ui \
    GUI/mainswitcherwindow.ui \
    GUI/manrlswindow.ui \
    GUI/drawArea/DecktopItems/form.ui \
    GUI/createprojectwindow.ui

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
    neuronModel/usedNet.py \
    resurs/Thumbs.db \
    resurs/copy.png \
    resurs/downVector.png \
    resurs/drone1.png \
    resurs/droneFinish.png \
    resurs/droneStart.png \
    resurs/editEarthTool.png \
    resurs/genFiles.png \
    resurs/hand.png \
    resurs/hand3D.png \
    resurs/handDrone.png \
    resurs/icon3D.png \
    resurs/leftVector.png \
    resurs/machinery.png \
    resurs/new.png \
    resurs/offRLS.png \
    resurs/onRLS.png \
    resurs/plane.png \
    resurs/radarBlue.png \
    resurs/radarGreen.png \
    resurs/rightVector.png \
    resurs/RLS.png \
    resurs/save.png \
    resurs/startWindow.png \
    resurs/toolEarthDown.png \
    resurs/toolEarthMove.png \
    resurs/toolEarthUp.png \
    resurs/trail1.png \
    resurs/trail2.png \
    resurs/upVector.png \
    resurs/zoom.png \
    resurs/zoom2.png \
    resurs/zoomTool.png \
    GUI/algorithmPredict/doc.txt \
    maps/img4.png \
    maps/img.png \
    maps/img2.png \
    maps/img3.png

RESOURCES += \
    res.qrc
