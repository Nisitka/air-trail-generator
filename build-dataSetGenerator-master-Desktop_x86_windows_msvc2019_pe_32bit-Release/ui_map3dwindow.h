/********************************************************************************
** Form generated from reading UI file 'map3dwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAP3DWINDOW_H
#define UI_MAP3DWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_map3DWindow
{
public:
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *mainGroupBox;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *updateButton;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *areaLayout;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *checkBoxLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *colorsLabelLayout;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *areaLayout2;

    void setupUi(QWidget *map3DWindow)
    {
        if (map3DWindow->objectName().isEmpty())
            map3DWindow->setObjectName(QString::fromUtf8("map3DWindow"));
        map3DWindow->resize(533, 439);
        horizontalLayout_4 = new QHBoxLayout(map3DWindow);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        mainGroupBox = new QGroupBox(map3DWindow);
        mainGroupBox->setObjectName(QString::fromUtf8("mainGroupBox"));
        verticalLayout_3 = new QVBoxLayout(mainGroupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        updateButton = new QPushButton(mainGroupBox);
        updateButton->setObjectName(QString::fromUtf8("updateButton"));
        updateButton->setMinimumSize(QSize(100, 30));
        updateButton->setMaximumSize(QSize(100, 30));
        QFont font;
        font.setPointSize(12);
        updateButton->setFont(font);

        horizontalLayout->addWidget(updateButton);


        verticalLayout_3->addLayout(horizontalLayout);

        tabWidget = new QTabWidget(mainGroupBox);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setFont(font);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_3 = new QHBoxLayout(tab);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        areaLayout = new QVBoxLayout();
        areaLayout->setObjectName(QString::fromUtf8("areaLayout"));

        horizontalLayout_3->addLayout(areaLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        checkBoxLayout = new QVBoxLayout();
        checkBoxLayout->setObjectName(QString::fromUtf8("checkBoxLayout"));

        verticalLayout->addLayout(checkBoxLayout);

        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFont(font);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        colorsLabelLayout = new QVBoxLayout();
        colorsLabelLayout->setObjectName(QString::fromUtf8("colorsLabelLayout"));

        verticalLayout_2->addLayout(colorsLabelLayout);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_5 = new QHBoxLayout(tab_2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        areaLayout2 = new QVBoxLayout();
        areaLayout2->setObjectName(QString::fromUtf8("areaLayout2"));

        horizontalLayout_5->addLayout(areaLayout2);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_3->addWidget(tabWidget);


        horizontalLayout_4->addWidget(mainGroupBox);


        retranslateUi(map3DWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(map3DWindow);
    } // setupUi

    void retranslateUi(QWidget *map3DWindow)
    {
        map3DWindow->setWindowTitle(QCoreApplication::translate("map3DWindow", "Form", nullptr));
        mainGroupBox->setTitle(QString());
        updateButton->setText(QCoreApplication::translate("map3DWindow", "\320\236\321\202\320\276\320\261\321\200\320\260\320\267\320\270\321\202\321\214", nullptr));
        groupBox->setTitle(QCoreApplication::translate("map3DWindow", "\320\246\320\262\320\265\321\202\320\260 \320\262\321\213\321\201\320\276\321\202", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("map3DWindow", "\320\240\320\265\320\273\321\214\320\265\321\204", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("map3DWindow", "\320\227\320\276\320\275\320\260 \320\276\320\261\320\275\320\260\321\200\321\203\320\266\320\265\320\275\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class map3DWindow: public Ui_map3DWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAP3DWINDOW_H
