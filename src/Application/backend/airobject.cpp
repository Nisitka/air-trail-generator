#include "airobject.h"
#include "ui_airobject.h"
#include <QDebug>

AirObject::AirObject(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AirObject)
{
    ui->setupUi(this);


    connect(ui->loadingButton, SIGNAL(clicked()),
            SLOT(show_AirObject()));
    connect(ui->creatButton, SIGNAL(clicked()),
            SLOT(creat_AirObject()));
    connect(ui->loadingPhotButton, SIGNAL(clicked()),
            SLOT(dowPhoto()));
}

AirObject::~AirObject()
{
    delete ui;
}

void AirObject::loading_AirObject(QString ID, QString name)
{
    ui->airBox->addItem(name, ID);
}

void AirObject::show_AirObject()
{
    show_AirObject(ui->airBox->currentData().toString());
}

void AirObject::show_AirObject(QString n_Air, double l_Air, double w_Air, double s_Air, QString p_Air
                               /*  AirObject*  */)
{
    AirObjectFunWindow *air = new AirObjectFunWindow;
    air->setParameters(n_Air,l_Air, w_Air,s_Air,p_Air);

    QDockWidget *dockWidget = new QDockWidget(n_Air);
    dockWidget->setObjectName(n_Air);
    dockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
    dockWidget->setWidget(air);
    dockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea,dockWidget);
}

void AirObject::creat_AirObject()
{
    creat_AirObject(ui->nameEdit->text(),
                    ui->longEdit->text().toDouble(),
                    ui->weightEdit->text().toDouble(),
                    ui->speedEdit->text().toDouble(),
                    ui->photEdit->text());
}

void AirObject::clearBoxs()
{
    ui->airBox->clear();
}

void AirObject::dowPhoto()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open text", "/home/",
                                                    "(*.png)");
    QFileInfo fileinfo(fileName);
    QString photo = fileinfo.fileName();
    ui->photEdit->setText(photo);
}
