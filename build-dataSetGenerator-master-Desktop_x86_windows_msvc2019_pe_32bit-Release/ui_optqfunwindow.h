/********************************************************************************
** Form generated from reading UI file 'optqfunwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTQFUNWINDOW_H
#define UI_OPTQFUNWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_optQFunWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QGroupBox *mainGroupBox;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_28;
    QSpacerItem *horizontalSpacer_22;
    QPushButton *calcQFunButton;
    QSpacerItem *horizontalSpacer_23;
    QProgressBar *calcQFunProgressBar;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *optQFunWindow)
    {
        if (optQFunWindow->objectName().isEmpty())
            optQFunWindow->setObjectName(QString::fromUtf8("optQFunWindow"));
        optQFunWindow->resize(304, 171);
        horizontalLayout = new QHBoxLayout(optQFunWindow);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        mainGroupBox = new QGroupBox(optQFunWindow);
        mainGroupBox->setObjectName(QString::fromUtf8("mainGroupBox"));
        verticalLayout = new QVBoxLayout(mainGroupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_28->addItem(horizontalSpacer_22);

        calcQFunButton = new QPushButton(mainGroupBox);
        calcQFunButton->setObjectName(QString::fromUtf8("calcQFunButton"));
        calcQFunButton->setMinimumSize(QSize(225, 30));
        QFont font;
        font.setPointSize(12);
        calcQFunButton->setFont(font);

        horizontalLayout_28->addWidget(calcQFunButton);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_28->addItem(horizontalSpacer_23);


        verticalLayout->addLayout(horizontalLayout_28);

        calcQFunProgressBar = new QProgressBar(mainGroupBox);
        calcQFunProgressBar->setObjectName(QString::fromUtf8("calcQFunProgressBar"));
        calcQFunProgressBar->setValue(24);

        verticalLayout->addWidget(calcQFunProgressBar);

        verticalSpacer = new QSpacerItem(20, 29, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(mainGroupBox);


        retranslateUi(optQFunWindow);

        QMetaObject::connectSlotsByName(optQFunWindow);
    } // setupUi

    void retranslateUi(QWidget *optQFunWindow)
    {
        optQFunWindow->setWindowTitle(QCoreApplication::translate("optQFunWindow", "Form", nullptr));
        mainGroupBox->setTitle(QString());
        calcQFunButton->setText(QCoreApplication::translate("optQFunWindow", " \320\236\320\261\321\201\321\207\320\265\321\202 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\320\271 Q \321\204\321\203\320\275\320\272\321\206\320\270\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class optQFunWindow: public Ui_optQFunWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTQFUNWINDOW_H
