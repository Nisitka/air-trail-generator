#include "processtmpwidget.h"

processTmpWidget::processTmpWidget(QWidget* backgroundWidget_):
    QLabel(backgroundWidget_), backgroundWidget(backgroundWidget_)
{

    this->setStyleSheet("QWidget{"
                        "   background-color:transparent;"
                        "   border: 1px solid rgb(55,55,55,0);"
                        "};)");

    gif = new QMovie(":/resurs/victory.gif");
    this->setMovie(gif);

    //this->hide();
}

void processTmpWidget::Show()
{
    gif->start();

    this->setFixedSize(gif->currentImage().size());
    QPoint p(this->width()/2, this->height()/2);
    this->move(backgroundWidget->rect().center() - p);

    this->show();
}

void processTmpWidget::Hide()
{
    gif->stop();

    this->hide();
}

processTmpWidget::~processTmpWidget()
{
    gif->stop();
    delete gif;
}
