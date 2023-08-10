/********************************************************************************
** Form generated from reading UI file 'optrlswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTRLSWINDOW_H
#define UI_OPTRLSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_optRLSwindow
{
public:
    QHBoxLayout *horizontalLayout_19;
    QGroupBox *mainGroupBox;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_10;
    QGroupBox *addRLSGroupBox;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_16;
    QGroupBox *nameNewRLSGroupBox;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *nameNewRLSLineEdit;
    QVBoxLayout *verticalLayout_8;
    QSpacerItem *verticalSpacer_3;
    QPushButton *createRLSButton;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *listRLSGroupBox;
    QHBoxLayout *horizontalLayout_9;
    QComboBox *listRLSComboBox;
    QPushButton *removeRLSButton;
    QSpacerItem *verticalSpacer_5;
    QTabWidget *generateDVOptTabWidget;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_13;
    QGroupBox *optionsGroupBox;
    QVBoxLayout *verticalLayout_11;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_17;
    QGroupBox *RmaxGroupBox;
    QHBoxLayout *horizontalLayout_5;
    QSpinBox *RmaxSpinBox;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_7;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_12;
    QGroupBox *deltaZDGroupBox;
    QVBoxLayout *verticalLayout_15;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_18;
    QSpinBox *countHorVecZDSpinBox;
    QSpacerItem *horizontalSpacer_6;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_12;
    QSpinBox *countPointsDVSpinBox;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QProgressBar *setOptRLSProgressBar;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QPushButton *setOptZDvertButton;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_8;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_14;
    QGroupBox *ZDvertGroupBox;
    QVBoxLayout *verticalLayout_3;
    QCustomPlot *graphicDVWidget;
    QGroupBox *HRLSgroupBox;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_13;
    QSlider *hZDSlider;
    QSpinBox *hZDspinBox;
    QLabel *mLabel_4;
    QLabel *colorHLabel;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *rlsTabWidget;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_17;
    QHBoxLayout *horizontalLayout_11;
    QGroupBox *coordRLSgroupBox;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_15;
    QLabel *xRLSLabel;
    QSpinBox *xRLSspinBox;
    QLabel *mLabel_2;
    QHBoxLayout *horizontalLayout_14;
    QLabel *yRLSLabel;
    QSpinBox *yRLSspinBox;
    QLabel *mLabel_3;
    QHBoxLayout *horizontalLayout_21;
    QLabel *zRLSLabel;
    QLabel *zValueRLSLabel;
    QLabel *mLabel_6;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_7;
    QProgressBar *setRLSprogressBar;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *setCoordRLSpushButton;
    QPushButton *on_off_RLS_Button;
    QSpacerItem *horizontalSpacer_15;

    void setupUi(QWidget *optRLSwindow)
    {
        if (optRLSwindow->objectName().isEmpty())
            optRLSwindow->setObjectName(QString::fromUtf8("optRLSwindow"));
        optRLSwindow->resize(549, 636);
        horizontalLayout_19 = new QHBoxLayout(optRLSwindow);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        mainGroupBox = new QGroupBox(optRLSwindow);
        mainGroupBox->setObjectName(QString::fromUtf8("mainGroupBox"));
        verticalLayout_6 = new QVBoxLayout(mainGroupBox);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        addRLSGroupBox = new QGroupBox(mainGroupBox);
        addRLSGroupBox->setObjectName(QString::fromUtf8("addRLSGroupBox"));
        addRLSGroupBox->setMaximumSize(QSize(300, 999));
        QFont font;
        font.setPointSize(12);
        addRLSGroupBox->setFont(font);
        horizontalLayout_7 = new QHBoxLayout(addRLSGroupBox);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        nameNewRLSGroupBox = new QGroupBox(addRLSGroupBox);
        nameNewRLSGroupBox->setObjectName(QString::fromUtf8("nameNewRLSGroupBox"));
        nameNewRLSGroupBox->setMaximumSize(QSize(16777215, 70));
        nameNewRLSGroupBox->setFont(font);
        horizontalLayout_8 = new QHBoxLayout(nameNewRLSGroupBox);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        nameNewRLSLineEdit = new QLineEdit(nameNewRLSGroupBox);
        nameNewRLSLineEdit->setObjectName(QString::fromUtf8("nameNewRLSLineEdit"));
        nameNewRLSLineEdit->setFont(font);

        horizontalLayout_8->addWidget(nameNewRLSLineEdit);


        verticalLayout_16->addWidget(nameNewRLSGroupBox);


        horizontalLayout_7->addLayout(verticalLayout_16);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_8->addItem(verticalSpacer_3);

        createRLSButton = new QPushButton(addRLSGroupBox);
        createRLSButton->setObjectName(QString::fromUtf8("createRLSButton"));
        createRLSButton->setMinimumSize(QSize(100, 30));
        createRLSButton->setMaximumSize(QSize(100, 16777215));
        createRLSButton->setFont(font);

        verticalLayout_8->addWidget(createRLSButton);


        horizontalLayout_7->addLayout(verticalLayout_8);


        horizontalLayout_10->addWidget(addRLSGroupBox);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        listRLSGroupBox = new QGroupBox(mainGroupBox);
        listRLSGroupBox->setObjectName(QString::fromUtf8("listRLSGroupBox"));
        listRLSGroupBox->setMaximumSize(QSize(16777215, 70));
        listRLSGroupBox->setFont(font);
        horizontalLayout_9 = new QHBoxLayout(listRLSGroupBox);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        listRLSComboBox = new QComboBox(listRLSGroupBox);
        listRLSComboBox->setObjectName(QString::fromUtf8("listRLSComboBox"));
        listRLSComboBox->setMinimumSize(QSize(0, 30));
        listRLSComboBox->setFont(font);

        horizontalLayout_9->addWidget(listRLSComboBox);

        removeRLSButton = new QPushButton(listRLSGroupBox);
        removeRLSButton->setObjectName(QString::fromUtf8("removeRLSButton"));
        removeRLSButton->setMinimumSize(QSize(80, 30));
        removeRLSButton->setMaximumSize(QSize(80, 16777215));
        removeRLSButton->setFont(font);

        horizontalLayout_9->addWidget(removeRLSButton);


        verticalLayout_7->addWidget(listRLSGroupBox);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Ignored);

        verticalLayout_7->addItem(verticalSpacer_5);


        horizontalLayout_10->addLayout(verticalLayout_7);


        verticalLayout_6->addLayout(horizontalLayout_10);

        generateDVOptTabWidget = new QTabWidget(mainGroupBox);
        generateDVOptTabWidget->setObjectName(QString::fromUtf8("generateDVOptTabWidget"));
        generateDVOptTabWidget->setFont(font);
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_13 = new QVBoxLayout(tab_3);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        optionsGroupBox = new QGroupBox(tab_3);
        optionsGroupBox->setObjectName(QString::fromUtf8("optionsGroupBox"));
        optionsGroupBox->setFont(font);
        verticalLayout_11 = new QVBoxLayout(optionsGroupBox);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        tabWidget = new QTabWidget(optionsGroupBox);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QFont font1;
        font1.setPointSize(11);
        tabWidget->setFont(font1);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_9 = new QVBoxLayout(tab);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        RmaxGroupBox = new QGroupBox(tab);
        RmaxGroupBox->setObjectName(QString::fromUtf8("RmaxGroupBox"));
        RmaxGroupBox->setMinimumSize(QSize(0, 0));
        QFont font2;
        font2.setPointSize(10);
        RmaxGroupBox->setFont(font2);
        horizontalLayout_5 = new QHBoxLayout(RmaxGroupBox);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        RmaxSpinBox = new QSpinBox(RmaxGroupBox);
        RmaxSpinBox->setObjectName(QString::fromUtf8("RmaxSpinBox"));
        RmaxSpinBox->setFont(font);
        RmaxSpinBox->setMinimum(250);
        RmaxSpinBox->setMaximum(10000);

        horizontalLayout_5->addWidget(RmaxSpinBox);


        horizontalLayout_17->addWidget(RmaxGroupBox);

        horizontalSpacer = new QSpacerItem(150, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer);


        verticalLayout_9->addLayout(horizontalLayout_17);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_7);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_12 = new QVBoxLayout(tab_2);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        deltaZDGroupBox = new QGroupBox(tab_2);
        deltaZDGroupBox->setObjectName(QString::fromUtf8("deltaZDGroupBox"));
        deltaZDGroupBox->setFont(font);
        verticalLayout_15 = new QVBoxLayout(deltaZDGroupBox);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        groupBox = new QGroupBox(deltaZDGroupBox);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFont(font);
        horizontalLayout_18 = new QHBoxLayout(groupBox);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        countHorVecZDSpinBox = new QSpinBox(groupBox);
        countHorVecZDSpinBox->setObjectName(QString::fromUtf8("countHorVecZDSpinBox"));
        countHorVecZDSpinBox->setMaximumSize(QSize(200, 16777215));
        countHorVecZDSpinBox->setMinimum(900);
        countHorVecZDSpinBox->setMaximum(4000);

        horizontalLayout_18->addWidget(countHorVecZDSpinBox);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_6);


        verticalLayout_15->addWidget(groupBox);

        groupBox_2 = new QGroupBox(deltaZDGroupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font);
        horizontalLayout_12 = new QHBoxLayout(groupBox_2);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        countPointsDVSpinBox = new QSpinBox(groupBox_2);
        countPointsDVSpinBox->setObjectName(QString::fromUtf8("countPointsDVSpinBox"));
        countPointsDVSpinBox->setMaximumSize(QSize(200, 16777215));
        countPointsDVSpinBox->setMinimum(60);
        countPointsDVSpinBox->setMaximum(600);

        horizontalLayout_12->addWidget(countPointsDVSpinBox);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_8);


        verticalLayout_15->addWidget(groupBox_2);


        verticalLayout_12->addWidget(deltaZDGroupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_12->addItem(verticalSpacer);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_11->addWidget(tabWidget);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        setOptRLSProgressBar = new QProgressBar(optionsGroupBox);
        setOptRLSProgressBar->setObjectName(QString::fromUtf8("setOptRLSProgressBar"));
        setOptRLSProgressBar->setValue(24);

        verticalLayout->addWidget(setOptRLSProgressBar);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        setOptZDvertButton = new QPushButton(optionsGroupBox);
        setOptZDvertButton->setObjectName(QString::fromUtf8("setOptZDvertButton"));
        setOptZDvertButton->setMinimumSize(QSize(90, 30));
        setOptZDvertButton->setMaximumSize(QSize(90, 16777215));
        setOptZDvertButton->setFont(font1);

        verticalLayout_4->addWidget(setOptZDvertButton);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);


        horizontalLayout_6->addLayout(verticalLayout_4);


        horizontalLayout_2->addLayout(horizontalLayout_6);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_8);


        horizontalLayout_4->addLayout(verticalLayout);


        verticalLayout_11->addLayout(horizontalLayout_4);


        verticalLayout_13->addWidget(optionsGroupBox);

        generateDVOptTabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_14 = new QVBoxLayout(tab_4);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        ZDvertGroupBox = new QGroupBox(tab_4);
        ZDvertGroupBox->setObjectName(QString::fromUtf8("ZDvertGroupBox"));
        ZDvertGroupBox->setFont(font);
        ZDvertGroupBox->setAlignment(Qt::AlignCenter);
        verticalLayout_3 = new QVBoxLayout(ZDvertGroupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        graphicDVWidget = new QCustomPlot(ZDvertGroupBox);
        graphicDVWidget->setObjectName(QString::fromUtf8("graphicDVWidget"));
        graphicDVWidget->setMinimumSize(QSize(400, 230));

        verticalLayout_3->addWidget(graphicDVWidget);


        verticalLayout_14->addWidget(ZDvertGroupBox);

        HRLSgroupBox = new QGroupBox(tab_4);
        HRLSgroupBox->setObjectName(QString::fromUtf8("HRLSgroupBox"));
        HRLSgroupBox->setMaximumSize(QSize(16777215, 100));
        HRLSgroupBox->setFont(font);
        verticalLayout_5 = new QVBoxLayout(HRLSgroupBox);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        hZDSlider = new QSlider(HRLSgroupBox);
        hZDSlider->setObjectName(QString::fromUtf8("hZDSlider"));
        hZDSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_13->addWidget(hZDSlider);

        hZDspinBox = new QSpinBox(HRLSgroupBox);
        hZDspinBox->setObjectName(QString::fromUtf8("hZDspinBox"));
        hZDspinBox->setMinimum(5);
        hZDspinBox->setMaximum(10000);

        horizontalLayout_13->addWidget(hZDspinBox);

        mLabel_4 = new QLabel(HRLSgroupBox);
        mLabel_4->setObjectName(QString::fromUtf8("mLabel_4"));
        QFont font3;
        font3.setPointSize(16);
        mLabel_4->setFont(font3);

        horizontalLayout_13->addWidget(mLabel_4);

        colorHLabel = new QLabel(HRLSgroupBox);
        colorHLabel->setObjectName(QString::fromUtf8("colorHLabel"));
        colorHLabel->setMinimumSize(QSize(40, 30));
        colorHLabel->setMaximumSize(QSize(40, 30));

        horizontalLayout_13->addWidget(colorHLabel);


        verticalLayout_5->addLayout(horizontalLayout_13);


        verticalLayout_14->addWidget(HRLSgroupBox);

        generateDVOptTabWidget->addTab(tab_4, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        verticalLayout_2 = new QVBoxLayout(tab_6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        rlsTabWidget = new QTabWidget(tab_6);
        rlsTabWidget->setObjectName(QString::fromUtf8("rlsTabWidget"));
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        verticalLayout_17 = new QVBoxLayout(tab_5);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        coordRLSgroupBox = new QGroupBox(tab_5);
        coordRLSgroupBox->setObjectName(QString::fromUtf8("coordRLSgroupBox"));
        coordRLSgroupBox->setFont(font);
        verticalLayout_10 = new QVBoxLayout(coordRLSgroupBox);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        xRLSLabel = new QLabel(coordRLSgroupBox);
        xRLSLabel->setObjectName(QString::fromUtf8("xRLSLabel"));
        xRLSLabel->setMinimumSize(QSize(30, 0));
        xRLSLabel->setMaximumSize(QSize(30, 16777215));
        xRLSLabel->setFont(font);
        xRLSLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_15->addWidget(xRLSLabel);

        xRLSspinBox = new QSpinBox(coordRLSgroupBox);
        xRLSspinBox->setObjectName(QString::fromUtf8("xRLSspinBox"));
        xRLSspinBox->setMinimumSize(QSize(50, 0));
        xRLSspinBox->setMaximumSize(QSize(400, 16777215));
        xRLSspinBox->setMaximum(999999999);

        horizontalLayout_15->addWidget(xRLSspinBox);

        mLabel_2 = new QLabel(coordRLSgroupBox);
        mLabel_2->setObjectName(QString::fromUtf8("mLabel_2"));
        mLabel_2->setFont(font3);

        horizontalLayout_15->addWidget(mLabel_2);


        verticalLayout_10->addLayout(horizontalLayout_15);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        yRLSLabel = new QLabel(coordRLSgroupBox);
        yRLSLabel->setObjectName(QString::fromUtf8("yRLSLabel"));
        yRLSLabel->setMinimumSize(QSize(30, 0));
        yRLSLabel->setMaximumSize(QSize(30, 16777215));
        yRLSLabel->setFont(font);
        yRLSLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_14->addWidget(yRLSLabel);

        yRLSspinBox = new QSpinBox(coordRLSgroupBox);
        yRLSspinBox->setObjectName(QString::fromUtf8("yRLSspinBox"));
        yRLSspinBox->setMinimumSize(QSize(50, 0));
        yRLSspinBox->setMaximumSize(QSize(400, 16777215));
        yRLSspinBox->setMaximum(999999999);

        horizontalLayout_14->addWidget(yRLSspinBox);

        mLabel_3 = new QLabel(coordRLSgroupBox);
        mLabel_3->setObjectName(QString::fromUtf8("mLabel_3"));
        mLabel_3->setFont(font3);

        horizontalLayout_14->addWidget(mLabel_3);


        verticalLayout_10->addLayout(horizontalLayout_14);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        zRLSLabel = new QLabel(coordRLSgroupBox);
        zRLSLabel->setObjectName(QString::fromUtf8("zRLSLabel"));
        zRLSLabel->setMaximumSize(QSize(30, 16777215));
        zRLSLabel->setFont(font);
        zRLSLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_21->addWidget(zRLSLabel);

        zValueRLSLabel = new QLabel(coordRLSgroupBox);
        zValueRLSLabel->setObjectName(QString::fromUtf8("zValueRLSLabel"));

        horizontalLayout_21->addWidget(zValueRLSLabel);

        mLabel_6 = new QLabel(coordRLSgroupBox);
        mLabel_6->setObjectName(QString::fromUtf8("mLabel_6"));
        mLabel_6->setFont(font3);

        horizontalLayout_21->addWidget(mLabel_6);


        verticalLayout_10->addLayout(horizontalLayout_21);


        horizontalLayout_11->addWidget(coordRLSgroupBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_2);


        verticalLayout_17->addLayout(horizontalLayout_11);

        verticalSpacer_2 = new QSpacerItem(198, 222, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_17->addItem(verticalSpacer_2);

        rlsTabWidget->addTab(tab_5, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        rlsTabWidget->addTab(tab_7, QString());

        verticalLayout_2->addWidget(rlsTabWidget);

        generateDVOptTabWidget->addTab(tab_6, QString());

        verticalLayout_6->addWidget(generateDVOptTabWidget);

        setRLSprogressBar = new QProgressBar(mainGroupBox);
        setRLSprogressBar->setObjectName(QString::fromUtf8("setRLSprogressBar"));
        setRLSprogressBar->setValue(24);

        verticalLayout_6->addWidget(setRLSprogressBar);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_7);

        setCoordRLSpushButton = new QPushButton(mainGroupBox);
        setCoordRLSpushButton->setObjectName(QString::fromUtf8("setCoordRLSpushButton"));
        setCoordRLSpushButton->setMinimumSize(QSize(130, 30));
        setCoordRLSpushButton->setFont(font);

        horizontalLayout_16->addWidget(setCoordRLSpushButton);

        on_off_RLS_Button = new QPushButton(mainGroupBox);
        on_off_RLS_Button->setObjectName(QString::fromUtf8("on_off_RLS_Button"));
        on_off_RLS_Button->setMinimumSize(QSize(130, 30));
        on_off_RLS_Button->setFont(font);

        horizontalLayout_16->addWidget(on_off_RLS_Button);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_15);


        verticalLayout_6->addLayout(horizontalLayout_16);


        horizontalLayout_19->addWidget(mainGroupBox);


        retranslateUi(optRLSwindow);

        generateDVOptTabWidget->setCurrentIndex(2);
        tabWidget->setCurrentIndex(0);
        rlsTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(optRLSwindow);
    } // setupUi

    void retranslateUi(QWidget *optRLSwindow)
    {
        optRLSwindow->setWindowTitle(QCoreApplication::translate("optRLSwindow", "Form", nullptr));
        mainGroupBox->setTitle(QString());
        addRLSGroupBox->setTitle(QCoreApplication::translate("optRLSwindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\240\320\233\320\241", nullptr));
        nameNewRLSGroupBox->setTitle(QCoreApplication::translate("optRLSwindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        createRLSButton->setText(QCoreApplication::translate("optRLSwindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 ", nullptr));
        listRLSGroupBox->setTitle(QCoreApplication::translate("optRLSwindow", "\320\241\320\277\320\270\321\201\320\276\320\272 \320\240\320\233\320\241", nullptr));
        removeRLSButton->setText(QCoreApplication::translate("optRLSwindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        optionsGroupBox->setTitle(QCoreApplication::translate("optRLSwindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", nullptr));
        RmaxGroupBox->setTitle(QCoreApplication::translate("optRLSwindow", "Rmax:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("optRLSwindow", "\320\220\320\275\321\202\320\265\320\275\321\213", nullptr));
        deltaZDGroupBox->setTitle(QCoreApplication::translate("optRLSwindow", "\320\224\320\270\321\201\320\272\321\200\320\265\321\202\320\275\320\276\321\201\321\202\321\214", nullptr));
        groupBox->setTitle(QCoreApplication::translate("optRLSwindow", "\320\223\320\276\321\200\320\270\320\267\320\276\320\275\321\202\320\260\320\273\321\214\320\275\321\213\320\265 \320\264\320\270\321\201\320\272\321\200\320\265\321\202\321\213", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("optRLSwindow", "\320\222\320\265\321\200\321\202\320\270\320\272\320\260\320\273\321\214\320\275\321\213\320\265 \320\264\320\270\321\201\320\272\321\200\320\265\321\202\321\213", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("optRLSwindow", "\320\234\320\276\320\264\320\265\320\273\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217 \321\201\320\270\320\263\320\275\320\260\320\273\320\260", nullptr));
        setOptZDvertButton->setText(QCoreApplication::translate("optRLSwindow", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        generateDVOptTabWidget->setTabText(generateDVOptTabWidget->indexOf(tab_3), QCoreApplication::translate("optRLSwindow", "\320\241\320\270\320\263\320\275\320\260\320\273", nullptr));
        ZDvertGroupBox->setTitle(QCoreApplication::translate("optRLSwindow", "\320\227\320\276\320\275\320\260 \320\276\320\261\320\275\320\260\321\200\321\203\320\266\320\265\320\275\320\270\321\217 \320\262 \320\262\320\265\321\200\321\202\320\270\320\272\320\260\320\273\321\214\320\275\320\276\320\271 \320\277\320\273\320\276\321\201\320\272\320\276\321\201\321\202\320\270", nullptr));
        HRLSgroupBox->setTitle(QCoreApplication::translate("optRLSwindow", "\320\241\321\200\320\265\320\267 \320\262\321\213\321\201\320\276\321\202\321\213 \320\227\320\236", nullptr));
        mLabel_4->setText(QCoreApplication::translate("optRLSwindow", "\320\274", nullptr));
        colorHLabel->setText(QString());
        generateDVOptTabWidget->setTabText(generateDVOptTabWidget->indexOf(tab_4), QCoreApplication::translate("optRLSwindow", "\320\227\320\276\320\275\320\260 \320\276\320\261\320\275\320\260\321\200\321\203\320\266\320\265\320\275\320\270\321\217", nullptr));
        coordRLSgroupBox->setTitle(QCoreApplication::translate("optRLSwindow", "\320\232\320\276\320\276\321\200\320\264\320\270\320\275\320\260\321\202\321\213", nullptr));
        xRLSLabel->setText(QCoreApplication::translate("optRLSwindow", "X:", nullptr));
        mLabel_2->setText(QCoreApplication::translate("optRLSwindow", "\320\274", nullptr));
        yRLSLabel->setText(QCoreApplication::translate("optRLSwindow", "Y:", nullptr));
        mLabel_3->setText(QCoreApplication::translate("optRLSwindow", "\320\274", nullptr));
        zRLSLabel->setText(QCoreApplication::translate("optRLSwindow", "Z:", nullptr));
        zValueRLSLabel->setText(QCoreApplication::translate("optRLSwindow", "--", nullptr));
        mLabel_6->setText(QCoreApplication::translate("optRLSwindow", "\320\274", nullptr));
        rlsTabWidget->setTabText(rlsTabWidget->indexOf(tab_5), QCoreApplication::translate("optRLSwindow", "\320\237\320\276\320\267\320\270\321\206\320\270\321\217", nullptr));
        rlsTabWidget->setTabText(rlsTabWidget->indexOf(tab_7), QCoreApplication::translate("optRLSwindow", "Tab 2", nullptr));
        generateDVOptTabWidget->setTabText(generateDVOptTabWidget->indexOf(tab_6), QCoreApplication::translate("optRLSwindow", "\320\240\320\233\320\241", nullptr));
        setCoordRLSpushButton->setText(QCoreApplication::translate("optRLSwindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        on_off_RLS_Button->setText(QCoreApplication::translate("optRLSwindow", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class optRLSwindow: public Ui_optRLSwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTRLSWINDOW_H
