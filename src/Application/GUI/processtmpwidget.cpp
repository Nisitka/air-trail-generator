#include "processtmpwidget.h"

processTmpWidget::processTmpWidget(QWidget* backgroundWidget_):
    QLabel(backgroundWidget_), backgroundWidget(backgroundWidget_)
{

    this->setStyleSheet("QWidget{"
                        "   background-color:transparent;"
                        "   border: 1px solid rgb(55,55,55,0);"
                        "};)");

    gif = new QMovie(":/resurs/loading2.gif"); //victory
    QSize size = QSize(80, 80);
    gif->setScaledSize(size);
    this->setMovie(gif);

    textIsShow = false;

    textLabel = new QLabel(this);
    textLabel->setFixedSize(size);
    textLabel->setAlignment(Qt::AlignCenter);
    textLabel->move(5,3);

    //this->hide();
}

void processTmpWidget::setValProgress(int percent)
{
    if (!textIsShow)
    {
        textIsShow = true;
        textLabel->show();
    }

    textLabel->setText(QString::number(percent) + "%");
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

    textLabel->hide();
    textIsShow = false;

    this->hide();
}

processTmpWidget::~processTmpWidget()
{
    gif->stop();
    delete gif;
    delete textLabel;
}
