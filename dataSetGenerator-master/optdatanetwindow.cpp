#include "optdatanetwindow.h"
#include "ui_optdatanetwindow.h"

optDataNetWindow::optDataNetWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::optDataNetWindow)
{
    ui->setupUi(this);

    connect(ui->genDataNetButton, SIGNAL(clicked()),
            this,                 SIGNAL(generateImage()));
}

optDataNetWindow::~optDataNetWindow()
{
    delete ui;
}
