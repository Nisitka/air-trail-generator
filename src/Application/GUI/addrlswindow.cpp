#include "addrlswindow.h"
#include "ui_addrlswindow.h"

#include "designer.h"

addRLSWindow::addRLSWindow(CreatorRLS* creatorRLS,
                           GISInformer* gis,
                           QWidget *parent):
    creatorRLS(creatorRLS),
    gis(gis),
    QDialog(parent),
    ui(new Ui::addRLSWindow)
{
    ui->setupUi(this);
    setDesine();

    connect(ui->addRLSPushButton, SIGNAL(clicked(bool)),
            this,                 SLOT(addRLS()));

    // Изменение значения высоты при изменении координат
    connect(ui->xRLSspinBox, SIGNAL(valueChanged(int)),
            this,            SLOT(updateHeightRLS()));
    connect(ui->yRLSspinBox, SIGNAL(valueChanged(int)),
            this,            SLOT(updateHeightRLS()));
}

void addRLSWindow::addRLS()
{
    int idX = ui->xRLSspinBox->value();
    int idY = ui->yRLSspinBox->value();
    int idH = ui->zValueRLSLabel->text().toInt();

    LabelRLS dataRLS(QVector3D(idX, idY, idH),
                     ui->nameRLSLineEdit->text());

    creatorRLS->addRLS(dataRLS);

    clearFields();

    this->hide();

    loadRLS();
}

void addRLSWindow::updateHeightRLS()
{
    int idX = ui->xRLSspinBox->value();
    int idY = ui->yRLSspinBox->value();
    ui->zValueRLSLabel->setText(
                    QString::number(
                        gis->getH(idX, idY, Coords::id)));

}

void addRLSWindow::clearFields()
{
    ui->nameRLSLineEdit->clear();
    ui->xRLSspinBox->clear();
    ui->yRLSspinBox->clear();
    ui->zValueRLSLabel->clear();
}

void addRLSWindow::setDesine()
{
    this->setWindowTitle("Добавить РЛС");

    Designer::setButton(ui->addRLSPushButton);

    Designer::setGroupBox(ui->coordRLSgroupBox);
    Designer::setGroupBox(ui->nameRLSGroupBox);
}

addRLSWindow::~addRLSWindow()
{
    delete ui;
}
