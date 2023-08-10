/********************************************************************************
** Form generated from reading UI file 'optdronewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTDRONEWINDOW_H
#define UI_OPTDRONEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_optDroneWindow
{
public:
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *mainGroupBox;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *trailGroupBox;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *angleESpinBox;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *setTrakButton;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *optDroneWindow)
    {
        if (optDroneWindow->objectName().isEmpty())
            optDroneWindow->setObjectName(QString::fromUtf8("optDroneWindow"));
        optDroneWindow->resize(278, 266);
        horizontalLayout_3 = new QHBoxLayout(optDroneWindow);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        mainGroupBox = new QGroupBox(optDroneWindow);
        mainGroupBox->setObjectName(QString::fromUtf8("mainGroupBox"));
        verticalLayout_2 = new QVBoxLayout(mainGroupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        trailGroupBox = new QGroupBox(mainGroupBox);
        trailGroupBox->setObjectName(QString::fromUtf8("trailGroupBox"));
        QFont font;
        font.setPointSize(14);
        trailGroupBox->setFont(font);
        verticalLayout = new QVBoxLayout(trailGroupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(trailGroupBox);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(200, 0));
        QFont font1;
        font1.setPointSize(12);
        groupBox->setFont(font1);
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        angleESpinBox = new QDoubleSpinBox(groupBox);
        angleESpinBox->setObjectName(QString::fromUtf8("angleESpinBox"));
        angleESpinBox->setFont(font1);
        angleESpinBox->setMaximum(359.990000000000009);

        horizontalLayout->addWidget(angleESpinBox);

        horizontalSpacer = new QSpacerItem(148, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(groupBox);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        setTrakButton = new QPushButton(trailGroupBox);
        setTrakButton->setObjectName(QString::fromUtf8("setTrakButton"));
        setTrakButton->setMinimumSize(QSize(0, 30));
        setTrakButton->setFont(font1);

        horizontalLayout_2->addWidget(setTrakButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addWidget(trailGroupBox);

        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_3->addWidget(mainGroupBox);


        retranslateUi(optDroneWindow);

        QMetaObject::connectSlotsByName(optDroneWindow);
    } // setupUi

    void retranslateUi(QWidget *optDroneWindow)
    {
        optDroneWindow->setWindowTitle(QCoreApplication::translate("optDroneWindow", "Form", nullptr));
        mainGroupBox->setTitle(QString());
        trailGroupBox->setTitle(QCoreApplication::translate("optDroneWindow", "\320\242\321\200\320\260\320\265\320\272\321\202\320\276\321\200\320\270\321\217", nullptr));
        groupBox->setTitle(QCoreApplication::translate("optDroneWindow", "\320\220\320\267\320\270\320\274\321\203\321\202 \320\272\320\276\320\275\320\265\321\207\320\275\320\276\320\271 \321\202\320\276\321\207\320\272\320\270", nullptr));
        angleESpinBox->setPrefix(QString());
        setTrakButton->setText(QCoreApplication::translate("optDroneWindow", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class optDroneWindow: public Ui_optDroneWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTDRONEWINDOW_H
