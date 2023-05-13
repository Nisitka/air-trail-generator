#include "map3dwindow.h"
#include "ui_map3dwindow.h"

#include "designer.h"

map3DWindow::map3DWindow(Map* map_, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::map3DWindow)
{
    map = map_;

    ui->setupUi(this);

    connect(ui->updateButton, SIGNAL(clicked()),
            this,             SIGNAL(generateMap3D()));
    Designer::setButton(ui->updateButton);

    Designer::setGroupBox(ui->mainGroupBox, Designer::lightBlue);

    Designer::setGroupBox(ui->groupBox);
    ui->groupBox->setMaximumWidth(115);

    widgetArea1 = NULL;
    colorLabel = NULL;
    textureCheckBox = NULL;

    widgetArea2 = NULL;
    modifier = NULL;

    Designer::setTabWidget(ui->tabWidget);

}

void map3DWindow::finishBuildMap(int idXo, int idYo, int numW, int numL)
{
    setMap(idXo, idYo, numW, numL);
}

void map3DWindow::setMap(int idXo, int idYo, int numW, int numL)
{
    ui->areaLayout->removeWidget(widgetArea1);
    ui->colorsLabelLayout->removeWidget(colorLabel);
    ui->checkBoxLayout->removeWidget(textureCheckBox);
    delete widgetArea1;
    delete colorLabel;
    delete textureCheckBox;

    widgetArea1 = new QWidget;
    ui->areaLayout->addWidget(widgetArea1);

    colorLabel = new QLabel;
    ui->colorsLabelLayout->addWidget(colorLabel);

    textureCheckBox = new QCheckBox;
    ui->checkBoxLayout->addWidget(textureCheckBox);

    visMap = new visualMap3D(widgetArea1, colorLabel, textureCheckBox,
                             idXo, idYo,
                             numW, numL,
                             map);

    int L = numL - (numL%4);
    setAreaZD(idXo, idYo, numW, L);
}

void map3DWindow::setAreaZD(int idXo, int idYo, int numW, int numL)
{
    ui->areaLayout->removeWidget(widgetArea2);
    delete widgetArea2;

    widgetArea2 = new QWidget;
    QWidget* widget = widgetArea2;

    Q3DScatter *graph = new Q3DScatter();
    QWidget *container = QWidget::createWindowContainer(graph);

    if (!graph->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
    }



    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 3, screenSize.height() / 3));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    //QWidget *widget = new QWidget();
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    QVBoxLayout *vLayout2 = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    hLayout->addLayout(vLayout2);

    widget->setWindowTitle(QStringLiteral("Volumetric object example - 3D terrain"));

    QCheckBox *sliceXCheckBox = new QCheckBox(widget);
    sliceXCheckBox->setText(QStringLiteral("Срез по оси X"));
    sliceXCheckBox->setChecked(false);
    QCheckBox *sliceYCheckBox = new QCheckBox(widget);
    sliceYCheckBox->setText(QStringLiteral("Срез по оси Z"));
    sliceYCheckBox->setChecked(false);
    QCheckBox *sliceZCheckBox = new QCheckBox(widget);
    sliceZCheckBox->setText(QStringLiteral("Срез по оси Y"));
    sliceZCheckBox->setChecked(false);

    QSlider *sliceXSlider = new QSlider(Qt::Horizontal, widget);
    sliceXSlider->setMinimum(0);
    sliceXSlider->setMaximum(1024);
    sliceXSlider->setValue(512);
    sliceXSlider->setEnabled(true);
    QSlider *sliceYSlider = new QSlider(Qt::Horizontal, widget);
    sliceYSlider->setMinimum(0);
    sliceYSlider->setMaximum(1024);
    sliceYSlider->setValue(512);
    sliceYSlider->setEnabled(true);
    QSlider *sliceZSlider = new QSlider(Qt::Horizontal, widget);
    sliceZSlider->setMinimum(0);
    sliceZSlider->setMaximum(1024);
    sliceZSlider->setValue(512);
    sliceZSlider->setEnabled(true);


    QCheckBox *fpsCheckBox = new QCheckBox(widget);
    fpsCheckBox->setText(QStringLiteral("FPS"));
    fpsCheckBox->setChecked(false);
    QLabel *fpsLabel = new QLabel(QStringLiteral(""), widget);

    QLabel *sliceImageXLabel = new QLabel(widget);
    QLabel *sliceImageYLabel = new QLabel(widget);
    QLabel *sliceImageZLabel = new QLabel(widget);
    sliceImageXLabel->setMinimumSize(QSize(200, 100));
    sliceImageYLabel->setMinimumSize(QSize(200, 200));
    sliceImageZLabel->setMinimumSize(QSize(200, 100));
    sliceImageXLabel->setMaximumSize(QSize(200, 100));
    sliceImageYLabel->setMaximumSize(QSize(200, 200));
    sliceImageZLabel->setMaximumSize(QSize(200, 100));
    sliceImageXLabel->setFrameShape(QFrame::Box);
    sliceImageYLabel->setFrameShape(QFrame::Box);
    sliceImageZLabel->setFrameShape(QFrame::Box);
    sliceImageXLabel->setScaledContents(true);
    sliceImageYLabel->setScaledContents(true);
    sliceImageZLabel->setScaledContents(true);

    QSlider *alphaMultiplierSlider = new QSlider(Qt::Horizontal, widget);
    alphaMultiplierSlider->setMinimum(0);
    alphaMultiplierSlider->setMaximum(139);
    alphaMultiplierSlider->setValue(100);
    alphaMultiplierSlider->setEnabled(true);
    QLabel *alphaMultiplierLabel = new QLabel(QStringLiteral("Доля прозрачности: 1.0"));

    QCheckBox *preserveOpacityCheckBox = new QCheckBox(widget);
    preserveOpacityCheckBox->setText(QStringLiteral("Прозрачный рельеф"));
    preserveOpacityCheckBox->setChecked(false);

    QCheckBox *useHighDefShaderCheckBox = new QCheckBox(widget);
    useHighDefShaderCheckBox->setText(QStringLiteral("HD шейдер"));
    useHighDefShaderCheckBox->setChecked(true);

    QLabel *performanceNoteLabel =
            new QLabel(QStringLiteral(
                           "Примечание:\nДля большей произволительности\nрекомендуется использовать\nграфический чип (GPU)."));
    performanceNoteLabel->setFrameShape(QFrame::Box);

    QCheckBox *drawSliceFramesCheckBox = new QCheckBox(widget);
    drawSliceFramesCheckBox->setText(QStringLiteral("Рисовать линии срезов"));
    drawSliceFramesCheckBox->setChecked(false);

    vLayout->addWidget(sliceXCheckBox);
    vLayout->addWidget(sliceXSlider);
    vLayout->addWidget(sliceImageXLabel);
    vLayout->addWidget(sliceYCheckBox);
    vLayout->addWidget(sliceYSlider);
    vLayout->addWidget(sliceImageYLabel);
    vLayout->addWidget(sliceZCheckBox);
    vLayout->addWidget(sliceZSlider);
    vLayout->addWidget(sliceImageZLabel);
    vLayout->addWidget(drawSliceFramesCheckBox, 1, Qt::AlignTop);
    vLayout2->addWidget(fpsCheckBox);
    vLayout2->addWidget(fpsLabel);
    vLayout2->addWidget(alphaMultiplierLabel);
    vLayout2->addWidget(alphaMultiplierSlider);
    vLayout2->addWidget(preserveOpacityCheckBox);
    vLayout2->addWidget(useHighDefShaderCheckBox);
    vLayout2->addWidget(performanceNoteLabel, 1, Qt::AlignTop);

    modifier = new VolumetricModifier(graph, map, idXo, idYo, numW, numL);

    modifier->setFpsLabel(fpsLabel);

    modifier->setSliceSliders(sliceXSlider, sliceYSlider, sliceZSlider);
    modifier->setSliceLabels(sliceImageXLabel, sliceImageYLabel, sliceImageZLabel);
    modifier->setAlphaMultiplierLabel(alphaMultiplierLabel);

    QObject::connect(fpsCheckBox, &QCheckBox::stateChanged, modifier,
                     &VolumetricModifier::setFpsMeasurement);
    QObject::connect(sliceXCheckBox, &QCheckBox::stateChanged, modifier,
                     &VolumetricModifier::sliceX);
    QObject::connect(sliceYCheckBox, &QCheckBox::stateChanged, modifier,
                     &VolumetricModifier::sliceY);
    QObject::connect(sliceZCheckBox, &QCheckBox::stateChanged, modifier,
                     &VolumetricModifier::sliceZ);
    QObject::connect(sliceXSlider, &QSlider::valueChanged, modifier,
                     &VolumetricModifier::adjustSliceX);
    QObject::connect(sliceYSlider, &QSlider::valueChanged, modifier,
                     &VolumetricModifier::adjustSliceY);
    QObject::connect(sliceZSlider, &QSlider::valueChanged, modifier,
                     &VolumetricModifier::adjustSliceZ);
    QObject::connect(preserveOpacityCheckBox, &QCheckBox::stateChanged, modifier,
                     &VolumetricModifier::setPreserveOpacity);
    QObject::connect(useHighDefShaderCheckBox, &QCheckBox::stateChanged, modifier,
                     &VolumetricModifier::setUseHighDefShader);
    QObject::connect(alphaMultiplierSlider, &QSlider::valueChanged, modifier,
                     &VolumetricModifier::adjustAlphaMultiplier);
    QObject::connect(drawSliceFramesCheckBox, &QCheckBox::stateChanged, modifier,
                     &VolumetricModifier::setDrawSliceFrames);

    ui->areaLayout2->addWidget(widgetArea2);
    widgetArea2->show();
}

map3DWindow::~map3DWindow()
{
    delete ui;
}
