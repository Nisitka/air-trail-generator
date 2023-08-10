/********************************************************************************
** Form generated from reading UI file 'optmapgeneratorwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTMAPGENERATORWINDOW_H
#define UI_OPTMAPGENERATORWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_optMapGeneratorWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QGroupBox *mainGroupBox;
    QHBoxLayout *horizontalLayout_10;
    QTabWidget *optTabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *geoGroupBox;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *pBuildBlockGroupBox;
    QVBoxLayout *verticalLayout_19;
    QDoubleSpinBox *pBuildBlockSpinBox;
    QGroupBox *countEpochsGroupBox;
    QVBoxLayout *verticalLayout_20;
    QSpinBox *countEpochsSpinBox;
    QGroupBox *optBlocksGroupBox;
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *mapGroupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *wMapLabel;
    QSpinBox *countWidBlocksSpinBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lMapLabel;
    QSpinBox *countLenBlocksSpinBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *hMapLabel;
    QSpinBox *countHeiBlocksSpinBox;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_7;
    QDoubleSpinBox *lenBlockSpinBox;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_17;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *generateNewGbutton;
    QSpacerItem *horizontalSpacer_17;
    QProgressBar *buildProgressBar;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *dirOpenMapGroupBox;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *dirMapLineEdit;
    QPushButton *setDirNameMapButton;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_4;
    QPushButton *openMapButton;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *optMapGeneratorWindow)
    {
        if (optMapGeneratorWindow->objectName().isEmpty())
            optMapGeneratorWindow->setObjectName(QString::fromUtf8("optMapGeneratorWindow"));
        optMapGeneratorWindow->resize(450, 470);
        horizontalLayout = new QHBoxLayout(optMapGeneratorWindow);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        mainGroupBox = new QGroupBox(optMapGeneratorWindow);
        mainGroupBox->setObjectName(QString::fromUtf8("mainGroupBox"));
        horizontalLayout_10 = new QHBoxLayout(mainGroupBox);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        optTabWidget = new QTabWidget(mainGroupBox);
        optTabWidget->setObjectName(QString::fromUtf8("optTabWidget"));
        QFont font;
        font.setPointSize(12);
        optTabWidget->setFont(font);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_7 = new QVBoxLayout(tab);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        geoGroupBox = new QGroupBox(tab);
        geoGroupBox->setObjectName(QString::fromUtf8("geoGroupBox"));
        QFont font1;
        font1.setPointSize(14);
        geoGroupBox->setFont(font1);
        geoGroupBox->setAlignment(Qt::AlignCenter);
        verticalLayout_6 = new QVBoxLayout(geoGroupBox);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pBuildBlockGroupBox = new QGroupBox(geoGroupBox);
        pBuildBlockGroupBox->setObjectName(QString::fromUtf8("pBuildBlockGroupBox"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Adobe Arabic"));
        font2.setPointSize(12);
        pBuildBlockGroupBox->setFont(font2);
        pBuildBlockGroupBox->setAlignment(Qt::AlignCenter);
        verticalLayout_19 = new QVBoxLayout(pBuildBlockGroupBox);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        pBuildBlockSpinBox = new QDoubleSpinBox(pBuildBlockGroupBox);
        pBuildBlockSpinBox->setObjectName(QString::fromUtf8("pBuildBlockSpinBox"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Adobe Arabic"));
        font3.setPointSize(14);
        font3.setBold(false);
        font3.setWeight(50);
        pBuildBlockSpinBox->setFont(font3);
        pBuildBlockSpinBox->setDecimals(3);
        pBuildBlockSpinBox->setMinimum(0.010000000000000);
        pBuildBlockSpinBox->setMaximum(0.990000000000000);
        pBuildBlockSpinBox->setSingleStep(0.001000000000000);
        pBuildBlockSpinBox->setValue(0.200000000000000);

        verticalLayout_19->addWidget(pBuildBlockSpinBox);


        horizontalLayout_3->addWidget(pBuildBlockGroupBox);

        countEpochsGroupBox = new QGroupBox(geoGroupBox);
        countEpochsGroupBox->setObjectName(QString::fromUtf8("countEpochsGroupBox"));
        countEpochsGroupBox->setFont(font2);
        countEpochsGroupBox->setAlignment(Qt::AlignCenter);
        verticalLayout_20 = new QVBoxLayout(countEpochsGroupBox);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        countEpochsSpinBox = new QSpinBox(countEpochsGroupBox);
        countEpochsSpinBox->setObjectName(QString::fromUtf8("countEpochsSpinBox"));
        countEpochsSpinBox->setFont(font3);
        countEpochsSpinBox->setMinimum(1);
        countEpochsSpinBox->setMaximum(300);
        countEpochsSpinBox->setValue(100);

        verticalLayout_20->addWidget(countEpochsSpinBox);


        horizontalLayout_3->addWidget(countEpochsGroupBox);


        verticalLayout_6->addLayout(horizontalLayout_3);


        verticalLayout_7->addWidget(geoGroupBox);

        optBlocksGroupBox = new QGroupBox(tab);
        optBlocksGroupBox->setObjectName(QString::fromUtf8("optBlocksGroupBox"));
        optBlocksGroupBox->setFont(font1);
        optBlocksGroupBox->setAlignment(Qt::AlignCenter);
        horizontalLayout_6 = new QHBoxLayout(optBlocksGroupBox);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        mapGroupBox = new QGroupBox(optBlocksGroupBox);
        mapGroupBox->setObjectName(QString::fromUtf8("mapGroupBox"));
        mapGroupBox->setFont(font);
        mapGroupBox->setAlignment(Qt::AlignCenter);
        verticalLayout_2 = new QVBoxLayout(mapGroupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        wMapLabel = new QLabel(mapGroupBox);
        wMapLabel->setObjectName(QString::fromUtf8("wMapLabel"));
        wMapLabel->setFont(font);
        wMapLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(wMapLabel);

        countWidBlocksSpinBox = new QSpinBox(mapGroupBox);
        countWidBlocksSpinBox->setObjectName(QString::fromUtf8("countWidBlocksSpinBox"));
        countWidBlocksSpinBox->setFont(font3);
        countWidBlocksSpinBox->setMinimum(10);
        countWidBlocksSpinBox->setMaximum(2000);
        countWidBlocksSpinBox->setValue(200);

        horizontalLayout_2->addWidget(countWidBlocksSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        lMapLabel = new QLabel(mapGroupBox);
        lMapLabel->setObjectName(QString::fromUtf8("lMapLabel"));
        lMapLabel->setFont(font);
        lMapLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(lMapLabel);

        countLenBlocksSpinBox = new QSpinBox(mapGroupBox);
        countLenBlocksSpinBox->setObjectName(QString::fromUtf8("countLenBlocksSpinBox"));
        countLenBlocksSpinBox->setFont(font3);
        countLenBlocksSpinBox->setMinimum(10);
        countLenBlocksSpinBox->setMaximum(2000);
        countLenBlocksSpinBox->setValue(200);

        horizontalLayout_4->addWidget(countLenBlocksSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        hMapLabel = new QLabel(mapGroupBox);
        hMapLabel->setObjectName(QString::fromUtf8("hMapLabel"));
        hMapLabel->setFont(font);
        hMapLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(hMapLabel);

        countHeiBlocksSpinBox = new QSpinBox(mapGroupBox);
        countHeiBlocksSpinBox->setObjectName(QString::fromUtf8("countHeiBlocksSpinBox"));
        countHeiBlocksSpinBox->setFont(font3);
        countHeiBlocksSpinBox->setMinimum(10);
        countHeiBlocksSpinBox->setMaximum(500);
        countHeiBlocksSpinBox->setValue(200);

        horizontalLayout_5->addWidget(countHeiBlocksSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_5);


        horizontalLayout_6->addWidget(mapGroupBox);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox = new QGroupBox(optBlocksGroupBox);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFont(font);
        groupBox->setAlignment(Qt::AlignCenter);
        horizontalLayout_7 = new QHBoxLayout(groupBox);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        lenBlockSpinBox = new QDoubleSpinBox(groupBox);
        lenBlockSpinBox->setObjectName(QString::fromUtf8("lenBlockSpinBox"));
        lenBlockSpinBox->setFont(font);
        lenBlockSpinBox->setMinimum(5.000000000000000);
        lenBlockSpinBox->setMaximum(100.000000000000000);

        horizontalLayout_7->addWidget(lenBlockSpinBox);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        horizontalLayout_7->addWidget(label);


        verticalLayout_3->addWidget(groupBox);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        horizontalLayout_6->addLayout(verticalLayout_3);


        verticalLayout_7->addWidget(optBlocksGroupBox);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_3);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_14);

        generateNewGbutton = new QPushButton(tab);
        generateNewGbutton->setObjectName(QString::fromUtf8("generateNewGbutton"));
        generateNewGbutton->setMinimumSize(QSize(120, 30));
        generateNewGbutton->setFont(font);

        horizontalLayout_17->addWidget(generateNewGbutton);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_17);


        verticalLayout_7->addLayout(horizontalLayout_17);

        buildProgressBar = new QProgressBar(tab);
        buildProgressBar->setObjectName(QString::fromUtf8("buildProgressBar"));
        buildProgressBar->setValue(24);

        verticalLayout_7->addWidget(buildProgressBar);

        optTabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_8 = new QVBoxLayout(tab_2);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        dirOpenMapGroupBox = new QGroupBox(tab_2);
        dirOpenMapGroupBox->setObjectName(QString::fromUtf8("dirOpenMapGroupBox"));
        horizontalLayout_8 = new QHBoxLayout(dirOpenMapGroupBox);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        dirMapLineEdit = new QLineEdit(dirOpenMapGroupBox);
        dirMapLineEdit->setObjectName(QString::fromUtf8("dirMapLineEdit"));
        dirMapLineEdit->setFont(font);

        horizontalLayout_8->addWidget(dirMapLineEdit);

        setDirNameMapButton = new QPushButton(dirOpenMapGroupBox);
        setDirNameMapButton->setObjectName(QString::fromUtf8("setDirNameMapButton"));
        setDirNameMapButton->setMinimumSize(QSize(40, 0));
        setDirNameMapButton->setMaximumSize(QSize(40, 16777215));
        QFont font4;
        font4.setPointSize(16);
        font4.setBold(true);
        font4.setWeight(75);
        setDirNameMapButton->setFont(font4);

        horizontalLayout_8->addWidget(setDirNameMapButton);


        verticalLayout_8->addWidget(dirOpenMapGroupBox);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        openMapButton = new QPushButton(tab_2);
        openMapButton->setObjectName(QString::fromUtf8("openMapButton"));
        openMapButton->setMaximumSize(QSize(80, 16777215));
        openMapButton->setFont(font);

        verticalLayout_4->addWidget(openMapButton);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);


        horizontalLayout_9->addLayout(verticalLayout_4);


        verticalLayout_8->addLayout(horizontalLayout_9);

        optTabWidget->addTab(tab_2, QString());
        dirOpenMapGroupBox->raise();

        horizontalLayout_10->addWidget(optTabWidget);


        horizontalLayout->addWidget(mainGroupBox);


        retranslateUi(optMapGeneratorWindow);

        optTabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(optMapGeneratorWindow);
    } // setupUi

    void retranslateUi(QWidget *optMapGeneratorWindow)
    {
        optMapGeneratorWindow->setWindowTitle(QCoreApplication::translate("optMapGeneratorWindow", "Form", nullptr));
        mainGroupBox->setTitle(QString());
        geoGroupBox->setTitle(QCoreApplication::translate("optMapGeneratorWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\263\320\265\320\275\320\265\321\200\320\260\321\206\320\270\320\270 \320\261\320\273\320\276\320\272\320\276\320\262 (\320\272\320\273\320\265\321\202\320\276\320\272)", nullptr));
        pBuildBlockGroupBox->setTitle(QCoreApplication::translate("optMapGeneratorWindow", "\320\240 \320\277\320\276\321\217\320\262\320\273\320\265\320\275\320\270\321\217 \320\272\320\273\320\265\321\202\320\272\320\270", nullptr));
        countEpochsGroupBox->setTitle(QCoreApplication::translate("optMapGeneratorWindow", "\320\232\320\276\320\273\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\215\320\277\320\276\321\205", nullptr));
        optBlocksGroupBox->setTitle(QCoreApplication::translate("optMapGeneratorWindow", "\320\240\320\265\320\273\321\214\320\265\321\204", nullptr));
        mapGroupBox->setTitle(QCoreApplication::translate("optMapGeneratorWindow", "\320\240\320\260\320\267\320\274\320\265\321\200\321\213 \320\262 \320\261\320\273\320\276\320\272\320\260\321\205", nullptr));
        wMapLabel->setText(QCoreApplication::translate("optMapGeneratorWindow", "\320\250\320\270\321\200\320\270\320\275\320\260:", nullptr));
        lMapLabel->setText(QCoreApplication::translate("optMapGeneratorWindow", "\320\224\320\273\320\270\320\275\320\260:", nullptr));
        hMapLabel->setText(QCoreApplication::translate("optMapGeneratorWindow", "\320\222\321\213\321\201\320\276\321\202\320\260:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("optMapGeneratorWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261", nullptr));
        label->setText(QCoreApplication::translate("optMapGeneratorWindow", "\321\201\321\202\320\276\321\200\320\276\320\275\320\260 \320\272\321\203\320\261\320\260", nullptr));
        generateNewGbutton->setText(QCoreApplication::translate("optMapGeneratorWindow", "\320\235\320\276\320\262\321\213\320\271 \321\200\320\265\320\273\321\214\320\265\321\204", nullptr));
        optTabWidget->setTabText(optTabWidget->indexOf(tab), QCoreApplication::translate("optMapGeneratorWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        dirOpenMapGroupBox->setTitle(QCoreApplication::translate("optMapGeneratorWindow", "\320\237\321\203\321\202\321\214", nullptr));
        setDirNameMapButton->setText(QCoreApplication::translate("optMapGeneratorWindow", "...", nullptr));
        openMapButton->setText(QCoreApplication::translate("optMapGeneratorWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        optTabWidget->setTabText(optTabWidget->indexOf(tab_2), QCoreApplication::translate("optMapGeneratorWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class optMapGeneratorWindow: public Ui_optMapGeneratorWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTMAPGENERATORWINDOW_H
