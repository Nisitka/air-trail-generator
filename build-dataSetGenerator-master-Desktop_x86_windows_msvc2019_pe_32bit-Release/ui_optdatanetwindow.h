/********************************************************************************
** Form generated from reading UI file 'optdatanetwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTDATANETWINDOW_H
#define UI_OPTDATANETWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_optDataNetWindow
{
public:
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *mainGroupBox;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *rgbGroupBox;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *Label_1;
    QSlider *kG1Slider;
    QHBoxLayout *horizontalLayout_5;
    QLabel *Label_2;
    QSlider *kG2Slider;
    QHBoxLayout *horizontalLayout_6;
    QLabel *Label_3;
    QSlider *kG3Slider;
    QHBoxLayout *horizontalLayout_7;
    QLabel *Label_4;
    QSlider *kG4Slider;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *setDefaultKrgbButton;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *buildDataGroupBox;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *genDataNetButton;
    QSpacerItem *horizontalSpacer;
    QProgressBar *genDNProgressBar;

    void setupUi(QWidget *optDataNetWindow)
    {
        if (optDataNetWindow->objectName().isEmpty())
            optDataNetWindow->setObjectName(QString::fromUtf8("optDataNetWindow"));
        optDataNetWindow->resize(335, 390);
        horizontalLayout_8 = new QHBoxLayout(optDataNetWindow);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        mainGroupBox = new QGroupBox(optDataNetWindow);
        mainGroupBox->setObjectName(QString::fromUtf8("mainGroupBox"));
        verticalLayout_2 = new QVBoxLayout(mainGroupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        rgbGroupBox = new QGroupBox(mainGroupBox);
        rgbGroupBox->setObjectName(QString::fromUtf8("rgbGroupBox"));
        QFont font;
        font.setPointSize(12);
        rgbGroupBox->setFont(font);
        verticalLayout = new QVBoxLayout(rgbGroupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(rgbGroupBox);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QFont font1;
        font1.setPointSize(11);
        tabWidget->setFont(font1);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        Label_1 = new QLabel(tab_2);
        Label_1->setObjectName(QString::fromUtf8("Label_1"));
        Label_1->setMaximumSize(QSize(30, 16777215));
        Label_1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(Label_1);

        kG1Slider = new QSlider(tab_2);
        kG1Slider->setObjectName(QString::fromUtf8("kG1Slider"));
        kG1Slider->setMinimum(1);
        kG1Slider->setMaximum(1000);
        kG1Slider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(kG1Slider);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        Label_2 = new QLabel(tab_2);
        Label_2->setObjectName(QString::fromUtf8("Label_2"));
        Label_2->setMaximumSize(QSize(30, 16777215));
        Label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(Label_2);

        kG2Slider = new QSlider(tab_2);
        kG2Slider->setObjectName(QString::fromUtf8("kG2Slider"));
        kG2Slider->setMinimum(1);
        kG2Slider->setMaximum(1000);
        kG2Slider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(kG2Slider);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        Label_3 = new QLabel(tab_2);
        Label_3->setObjectName(QString::fromUtf8("Label_3"));
        Label_3->setMaximumSize(QSize(30, 16777215));
        Label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(Label_3);

        kG3Slider = new QSlider(tab_2);
        kG3Slider->setObjectName(QString::fromUtf8("kG3Slider"));
        kG3Slider->setMinimum(1);
        kG3Slider->setMaximum(1000);
        kG3Slider->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(kG3Slider);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        Label_4 = new QLabel(tab_2);
        Label_4->setObjectName(QString::fromUtf8("Label_4"));
        Label_4->setMaximumSize(QSize(30, 16777215));
        Label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(Label_4);

        kG4Slider = new QSlider(tab_2);
        kG4Slider->setObjectName(QString::fromUtf8("kG4Slider"));
        kG4Slider->setMinimum(1);
        kG4Slider->setMaximum(1000);
        kG4Slider->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(kG4Slider);


        verticalLayout_3->addLayout(horizontalLayout_7);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tabWidget->addTab(tab_3, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        setDefaultKrgbButton = new QPushButton(rgbGroupBox);
        setDefaultKrgbButton->setObjectName(QString::fromUtf8("setDefaultKrgbButton"));
        setDefaultKrgbButton->setMinimumSize(QSize(65, 30));
        setDefaultKrgbButton->setMaximumSize(QSize(65, 16777215));
        setDefaultKrgbButton->setFont(font1);

        horizontalLayout_3->addWidget(setDefaultKrgbButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addWidget(rgbGroupBox);

        buildDataGroupBox = new QGroupBox(mainGroupBox);
        buildDataGroupBox->setObjectName(QString::fromUtf8("buildDataGroupBox"));
        buildDataGroupBox->setFont(font);
        verticalLayout_4 = new QVBoxLayout(buildDataGroupBox);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        genDataNetButton = new QPushButton(buildDataGroupBox);
        genDataNetButton->setObjectName(QString::fromUtf8("genDataNetButton"));
        genDataNetButton->setMinimumSize(QSize(100, 30));
        genDataNetButton->setFont(font);

        horizontalLayout->addWidget(genDataNetButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(horizontalLayout);

        genDNProgressBar = new QProgressBar(buildDataGroupBox);
        genDNProgressBar->setObjectName(QString::fromUtf8("genDNProgressBar"));
        genDNProgressBar->setValue(24);

        verticalLayout_4->addWidget(genDNProgressBar);


        verticalLayout_2->addWidget(buildDataGroupBox);


        horizontalLayout_8->addWidget(mainGroupBox);


        retranslateUi(optDataNetWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(optDataNetWindow);
    } // setupUi

    void retranslateUi(QWidget *optDataNetWindow)
    {
        optDataNetWindow->setWindowTitle(QCoreApplication::translate("optDataNetWindow", "Form", nullptr));
        mainGroupBox->setTitle(QString());
        rgbGroupBox->setTitle(QCoreApplication::translate("optDataNetWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \321\206\320\262\320\265\321\202\320\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("optDataNetWindow", "\320\240\320\265\320\273\321\214\320\265\321\204", nullptr));
        Label_1->setText(QCoreApplication::translate("optDataNetWindow", "K1:", nullptr));
        Label_2->setText(QCoreApplication::translate("optDataNetWindow", "K2:", nullptr));
        Label_3->setText(QCoreApplication::translate("optDataNetWindow", "K3:", nullptr));
        Label_4->setText(QCoreApplication::translate("optDataNetWindow", "K4:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("optDataNetWindow", "\320\234\320\260\320\275\320\265\320\262\321\200", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("optDataNetWindow", "\320\240\320\233\320\241", nullptr));
        setDefaultKrgbButton->setText(QCoreApplication::translate("optDataNetWindow", "\320\241\320\261\321\200\320\276\321\201", nullptr));
        buildDataGroupBox->setTitle(QCoreApplication::translate("optDataNetWindow", "\320\223\320\265\320\275\320\265\321\200\320\260\321\206\320\270\321\217 \320\276\320\261\321\200\320\260\320\267\320\260", nullptr));
        genDataNetButton->setText(QCoreApplication::translate("optDataNetWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class optDataNetWindow: public Ui_optDataNetWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTDATANETWINDOW_H
