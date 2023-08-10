/********************************************************************************
** Form generated from reading UI file 'optbuilddatasetwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTBUILDDATASETWINDOW_H
#define UI_OPTBUILDDATASETWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_optBuildDataSetWindow
{
public:
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *mainGroupBox;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *dirsDataSetGroupBox;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_9;
    QLineEdit *netImagesDirLineEdit;
    QPushButton *setDirNetImgButton;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *qFunDirLineEdit;
    QPushButton *setDirQFunButton;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *sizeDSGroupBox;
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QSpinBox *countMapSpinBox;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_5;
    QSpinBox *countRectSpinBox;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *sizeDataSetLabel;
    QLabel *sizeDSLabelValue;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *buildDataSetButton;
    QSpacerItem *horizontalSpacer_3;
    QProgressBar *buildDSProgressBar;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *optBuildDataSetWindow)
    {
        if (optBuildDataSetWindow->objectName().isEmpty())
            optBuildDataSetWindow->setObjectName(QString::fromUtf8("optBuildDataSetWindow"));
        optBuildDataSetWindow->resize(322, 493);
        horizontalLayout_4 = new QHBoxLayout(optBuildDataSetWindow);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        mainGroupBox = new QGroupBox(optBuildDataSetWindow);
        mainGroupBox->setObjectName(QString::fromUtf8("mainGroupBox"));
        verticalLayout_3 = new QVBoxLayout(mainGroupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        dirsDataSetGroupBox = new QGroupBox(mainGroupBox);
        dirsDataSetGroupBox->setObjectName(QString::fromUtf8("dirsDataSetGroupBox"));
        QFont font;
        font.setPointSize(12);
        dirsDataSetGroupBox->setFont(font);
        verticalLayout = new QVBoxLayout(dirsDataSetGroupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_4 = new QGroupBox(dirsDataSetGroupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setFont(font);
        horizontalLayout_9 = new QHBoxLayout(groupBox_4);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        netImagesDirLineEdit = new QLineEdit(groupBox_4);
        netImagesDirLineEdit->setObjectName(QString::fromUtf8("netImagesDirLineEdit"));
        netImagesDirLineEdit->setMinimumSize(QSize(0, 25));
        netImagesDirLineEdit->setReadOnly(true);

        horizontalLayout_9->addWidget(netImagesDirLineEdit);

        setDirNetImgButton = new QPushButton(groupBox_4);
        setDirNetImgButton->setObjectName(QString::fromUtf8("setDirNetImgButton"));
        setDirNetImgButton->setMinimumSize(QSize(40, 0));
        setDirNetImgButton->setMaximumSize(QSize(40, 16777215));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        setDirNetImgButton->setFont(font1);

        horizontalLayout_9->addWidget(setDirNetImgButton);


        verticalLayout->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(dirsDataSetGroupBox);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setFont(font);
        horizontalLayout_10 = new QHBoxLayout(groupBox_5);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        qFunDirLineEdit = new QLineEdit(groupBox_5);
        qFunDirLineEdit->setObjectName(QString::fromUtf8("qFunDirLineEdit"));
        qFunDirLineEdit->setMinimumSize(QSize(0, 25));
        qFunDirLineEdit->setReadOnly(true);

        horizontalLayout_10->addWidget(qFunDirLineEdit);

        setDirQFunButton = new QPushButton(groupBox_5);
        setDirQFunButton->setObjectName(QString::fromUtf8("setDirQFunButton"));
        setDirQFunButton->setMinimumSize(QSize(40, 0));
        setDirQFunButton->setMaximumSize(QSize(40, 16777215));
        setDirQFunButton->setFont(font1);

        horizontalLayout_10->addWidget(setDirQFunButton);


        verticalLayout->addWidget(groupBox_5);


        verticalLayout_3->addWidget(dirsDataSetGroupBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        sizeDSGroupBox = new QGroupBox(mainGroupBox);
        sizeDSGroupBox->setObjectName(QString::fromUtf8("sizeDSGroupBox"));
        sizeDSGroupBox->setFont(font);
        horizontalLayout_6 = new QHBoxLayout(sizeDSGroupBox);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        groupBox_2 = new QGroupBox(sizeDSGroupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QFont font2;
        font2.setPointSize(10);
        groupBox_2->setFont(font2);
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        countMapSpinBox = new QSpinBox(groupBox_2);
        countMapSpinBox->setObjectName(QString::fromUtf8("countMapSpinBox"));
        countMapSpinBox->setFont(font);
        countMapSpinBox->setMinimum(2);
        countMapSpinBox->setMaximum(1000);

        horizontalLayout->addWidget(countMapSpinBox);


        horizontalLayout_6->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(sizeDSGroupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(120, 0));
        groupBox_3->setFont(font2);
        horizontalLayout_5 = new QHBoxLayout(groupBox_3);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        countRectSpinBox = new QSpinBox(groupBox_3);
        countRectSpinBox->setObjectName(QString::fromUtf8("countRectSpinBox"));
        countRectSpinBox->setMinimumSize(QSize(0, 0));
        countRectSpinBox->setFont(font);
        countRectSpinBox->setMinimum(1);
        countRectSpinBox->setMaximum(10);

        horizontalLayout_5->addWidget(countRectSpinBox);


        horizontalLayout_6->addWidget(groupBox_3);


        horizontalLayout_3->addWidget(sizeDSGroupBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        sizeDataSetLabel = new QLabel(mainGroupBox);
        sizeDataSetLabel->setObjectName(QString::fromUtf8("sizeDataSetLabel"));
        sizeDataSetLabel->setFont(font);
        sizeDataSetLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(sizeDataSetLabel);

        sizeDSLabelValue = new QLabel(mainGroupBox);
        sizeDSLabelValue->setObjectName(QString::fromUtf8("sizeDSLabelValue"));
        sizeDSLabelValue->setFont(font);

        horizontalLayout_2->addWidget(sizeDSLabelValue);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        buildDataSetButton = new QPushButton(mainGroupBox);
        buildDataSetButton->setObjectName(QString::fromUtf8("buildDataSetButton"));
        buildDataSetButton->setMinimumSize(QSize(120, 30));
        buildDataSetButton->setFont(font);

        horizontalLayout_8->addWidget(buildDataSetButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_8);


        verticalLayout_3->addLayout(verticalLayout_2);

        buildDSProgressBar = new QProgressBar(mainGroupBox);
        buildDSProgressBar->setObjectName(QString::fromUtf8("buildDSProgressBar"));
        buildDSProgressBar->setValue(24);

        verticalLayout_3->addWidget(buildDSProgressBar);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_4->addWidget(mainGroupBox);


        retranslateUi(optBuildDataSetWindow);

        QMetaObject::connectSlotsByName(optBuildDataSetWindow);
    } // setupUi

    void retranslateUi(QWidget *optBuildDataSetWindow)
    {
        optBuildDataSetWindow->setWindowTitle(QCoreApplication::translate("optBuildDataSetWindow", "Form", nullptr));
        mainGroupBox->setTitle(QString());
        dirsDataSetGroupBox->setTitle(QCoreApplication::translate("optBuildDataSetWindow", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\320\270", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("optBuildDataSetWindow", "\320\222\321\205\320\276\320\264\320\275\321\213\320\265 \320\276\320\261\321\200\320\260\320\267\321\213", nullptr));
        setDirNetImgButton->setText(QCoreApplication::translate("optBuildDataSetWindow", "...", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("optBuildDataSetWindow", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\321\217 \320\246\320\244 (\320\275\320\260\320\263\321\200\320\260\320\264\321\213)", nullptr));
        setDirQFunButton->setText(QCoreApplication::translate("optBuildDataSetWindow", "...", nullptr));
        sizeDSGroupBox->setTitle(QCoreApplication::translate("optBuildDataSetWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 \320\262\321\213\320\261\320\276\321\200\320\272\320\270", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("optBuildDataSetWindow", "\320\240\320\265\320\273\321\214\320\265\321\204\320\276\320\262", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("optBuildDataSetWindow", "\320\237\320\276\321\201\321\202\320\260\320\275\320\276\320\262\320\276\320\272", nullptr));
        sizeDataSetLabel->setText(QCoreApplication::translate("optBuildDataSetWindow", "\320\232\320\276\320\273-\320\262\320\276 \320\277\320\260\321\200:", nullptr));
        sizeDSLabelValue->setText(QCoreApplication::translate("optBuildDataSetWindow", "---", nullptr));
        buildDataSetButton->setText(QCoreApplication::translate("optBuildDataSetWindow", "\320\223\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class optBuildDataSetWindow: public Ui_optBuildDataSetWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTBUILDDATASETWINDOW_H
