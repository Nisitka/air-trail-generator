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
    backend/buildertraildrones.cpp \
    backend/drone.cpp \
    backend/managerrls.cpp \
    backend/ray.cpp \
    backend/rls.cpp \
    GUI/designer.cpp \
    GUI/gui.cpp \
    GUI/mainwindow.cpp \
    GUI/optdronewindow.cpp \
    GUI/optmapgeneratorwindow.cpp \
    GUI/optrlswindow.cpp \
    GUI/runwindow.cpp \
    GUI/visualinfowidget.cpp \
    GUI/drawArea/areadrawwidget.cpp \
    GUI/drawArea/drawareatool.cpp \
    GUI/drawArea/toolsetrls.cpp \
    GUI/drawArea/tooldefault.cpp \
    GUI/drawArea/toolmovemap.cpp \
    GUI/drawArea/toolzoommap.cpp \
    GUI/drawArea/toolpredrect.cpp \
    GUI/drawArea/toolpredtrail.cpp \
    GUI/drawArea/toolvismap.cpp \
    GUI/drawArea/tooleditmap.cpp \
    backend/managerdrones.cpp \
    backend/trail.cpp \
    GUI/plotwidget.cpp \
    GUI/drawArea/toolruler.cpp \
    GUI/drawArea/toolsquareter.cpp \
    GUI/3DVisualization/mapopenglwidget.cpp \
    GUI/drawArea/toolpredict.cpp \
    backend/dao.cpp \
    GUI/dataaccessobjectwindow.cpp \
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
    backend/airobject.cpp \
    GUI/airobjectfunwindow.cpp \
    backend/GIS/geoblock.cpp \
    backend/GIS/geogenerator.cpp \
    backend/GIS/map.cpp \
    backend/GIS/paintermapimage.cpp \
    backend/GIS/gis.cpp \
    GUI/processtmpwidget.cpp \
    backend/graphicengine.cpp \
    backend/GIS/gisinformer.cpp \
    backend/GIS/coords.cpp \
    GUI/UI/airinfowindow.cpp \
    GUI/UI/airwindow.cpp

HEADERS  += \
    core.h \
    backend/buildertraildrones.h \
    backend/drone.h \
    backend/managerrls.h \
    backend/ray.h \
    backend/rls.h \
    GUI/designer.h \
    GUI/gui.h \
    GUI/mainwindow.h \
    GUI/optdronewindow.h \
    GUI/optmapgeneratorwindow.h \
    GUI/optrlswindow.h \
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
    backend/managerdrones.h \
    backend/trail.h \
    GUI/plotwidget.h \
    GUI/drawArea/drawtask.h \
    GUI/drawArea/toolruler.h \
    GUI/drawArea/toolsquareter.h \
    GUI/3DVisualization/mapopenglwidget.h \
    GUI/drawArea/toolpredict.h \
    backend/dao.h \
    GUI/dataaccessobjectwindow.h \
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
    backend/airobject.h \
    GUI/airobjectfunwindow.h \
    backend/GIS/geoblock.h \
    backend/GIS/geogenerator.h \
    backend/GIS/map.h \
    backend/GIS/paintermapimage.h \
    backend/GIS/gis.h \
    GUI/processtmpwidget.h \
    backend/graphicengine.h \
    backend/GIS/gisinformer.h \
    backend/GIS/coords.h \
    GUI/UI/airinfowindow.h \
    GUI/UI/airwindow.h

FORMS    += GUI/UI/mainwindow.ui \
    GUI/UI/optdronewindow.ui \
    GUI/UI/optmapgeneratorwindow.ui \
    GUI/UI/optqfunwindow.ui \
    GUI/UI/optrlswindow.ui \
    GUI/UI/dataaccessobjectwindow.ui \
    GUI/3DVisualization/map3dviswindow.ui \
    GUI/algorithmPredict/setalgpredictwindow.ui \
    GUI/drawArea/mapareamainwindow.ui \
    backend/airobject.ui \
    GUI/UI/airinfowindow.ui \
    GUI/UI/airwindow.ui

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
