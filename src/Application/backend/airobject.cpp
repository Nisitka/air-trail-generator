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

void AirObject::show_AirObject(QString n_Air, double l_Air, double w_Air, double s_Air, QString p_Air)
{

    nameLabel = new QLabel(tr("Название"));
    longsLabel = new QLabel(tr("Длина"));
    weightLabel = new QLabel(tr("Вес"));
    speedLabel = new QLabel(tr("Скорость"));

    nameEdit = new QLineEdit;
    nameEdit->setText(n_Air);
    longsEdit = new QLineEdit;
    longsEdit->setText(QString::number(l_Air));
    nweightEdit = new QLineEdit;
    nweightEdit->setText(QString::number(w_Air));
    speedEdit = new QLineEdit;
    speedEdit->setText(QString::number(s_Air));

    leftLayout = new QGridLayout;
    leftLayout->addWidget(nameLabel, 0, 0);
    leftLayout->addWidget(nameEdit, 0, 1);
    leftLayout->addWidget(longsLabel, 1, 0);
    leftLayout->addWidget(longsEdit, 1, 1);
    leftLayout->addWidget(weightLabel, 2, 0);
    leftLayout->addWidget(nweightEdit, 2, 1);
    leftLayout->addWidget(speedLabel, 3, 0);
    leftLayout->addWidget(speedEdit, 3, 1);

    widget = new QWidget;
    widget->setLayout(leftLayout);
    
    dockWidget = new QDockWidget(n_Air);
    dockWidget->setObjectName(n_Air);
    dockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
    dockWidget->setWidget(widget);
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
