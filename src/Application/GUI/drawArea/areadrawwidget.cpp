#include "areadrawwidget.h"

#include <QImage>
#include <QDebug>

#include <cmath>
#include <QBrush>

#include <QGuiApplication>

#include <QPixmap>

areaDrawWidget::areaDrawWidget(QImage* mapImg)
{
    this->setMinimumSize(100, 100);
    this->setMaximumSize(10080, 25000);
    this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    // отправляем данные об координатах курсора
    isExportCoord = true;

    // инициализация контейнера для изображений
    images = QVector <QImage*> (3);

    images[geoMap] = mapImg;

    //
    strFormatImg = QVector <const char*> (3);
    strFormatImg[jpg] = "JPG";
    strFormatImg[png] = "PNG";
    strFormatImg[bmp] = "BMP";

    drawGeoMap();

    // чтобы moveEvent работал без нажатия
    this->setMouseTracking(true);

    k = 1.0;

    pixRLS = new QPixmap(":/resurs/offRLS");
    pixCurRLS = new QPixmap(":/resurs/onRLS");
    curRLScolor.setRgb(0,255,255);

    this->setCursor(Qt::ArrowCursor);

    toolBar = new QToolBar("Панель инструментов");
    toolBar->setStyleSheet("QToolBar {"
                           "   border: 2px solid gray;"
                           "   padding: 2px 0px;"
                           "   border-radius: 2px;"
                           "   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                           "                                     stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
                           "};");
    addToolBar(Qt::TopToolBarArea, toolBar); // добавляем в панель инструментов

    //
    Tools[def]     = new toolDefault(this, def);
    Tools[moveImg] = new ToolMoveMap(this, moveImg);
    Tools[zoomImg] = new ToolZoomMap(this, zoomImg);

    keyCurTool = def;
    Tool = Tools[def];

    // Задачи, которые всегда должны выполняться
    appendDrawTask(background, new drawTask<areaDrawWidget>(this, &areaDrawWidget::drawBackground));
    appendDrawTask(terImg,     new drawTask<areaDrawWidget>(this, &areaDrawWidget::drawMap));
    appendDrawTask(iconRLS,    new drawTask<areaDrawWidget>(this, &areaDrawWidget::drawRLS));

    // Настройка визуала
    this->setStyleSheet("QMainWindow{"
                        "   background-color: rgb(255,255,255);"
                        "   border: 2px solid gray;"
                        "};");
}

void areaDrawWidget::appendTool(drawAreaTool *toolArea, int idPriority)
{
    Tools[idPriority] = toolArea;
}

void areaDrawWidget::contextMenuEvent(QContextMenuEvent *event)
{
    /* ... */
}

QToolBar* areaDrawWidget::getToolBar()
{
    return toolBar;
}

void areaDrawWidget::appendDrawTask(int priorityKey, taskPainter* task)
{
    // Добавляем задачу только если её не было
    if (!drawTasks.contains(priorityKey))
    {
        drawTasks[priorityKey] = task;
    }
}

void areaDrawWidget::delDrawTask(int priorityKey)
{
    drawTasks.remove(priorityKey);
}

void areaDrawWidget::drawBackground(QPainter &painter)
{
    // Отрисовка подложки
    painter.setPen(QPen(Qt::white, 2, Qt::SolidLine));
    painter.setBrush(QBrush(Qt::black, Qt::Dense7Pattern));
    painter.drawRect(0, 0, this->geometry().width(), this->geometry().height());

}

void areaDrawWidget::drawMap(QPainter &painter)
{
    // Какое изображение отрисовать
    switch (curOptRepaint)
    {
        case geoMap:
            drawImg = images[geoMap];
            break;

        case netData:
            drawImg = images[netData];
            break;

        case QFunction:
            drawImg = images[QFunction];
            break;
    }
    wightPixMap = drawImg->width() * k;
    heightPixMap = drawImg->height() * k;
    painter.drawImage(Xo, Yo, drawImg->scaled(wightPixMap, heightPixMap));
}

void areaDrawWidget::drawRLS(QPainter &painter)
{
    // Отрисовка станций (только на физ. карте)
    if (curOptRepaint == geoMap)
    {
        int rectX;
        int rectY;

        QColor colorText;
        for (int i=0; i<coordsRLS.size(); i++)
        {
            rectX = coordsRLS[i]->x() * k  + Xo;
            rectY = coordsRLS[i]->y() * k  + Yo;

            //
            if (i == idCurRLS)
            {
                painter.drawPixmap(rectX-16, rectY-18, pixCurRLS->scaled(36, 36));
                painter.setPen(curRLScolor);
            }

            else
            {
                 painter.drawPixmap(rectX-16, rectY-18, pixRLS->scaled(36, 36));
                 painter.setPen(Qt::black);
            }

            painter.drawText(QRect(rectX-16, rectY+15, 36, 20), namesRLS[i]);
        }
    }
}

void areaDrawWidget::getCoordDrawArea(int &Xo_, int &Yo_)
{
    Xo_ = Xo;
    Yo_ = Yo;
}

void areaDrawWidget::getSizePixMap(int &W, int &H)
{
    W = wightPixMap;
    H = heightPixMap;
}

double areaDrawWidget::getValZoom()
{
    return k;
}

void areaDrawWidget::addRLS(QPoint *posRLS, const QString& nameNewRLS)
{
    coordsRLS.append(posRLS);
    namesRLS.append(nameNewRLS);
}

void areaDrawWidget::delRLS(int indexRLS)
{
    coordsRLS.removeAt(indexRLS);
    namesRLS.removeAt(indexRLS);

    repaint();
}

void areaDrawWidget::setCurRLS(int idRLS)
{
    idCurRLS = idRLS;
    repaint();
}

void areaDrawWidget::saveImage(const QString &dirName, formatImg fImg, typeSaveImg tSave)
{
    // выбираем изображение которое будем сохранять
    QImage saveImg;
    switch (curOptRepaint) {
    case geoMap:
        saveImg = *images[geoMap];
        break;
    case netData:
        saveImg = *images[netData];
        break;
    case QFunction:
        saveImg = *images[QFunction];
        break;
    }

    // сохраняем
    switch (tSave) {
    case full:
        saveImg.save(dirName,
                      strFormatImg[fImg],
                      100);
        break;
    case screen:
        this->getScreen().toImage().save(dirName,
                                         strFormatImg[fImg],
                                         100);
        break;
    case rect:
//        size_t offset = idXoPredict * saveImg.depth() / 8
//                      + idYoPredict * saveImg.bytesPerLine();

//        QImage(saveImg.bits() + offset, 200, 200,
//               saveImg.bytesPerLine(), saveImg.format()).save(dirName,
//                                                                strFormatImg[fImg],
//                                                                100);
        break;
    }
}

QPixmap areaDrawWidget::getScreen()
{
    QPixmap pix(this->size());
    this->render(&pix);

    return pix;
}

void areaDrawWidget::paintEvent(QPaintEvent *pEvent)
{
    QPainter painter;
    painter.begin(this);

    // Прозрачная закраска
    QBrush voidBrush;

    // Выполнение задач отрисовки
    for (auto it = drawTasks.begin(); it != drawTasks.end(); ++it) {
        //(this->*it.value())(painter);
        it.value()->processing(painter);

        // чтобы цвет закраски был просзрачным
        painter.setBrush(voidBrush);
    }

    painter.end();
}

// Изменяем текущий инструмент
void areaDrawWidget::setTool(int key)
{

    // Освобождаем текущий от работы
    Tool->end();

    // Если хотим выбрать тот же инструменет, то отключаем его
    if (keyCurTool == key) key = def;

    //
    Tool = Tools[key];
    keyCurTool = key;

    // Подготавливаем его к работе
    Tool->init();

    repaint();
}

int areaDrawWidget::curTool()
{
    return keyCurTool;
}

void areaDrawWidget::setCoordDrawArea(int Xo_, int Yo_)
{
    Xo = Xo_;
    Yo = Yo_;
}

bool areaDrawWidget::mouseFromArea(QMouseEvent *mouseEvent)
{
    int xPressMouse = mouseEvent->x();
    int yPressMouse = mouseEvent->y();

    int dX, dY;
    dX = xPressMouse - Xo;
    dY = yPressMouse - Yo;

    // Условия
    return dX < wightPixMap &&
           dY < heightPixMap &&
           dX > 0 &&
           dY > 0;
}

void areaDrawWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
    if (mouseFromArea(mouseEvent)){

        Tool->mousePress(mouseEvent);
    }
}

void areaDrawWidget::wheelEvent(QWheelEvent *event)
{
    Tool->wheelEvent(event);
}

void areaDrawWidget::mouseReleaseEvent(QMouseEvent* mouseEvent)
{
    Tool->mouseRelease(mouseEvent);
}

void areaDrawWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if (mouseFromArea(mouseEvent))
    {
        Tool->mouseMove(mouseEvent);

        int idX, idY;
        Tool->getCoordMouse(idX, idY);

        // Обновляем координаты курсора
        updateCoord(double (idX - Xo) / k,
                    double (idY - Yo) / k);
    }
}

void areaDrawWidget::zoom(double dK)
{
    k += dK;

    if (k <= 0) k = 0.1;
}


void areaDrawWidget::drawGeoMap()
{
    curOptRepaint = geoMap;
    repaint();
}

void areaDrawWidget::drawDataNet()
{
    curOptRepaint = netData;
    repaint();
}

void areaDrawWidget::drawQFunction()
{
    curOptRepaint = QFunction;
    repaint();
}
