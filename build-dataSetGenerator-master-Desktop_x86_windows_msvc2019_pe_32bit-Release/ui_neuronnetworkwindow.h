/********************************************************************************
** Form generated from reading UI file 'neuronnetworkwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEURONNETWORKWINDOW_H
#define UI_NEURONNETWORKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_neuronNetworkWindow
{
public:
    QHBoxLayout *horizontalLayout_15;
    QGroupBox *mainGroupBox;
    QHBoxLayout *horizontalLayout_5;
    QTabWidget *mainTabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *predictModelGroupBox;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *nameModelComboBox;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *predictButton;
    QComboBox *typePredictComboBox;
    QSpacerItem *horizontalSpacer_2;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *modelGroupBox;
    QHBoxLayout *horizontalLayout_9;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *nameBuildModelLineEdit;
    QSpacerItem *horizontalSpacer_10;
    QGroupBox *dataGroupBox;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *dataTabWidget;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_11;
    QGroupBox *groupBox_8;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *patchInputDataLineEdit;
    QPushButton *setDirInputDataButton;
    QWidget *tab_4;
    QHBoxLayout *horizontalLayout_12;
    QGroupBox *groupBox_9;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *patchRewardDataLineEdit;
    QPushButton *setDirRewardDataButton;
    QHBoxLayout *horizontalLayout_14;
    QGroupBox *groupBox_10;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_6;
    QLabel *sizeDSLabel;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_7;
    QGroupBox *optTrainGroupBox;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_11;
    QHBoxLayout *horizontalLayout_16;
    QSpinBox *countEpochSpinBox;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *trainNetButton;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *neuronNetworkWindow)
    {
        if (neuronNetworkWindow->objectName().isEmpty())
            neuronNetworkWindow->setObjectName(QString::fromUtf8("neuronNetworkWindow"));
        neuronNetworkWindow->resize(546, 593);
        horizontalLayout_15 = new QHBoxLayout(neuronNetworkWindow);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        mainGroupBox = new QGroupBox(neuronNetworkWindow);
        mainGroupBox->setObjectName(QString::fromUtf8("mainGroupBox"));
        horizontalLayout_5 = new QHBoxLayout(mainGroupBox);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        mainTabWidget = new QTabWidget(mainGroupBox);
        mainTabWidget->setObjectName(QString::fromUtf8("mainTabWidget"));
        QFont font;
        font.setPointSize(12);
        mainTabWidget->setFont(font);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        predictModelGroupBox = new QGroupBox(tab);
        predictModelGroupBox->setObjectName(QString::fromUtf8("predictModelGroupBox"));
        predictModelGroupBox->setFont(font);
        horizontalLayout_2 = new QHBoxLayout(predictModelGroupBox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        nameModelComboBox = new QComboBox(predictModelGroupBox);
        nameModelComboBox->setObjectName(QString::fromUtf8("nameModelComboBox"));
        nameModelComboBox->setFont(font);

        horizontalLayout_2->addWidget(nameModelComboBox);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_9);


        horizontalLayout_4->addWidget(predictModelGroupBox);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        predictButton = new QPushButton(tab);
        predictButton->setObjectName(QString::fromUtf8("predictButton"));
        predictButton->setFont(font);

        horizontalLayout->addWidget(predictButton);

        typePredictComboBox = new QComboBox(tab);
        typePredictComboBox->setObjectName(QString::fromUtf8("typePredictComboBox"));
        typePredictComboBox->setMinimumSize(QSize(0, 25));

        horizontalLayout->addWidget(typePredictComboBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        mainTabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        modelGroupBox = new QGroupBox(tab_2);
        modelGroupBox->setObjectName(QString::fromUtf8("modelGroupBox"));
        QFont font1;
        font1.setPointSize(13);
        modelGroupBox->setFont(font1);
        horizontalLayout_9 = new QHBoxLayout(modelGroupBox);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        groupBox_5 = new QGroupBox(modelGroupBox);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setMaximumSize(QSize(150, 16777215));
        groupBox_5->setFont(font);
        horizontalLayout_6 = new QHBoxLayout(groupBox_5);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        nameBuildModelLineEdit = new QLineEdit(groupBox_5);
        nameBuildModelLineEdit->setObjectName(QString::fromUtf8("nameBuildModelLineEdit"));
        nameBuildModelLineEdit->setMaximumSize(QSize(16777215, 16777215));
        nameBuildModelLineEdit->setFont(font);

        horizontalLayout_6->addWidget(nameBuildModelLineEdit);


        horizontalLayout_9->addWidget(groupBox_5);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_10);


        verticalLayout_3->addWidget(modelGroupBox);

        dataGroupBox = new QGroupBox(tab_2);
        dataGroupBox->setObjectName(QString::fromUtf8("dataGroupBox"));
        dataGroupBox->setFont(font1);
        verticalLayout_2 = new QVBoxLayout(dataGroupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        dataTabWidget = new QTabWidget(dataGroupBox);
        dataTabWidget->setObjectName(QString::fromUtf8("dataTabWidget"));
        dataTabWidget->setFont(font);
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        horizontalLayout_11 = new QHBoxLayout(tab_3);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        groupBox_8 = new QGroupBox(tab_3);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setFont(font);
        horizontalLayout_7 = new QHBoxLayout(groupBox_8);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        patchInputDataLineEdit = new QLineEdit(groupBox_8);
        patchInputDataLineEdit->setObjectName(QString::fromUtf8("patchInputDataLineEdit"));
        patchInputDataLineEdit->setFont(font);

        horizontalLayout_7->addWidget(patchInputDataLineEdit);

        setDirInputDataButton = new QPushButton(groupBox_8);
        setDirInputDataButton->setObjectName(QString::fromUtf8("setDirInputDataButton"));
        setDirInputDataButton->setMinimumSize(QSize(35, 0));
        setDirInputDataButton->setMaximumSize(QSize(35, 16777215));
        QFont font2;
        font2.setPointSize(13);
        font2.setBold(true);
        font2.setWeight(75);
        setDirInputDataButton->setFont(font2);

        horizontalLayout_7->addWidget(setDirInputDataButton);


        horizontalLayout_11->addWidget(groupBox_8);

        dataTabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        horizontalLayout_12 = new QHBoxLayout(tab_4);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        groupBox_9 = new QGroupBox(tab_4);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setFont(font);
        horizontalLayout_10 = new QHBoxLayout(groupBox_9);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        patchRewardDataLineEdit = new QLineEdit(groupBox_9);
        patchRewardDataLineEdit->setObjectName(QString::fromUtf8("patchRewardDataLineEdit"));
        patchRewardDataLineEdit->setFont(font);

        horizontalLayout_10->addWidget(patchRewardDataLineEdit);

        setDirRewardDataButton = new QPushButton(groupBox_9);
        setDirRewardDataButton->setObjectName(QString::fromUtf8("setDirRewardDataButton"));
        setDirRewardDataButton->setMinimumSize(QSize(35, 0));
        setDirRewardDataButton->setMaximumSize(QSize(35, 16777215));
        setDirRewardDataButton->setFont(font2);

        horizontalLayout_10->addWidget(setDirRewardDataButton);


        horizontalLayout_12->addWidget(groupBox_9);

        dataTabWidget->addTab(tab_4, QString());

        verticalLayout_2->addWidget(dataTabWidget);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        groupBox_10 = new QGroupBox(dataGroupBox);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        groupBox_10->setFont(font);
        horizontalLayout_13 = new QHBoxLayout(groupBox_10);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_6);

        sizeDSLabel = new QLabel(groupBox_10);
        sizeDSLabel->setObjectName(QString::fromUtf8("sizeDSLabel"));
        sizeDSLabel->setFont(font);

        horizontalLayout_13->addWidget(sizeDSLabel);

        horizontalSpacer_5 = new QSpacerItem(161, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_5);


        horizontalLayout_14->addWidget(groupBox_10);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_7);


        verticalLayout_2->addLayout(horizontalLayout_14);


        verticalLayout_3->addWidget(dataGroupBox);

        optTrainGroupBox = new QGroupBox(tab_2);
        optTrainGroupBox->setObjectName(QString::fromUtf8("optTrainGroupBox"));
        horizontalLayout_3 = new QHBoxLayout(optTrainGroupBox);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBox_11 = new QGroupBox(optTrainGroupBox);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        horizontalLayout_16 = new QHBoxLayout(groupBox_11);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        countEpochSpinBox = new QSpinBox(groupBox_11);
        countEpochSpinBox->setObjectName(QString::fromUtf8("countEpochSpinBox"));
        countEpochSpinBox->setMinimum(1);

        horizontalLayout_16->addWidget(countEpochSpinBox);


        horizontalLayout_3->addWidget(groupBox_11);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);


        verticalLayout_3->addWidget(optTrainGroupBox);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);

        trainNetButton = new QPushButton(tab_2);
        trainNetButton->setObjectName(QString::fromUtf8("trainNetButton"));
        trainNetButton->setFont(font);

        horizontalLayout_8->addWidget(trainNetButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_8);

        mainTabWidget->addTab(tab_2, QString());

        horizontalLayout_5->addWidget(mainTabWidget);


        horizontalLayout_15->addWidget(mainGroupBox);


        retranslateUi(neuronNetworkWindow);

        mainTabWidget->setCurrentIndex(1);
        dataTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(neuronNetworkWindow);
    } // setupUi

    void retranslateUi(QWidget *neuronNetworkWindow)
    {
        neuronNetworkWindow->setWindowTitle(QCoreApplication::translate("neuronNetworkWindow", "Form", nullptr));
        mainGroupBox->setTitle(QString());
        predictModelGroupBox->setTitle(QCoreApplication::translate("neuronNetworkWindow", "\320\234\320\276\320\264\320\265\320\273\321\214", nullptr));
        predictButton->setText(QCoreApplication::translate("neuronNetworkWindow", "\320\237\321\200\320\276\320\263\320\275\320\276\320\267\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(tab), QCoreApplication::translate("neuronNetworkWindow", "\320\237\321\200\320\276\320\263\320\275\320\276\320\267", nullptr));
        modelGroupBox->setTitle(QCoreApplication::translate("neuronNetworkWindow", "\320\234\320\276\320\264\320\265\320\273\321\214", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("neuronNetworkWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        dataGroupBox->setTitle(QCoreApplication::translate("neuronNetworkWindow", "\320\224\320\260\320\275\320\275\321\213\320\265 ", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("neuronNetworkWindow", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217", nullptr));
        setDirInputDataButton->setText(QCoreApplication::translate("neuronNetworkWindow", "...", nullptr));
        dataTabWidget->setTabText(dataTabWidget->indexOf(tab_3), QCoreApplication::translate("neuronNetworkWindow", "\320\222\321\205\320\276\320\264\320\275\321\213\320\265 \320\276\320\261\321\200\320\260\320\267\321\213", nullptr));
        groupBox_9->setTitle(QCoreApplication::translate("neuronNetworkWindow", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217", nullptr));
        setDirRewardDataButton->setText(QCoreApplication::translate("neuronNetworkWindow", "...", nullptr));
        dataTabWidget->setTabText(dataTabWidget->indexOf(tab_4), QCoreApplication::translate("neuronNetworkWindow", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\321\217 \320\246\320\244", nullptr));
        groupBox_10->setTitle(QCoreApplication::translate("neuronNetworkWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 \320\276\320\261\321\203\321\207. \320\262\321\213\320\261\320\276\321\200\320\272\320\270", nullptr));
        sizeDSLabel->setText(QCoreApplication::translate("neuronNetworkWindow", "---", nullptr));
        optTrainGroupBox->setTitle(QCoreApplication::translate("neuronNetworkWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\276\320\261\321\203\321\207\320\265\320\275\320\270\321\217", nullptr));
        groupBox_11->setTitle(QCoreApplication::translate("neuronNetworkWindow", "\320\255\320\277\320\276\321\205\320\270", nullptr));
        trainNetButton->setText(QCoreApplication::translate("neuronNetworkWindow", "\320\236\320\261\321\203\321\207\320\270\321\202\321\214", nullptr));
        mainTabWidget->setTabText(mainTabWidget->indexOf(tab_2), QCoreApplication::translate("neuronNetworkWindow", "\320\236\320\261\321\203\321\207\320\265\320\275\320\270\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class neuronNetworkWindow: public Ui_neuronNetworkWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEURONNETWORKWINDOW_H
