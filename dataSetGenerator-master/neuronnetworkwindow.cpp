#include "neuronnetworkwindow.h"
#include "ui_neuronnetworkwindow.h"

#include <QApplication>
#include <QFileDialog>

#include <QDebug>

#include "designer.h"

neuronNetworkWindow::neuronNetworkWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::neuronNetworkWindow)
{
    ui->setupUi(this);

    connect(ui->predictButton, SIGNAL(clicked()),
            this,              SLOT(runPredict()));
    connect(ui->trainNetButton, SIGNAL(clicked()),
            this,               SLOT(runTrainNet()));

    ui->typePredictComboBox->addItems(listTypePredict);

    updateModelsList();

    connect(ui->setDirInputDataButton, SIGNAL(clicked()),
            this,                      SLOT(setDirImages()));
    connect(ui->setDirRewardDataButton, SIGNAL(clicked()),
            this,                       SLOT(setDirRewards()));

    countTrainImg = 0;
    countTrainReward = 0;

    setDesine();
}

void neuronNetworkWindow::setDirImages()
{
    // путь и имя сохраняемого файла
    QString patch = QFileDialog::getExistingDirectory(0, tr("Сохранить изображение"));

    ui->patchInputDataLineEdit->setText(patch);

    countTrainImg = countFilePatch(patch);
    if (countTrainReward != 0)
    {
        if (countTrainImg > countTrainReward)
        {
            ui->sizeDSLabel->setText(QString::number(countTrainReward));
        }
        else
        {
            ui->sizeDSLabel->setText(QString::number(countTrainImg));
        }
    }
}

void neuronNetworkWindow::setDirRewards()
{
    // путь и имя сохраняемого файла
    QString patch = QFileDialog::getExistingDirectory(0, tr("Сохранить изображение"));

    ui->patchRewardDataLineEdit->setText(patch);

    countTrainReward = countFilePatch(patch);
    if (countTrainImg != 0)
    {
        if (countTrainReward > countTrainImg)
        {
            ui->sizeDSLabel->setText(QString::number(countTrainImg));
        }
        else
        {
            ui->sizeDSLabel->setText(QString::number(countTrainReward));
        }
    }
}

int neuronNetworkWindow::countFilePatch(const QString &strDir)
{
    QDir dir;
    dir.setPath(strDir);
    dir.setFilter(QDir::Files| QDir :: NoDotAndDotDot);

    return dir.entryInfoList().count();
}

void neuronNetworkWindow::setDesine()
{
    // кнопки
    Designer::setButton(ui->trainNetButton);
    Designer::setButton(ui->predictButton);
    Designer::setButton(ui->setDirRewardDataButton);
    Designer::setButton(ui->setDirInputDataButton);

    //
    Designer::setGroupBox(ui->dataGroupBox);
    Designer::setGroupBox(ui->modelGroupBox);
    Designer::setGroupBox(ui->optTrainGroupBox);
    Designer::setGroupBox(ui->predictModelGroupBox);

    Designer::setTabWidget(ui->mainTabWidget);

    Designer::setGroupBox(ui->mainGroupBox, Designer::lightBlue);
}

void neuronNetworkWindow::updateModelsList()
{
    QDir netDirs;
    netDirs.setPath(QApplication::applicationDirPath() + "\\Models");
    netDirs.setFilter(QDir::Dirs | QDir :: NoDotAndDotDot);
    netDirs.setSorting(QDir::Time);

    ui->nameModelComboBox->clear();

    QStringList nameNetList;
    for (int i=0; i<netDirs.entryInfoList().count(); i++)
    {
        nameNetList << netDirs.entryInfoList().at(i).fileName();
    }

    ui->nameModelComboBox->addItems(nameNetList);
}

void neuronNetworkWindow::runPredict()
{
    switch (ui->typePredictComboBox->currentIndex()) {
    case rect:
        runPredictRect();
        break;
    case trail:
        runPredictTrail();
        break;
    }
}

void neuronNetworkWindow::runPredictRect()
{
    ui->predictButton->setEnabled(false);
    predictToRect(ui->nameModelComboBox->currentText());
}

void neuronNetworkWindow::runPredictTrail()
{
    predictTrail(ui->nameModelComboBox->currentText(),
                 beginPoint.x(), beginPoint.y(),
                 lastPoint.x(), lastPoint.y());
}

void neuronNetworkWindow::finishRectPredict(int idX, int idY)
{
    ui->predictButton->setEnabled(true);
    qDebug() << idX << idY;
}

void neuronNetworkWindow::setPointsPredictTrail(const QPoint &begin, const QPoint &last)
{
    beginPoint = begin;
    lastPoint = last;
}

void neuronNetworkWindow::runTrainNet()
{
    countTrainImg = 0;
    countTrainReward = 0;

    //ui->trainNetButton->setEnabled(false);
    trainNet(ui->patchInputDataLineEdit->text(),
             ui->patchRewardDataLineEdit->text(),
             ui->countEpochSpinBox->value(),
             ui->nameBuildModelLineEdit->text());
}

neuronNetworkWindow::~neuronNetworkWindow()
{
    delete ui;
}
