/********************************************************************************
** Form generated from reading UI file 'visualinfowidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISUALINFOWIDGET_H
#define UI_VISUALINFOWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_visualInfoWidget
{
public:
    QHBoxLayout *horizontalLayout_7;
    QGroupBox *mainGroupBox;
    QVBoxLayout *verticalLayout_11;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_18;
    QGroupBox *saveDataGroupBox;
    QVBoxLayout *verticalLayout_8;
    QTabWidget *saveTabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_15;
    QVBoxLayout *verticalLayout_9;
    QSpacerItem *verticalSpacer_7;
    QLabel *dirSaveImageLabel;
    QHBoxLayout *horizontalLayout_9;
    QLineEdit *dirSaveImgLineEdit;
    QPushButton *setDirSaveImgButton;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_8;
    QPushButton *saveImgButton;
    QComboBox *typeSaveImglComboBox;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_10;
    QSpacerItem *verticalSpacer_9;
    QLabel *dirSaveMapLabel;
    QHBoxLayout *horizontalLayout_11;
    QLineEdit *dirSaveMapLineEdit;
    QPushButton *setDirSaveMapButton;
    QPushButton *saveMapButton;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *typeVisObjGroupBox;
    QHBoxLayout *horizontalLayout_12;
    QComboBox *objectVisualComboBox;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_16;
    QVBoxLayout *verticalLayout_12;
    QGroupBox *toolsGroupBox;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *moveMapToolButton;
    QPushButton *setRLStoolButton;
    QPushButton *zoomMapToolButton;
    QPushButton *predictRectToolButton;
    QPushButton *predictTrailToolButton;
    QPushButton *map3DToolButton;
    QPushButton *editEarthToolButton;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *optToolsButton;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *areaDrawLayout;
    QGroupBox *coordsGroupBox;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *xTitleLabel;
    QLabel *xValueLabel;
    QHBoxLayout *horizontalLayout_5;
    QLabel *yTitleLabel;
    QLabel *yValueLabel;
    QHBoxLayout *horizontalLayout_6;
    QLabel *hTitleLabel;
    QLabel *hValueLabel;
    QSpacerItem *horizontalSpacer_2;
    QGroupBox *optToolsGroupBox;
    QVBoxLayout *verticalLayout_13;
    QStackedWidget *optToolsStackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_15;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_16;
    QTextEdit *textEdit;
    QWidget *page_2;
    QWidget *page_3;
    QWidget *page_4;
    QWidget *page_5;
    QWidget *page_6;
    QWidget *page_7;
    QVBoxLayout *verticalLayout_18;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_17;
    QSlider *sizeEditEarthSlider;
    QHBoxLayout *horizontalLayout_19;
    QSpinBox *sizeEditEarthSpinBox;
    QLabel *label;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_19;
    QTextEdit *textEdit_2;

    void setupUi(QWidget *visualInfoWidget)
    {
        if (visualInfoWidget->objectName().isEmpty())
            visualInfoWidget->setObjectName(QString::fromUtf8("visualInfoWidget"));
        visualInfoWidget->resize(744, 622);
        horizontalLayout_7 = new QHBoxLayout(visualInfoWidget);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        mainGroupBox = new QGroupBox(visualInfoWidget);
        mainGroupBox->setObjectName(QString::fromUtf8("mainGroupBox"));
        verticalLayout_11 = new QVBoxLayout(mainGroupBox);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        groupBox_4 = new QGroupBox(mainGroupBox);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMaximumSize(QSize(16777215, 170));
        horizontalLayout_18 = new QHBoxLayout(groupBox_4);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        saveDataGroupBox = new QGroupBox(groupBox_4);
        saveDataGroupBox->setObjectName(QString::fromUtf8("saveDataGroupBox"));
        saveDataGroupBox->setMaximumSize(QSize(16777215, 150));
        QFont font;
        font.setPointSize(12);
        saveDataGroupBox->setFont(font);
        verticalLayout_8 = new QVBoxLayout(saveDataGroupBox);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        saveTabWidget = new QTabWidget(saveDataGroupBox);
        saveTabWidget->setObjectName(QString::fromUtf8("saveTabWidget"));
        QFont font1;
        font1.setPointSize(10);
        saveTabWidget->setFont(font1);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_15 = new QHBoxLayout(tab);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_7);

        dirSaveImageLabel = new QLabel(tab);
        dirSaveImageLabel->setObjectName(QString::fromUtf8("dirSaveImageLabel"));
        dirSaveImageLabel->setMaximumSize(QSize(40, 16777215));
        QFont font2;
        font2.setPointSize(11);
        dirSaveImageLabel->setFont(font2);
        dirSaveImageLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_9->addWidget(dirSaveImageLabel);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        dirSaveImgLineEdit = new QLineEdit(tab);
        dirSaveImgLineEdit->setObjectName(QString::fromUtf8("dirSaveImgLineEdit"));
        dirSaveImgLineEdit->setFont(font);

        horizontalLayout_9->addWidget(dirSaveImgLineEdit);

        setDirSaveImgButton = new QPushButton(tab);
        setDirSaveImgButton->setObjectName(QString::fromUtf8("setDirSaveImgButton"));
        setDirSaveImgButton->setMinimumSize(QSize(35, 0));
        setDirSaveImgButton->setMaximumSize(QSize(35, 16777215));
        QFont font3;
        font3.setPointSize(13);
        font3.setBold(true);
        font3.setWeight(75);
        setDirSaveImgButton->setFont(font3);

        horizontalLayout_9->addWidget(setDirSaveImgButton);


        verticalLayout_9->addLayout(horizontalLayout_9);


        horizontalLayout_15->addLayout(verticalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_8);

        saveImgButton = new QPushButton(tab);
        saveImgButton->setObjectName(QString::fromUtf8("saveImgButton"));
        saveImgButton->setMinimumSize(QSize(0, 25));
        saveImgButton->setFont(font1);

        verticalLayout_3->addWidget(saveImgButton);

        typeSaveImglComboBox = new QComboBox(tab);
        typeSaveImglComboBox->setObjectName(QString::fromUtf8("typeSaveImglComboBox"));
        typeSaveImglComboBox->setMaximumSize(QSize(150, 16777215));
        typeSaveImglComboBox->setFont(font1);

        verticalLayout_3->addWidget(typeSaveImglComboBox);


        horizontalLayout_8->addLayout(verticalLayout_3);


        horizontalLayout_15->addLayout(horizontalLayout_8);

        saveTabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_10 = new QVBoxLayout(tab_3);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_9);

        dirSaveMapLabel = new QLabel(tab_3);
        dirSaveMapLabel->setObjectName(QString::fromUtf8("dirSaveMapLabel"));
        dirSaveMapLabel->setMaximumSize(QSize(40, 16777215));
        dirSaveMapLabel->setFont(font2);
        dirSaveMapLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_10->addWidget(dirSaveMapLabel);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        dirSaveMapLineEdit = new QLineEdit(tab_3);
        dirSaveMapLineEdit->setObjectName(QString::fromUtf8("dirSaveMapLineEdit"));
        dirSaveMapLineEdit->setFont(font);

        horizontalLayout_11->addWidget(dirSaveMapLineEdit);

        setDirSaveMapButton = new QPushButton(tab_3);
        setDirSaveMapButton->setObjectName(QString::fromUtf8("setDirSaveMapButton"));
        setDirSaveMapButton->setMinimumSize(QSize(35, 0));
        setDirSaveMapButton->setMaximumSize(QSize(35, 16777215));
        setDirSaveMapButton->setFont(font3);

        horizontalLayout_11->addWidget(setDirSaveMapButton);

        saveMapButton = new QPushButton(tab_3);
        saveMapButton->setObjectName(QString::fromUtf8("saveMapButton"));
        saveMapButton->setMinimumSize(QSize(0, 25));
        saveMapButton->setFont(font1);

        horizontalLayout_11->addWidget(saveMapButton);


        verticalLayout_10->addLayout(horizontalLayout_11);

        saveTabWidget->addTab(tab_3, QString());

        verticalLayout_8->addWidget(saveTabWidget);


        horizontalLayout_18->addWidget(saveDataGroupBox);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        typeVisObjGroupBox = new QGroupBox(groupBox_4);
        typeVisObjGroupBox->setObjectName(QString::fromUtf8("typeVisObjGroupBox"));
        typeVisObjGroupBox->setMinimumSize(QSize(180, 0));
        typeVisObjGroupBox->setFont(font);
        horizontalLayout_12 = new QHBoxLayout(typeVisObjGroupBox);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        objectVisualComboBox = new QComboBox(typeVisObjGroupBox);
        objectVisualComboBox->setObjectName(QString::fromUtf8("objectVisualComboBox"));
        objectVisualComboBox->setMaximumSize(QSize(150, 16777215));
        objectVisualComboBox->setFont(font1);

        horizontalLayout_12->addWidget(objectVisualComboBox);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_8);


        verticalLayout_4->addWidget(typeVisObjGroupBox);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);


        horizontalLayout_18->addLayout(verticalLayout_4);


        verticalLayout_11->addWidget(groupBox_4);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        toolsGroupBox = new QGroupBox(mainGroupBox);
        toolsGroupBox->setObjectName(QString::fromUtf8("toolsGroupBox"));
        toolsGroupBox->setMaximumSize(QSize(16777215, 70));
        toolsGroupBox->setFont(font);
        horizontalLayout_3 = new QHBoxLayout(toolsGroupBox);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        moveMapToolButton = new QPushButton(toolsGroupBox);
        moveMapToolButton->setObjectName(QString::fromUtf8("moveMapToolButton"));
        moveMapToolButton->setMinimumSize(QSize(38, 35));
        moveMapToolButton->setMaximumSize(QSize(38, 35));
        QIcon icon;
        icon.addFile(QString::fromUtf8("resurs/hand.png"), QSize(), QIcon::Normal, QIcon::Off);
        moveMapToolButton->setIcon(icon);
        moveMapToolButton->setIconSize(QSize(25, 25));

        horizontalLayout_3->addWidget(moveMapToolButton);

        setRLStoolButton = new QPushButton(toolsGroupBox);
        setRLStoolButton->setObjectName(QString::fromUtf8("setRLStoolButton"));
        setRLStoolButton->setMinimumSize(QSize(38, 35));
        setRLStoolButton->setMaximumSize(QSize(38, 35));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("resurs/radarBlue.png"), QSize(), QIcon::Normal, QIcon::Off);
        setRLStoolButton->setIcon(icon1);
        setRLStoolButton->setIconSize(QSize(28, 28));

        horizontalLayout_3->addWidget(setRLStoolButton);

        zoomMapToolButton = new QPushButton(toolsGroupBox);
        zoomMapToolButton->setObjectName(QString::fromUtf8("zoomMapToolButton"));
        zoomMapToolButton->setMinimumSize(QSize(38, 35));
        zoomMapToolButton->setMaximumSize(QSize(38, 35));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resurs/zoom.png"), QSize(), QIcon::Normal, QIcon::Off);
        zoomMapToolButton->setIcon(icon2);
        zoomMapToolButton->setIconSize(QSize(25, 25));

        horizontalLayout_3->addWidget(zoomMapToolButton);

        predictRectToolButton = new QPushButton(toolsGroupBox);
        predictRectToolButton->setObjectName(QString::fromUtf8("predictRectToolButton"));
        predictRectToolButton->setMinimumSize(QSize(38, 35));
        predictRectToolButton->setMaximumSize(QSize(38, 35));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resurs/mapIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        predictRectToolButton->setIcon(icon3);
        predictRectToolButton->setIconSize(QSize(25, 25));

        horizontalLayout_3->addWidget(predictRectToolButton);

        predictTrailToolButton = new QPushButton(toolsGroupBox);
        predictTrailToolButton->setObjectName(QString::fromUtf8("predictTrailToolButton"));
        predictTrailToolButton->setMinimumSize(QSize(38, 35));
        predictTrailToolButton->setMaximumSize(QSize(38, 35));
        predictTrailToolButton->setIcon(icon3);
        predictTrailToolButton->setIconSize(QSize(25, 25));

        horizontalLayout_3->addWidget(predictTrailToolButton);

        map3DToolButton = new QPushButton(toolsGroupBox);
        map3DToolButton->setObjectName(QString::fromUtf8("map3DToolButton"));
        map3DToolButton->setMinimumSize(QSize(38, 35));
        map3DToolButton->setMaximumSize(QSize(38, 35));
        map3DToolButton->setIcon(icon3);
        map3DToolButton->setIconSize(QSize(25, 25));

        horizontalLayout_3->addWidget(map3DToolButton);

        editEarthToolButton = new QPushButton(toolsGroupBox);
        editEarthToolButton->setObjectName(QString::fromUtf8("editEarthToolButton"));
        editEarthToolButton->setMinimumSize(QSize(38, 35));
        editEarthToolButton->setMaximumSize(QSize(38, 35));
        editEarthToolButton->setIcon(icon3);
        editEarthToolButton->setIconSize(QSize(25, 25));

        horizontalLayout_3->addWidget(editEarthToolButton);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_12);

        optToolsButton = new QPushButton(toolsGroupBox);
        optToolsButton->setObjectName(QString::fromUtf8("optToolsButton"));
        optToolsButton->setMinimumSize(QSize(38, 35));
        optToolsButton->setMaximumSize(QSize(38, 35));
        optToolsButton->setIcon(icon3);
        optToolsButton->setIconSize(QSize(25, 25));

        horizontalLayout_3->addWidget(optToolsButton);


        verticalLayout_12->addWidget(toolsGroupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        areaDrawLayout = new QVBoxLayout();
        areaDrawLayout->setObjectName(QString::fromUtf8("areaDrawLayout"));

        verticalLayout_2->addLayout(areaDrawLayout);

        coordsGroupBox = new QGroupBox(mainGroupBox);
        coordsGroupBox->setObjectName(QString::fromUtf8("coordsGroupBox"));
        coordsGroupBox->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_4 = new QHBoxLayout(coordsGroupBox);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        xTitleLabel = new QLabel(coordsGroupBox);
        xTitleLabel->setObjectName(QString::fromUtf8("xTitleLabel"));
        QFont font4;
        font4.setPointSize(10);
        font4.setBold(true);
        font4.setWeight(75);
        xTitleLabel->setFont(font4);
        xTitleLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(xTitleLabel);

        xValueLabel = new QLabel(coordsGroupBox);
        xValueLabel->setObjectName(QString::fromUtf8("xValueLabel"));

        horizontalLayout_2->addWidget(xValueLabel);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        yTitleLabel = new QLabel(coordsGroupBox);
        yTitleLabel->setObjectName(QString::fromUtf8("yTitleLabel"));
        yTitleLabel->setFont(font4);
        yTitleLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(yTitleLabel);

        yValueLabel = new QLabel(coordsGroupBox);
        yValueLabel->setObjectName(QString::fromUtf8("yValueLabel"));

        horizontalLayout_5->addWidget(yValueLabel);


        horizontalLayout_4->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        hTitleLabel = new QLabel(coordsGroupBox);
        hTitleLabel->setObjectName(QString::fromUtf8("hTitleLabel"));
        hTitleLabel->setFont(font4);
        hTitleLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(hTitleLabel);

        hValueLabel = new QLabel(coordsGroupBox);
        hValueLabel->setObjectName(QString::fromUtf8("hValueLabel"));

        horizontalLayout_6->addWidget(hValueLabel);


        horizontalLayout_4->addLayout(horizontalLayout_6);

        horizontalSpacer_2 = new QSpacerItem(246, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_2->addWidget(coordsGroupBox);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_12->addLayout(horizontalLayout);


        horizontalLayout_16->addLayout(verticalLayout_12);

        optToolsGroupBox = new QGroupBox(mainGroupBox);
        optToolsGroupBox->setObjectName(QString::fromUtf8("optToolsGroupBox"));
        optToolsGroupBox->setMinimumSize(QSize(170, 0));
        optToolsGroupBox->setMaximumSize(QSize(320, 16777215));
        optToolsGroupBox->setFont(font1);
        verticalLayout_13 = new QVBoxLayout(optToolsGroupBox);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        optToolsStackedWidget = new QStackedWidget(optToolsGroupBox);
        optToolsStackedWidget->setObjectName(QString::fromUtf8("optToolsStackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout_15 = new QVBoxLayout(page);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        groupBox = new QGroupBox(page);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_16 = new QVBoxLayout(groupBox);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        textEdit = new QTextEdit(groupBox);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setReadOnly(true);

        verticalLayout_16->addWidget(textEdit);


        verticalLayout_15->addWidget(groupBox);

        optToolsStackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        optToolsStackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        optToolsStackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        optToolsStackedWidget->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        optToolsStackedWidget->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        optToolsStackedWidget->addWidget(page_6);
        page_7 = new QWidget();
        page_7->setObjectName(QString::fromUtf8("page_7"));
        verticalLayout_18 = new QVBoxLayout(page_7);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        groupBox_2 = new QGroupBox(page_7);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_17 = new QVBoxLayout(groupBox_2);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        sizeEditEarthSlider = new QSlider(groupBox_2);
        sizeEditEarthSlider->setObjectName(QString::fromUtf8("sizeEditEarthSlider"));
        sizeEditEarthSlider->setOrientation(Qt::Horizontal);

        verticalLayout_17->addWidget(sizeEditEarthSlider);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        sizeEditEarthSpinBox = new QSpinBox(groupBox_2);
        sizeEditEarthSpinBox->setObjectName(QString::fromUtf8("sizeEditEarthSpinBox"));

        horizontalLayout_19->addWidget(sizeEditEarthSpinBox);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_19->addWidget(label);


        verticalLayout_17->addLayout(horizontalLayout_19);


        verticalLayout_18->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(page_7);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_19 = new QVBoxLayout(groupBox_3);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        textEdit_2 = new QTextEdit(groupBox_3);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setAutoFormatting(QTextEdit::AutoBulletList);
        textEdit_2->setReadOnly(true);

        verticalLayout_19->addWidget(textEdit_2);


        verticalLayout_18->addWidget(groupBox_3);

        optToolsStackedWidget->addWidget(page_7);

        verticalLayout_13->addWidget(optToolsStackedWidget);


        horizontalLayout_16->addWidget(optToolsGroupBox);


        verticalLayout_11->addLayout(horizontalLayout_16);


        horizontalLayout_7->addWidget(mainGroupBox);


        retranslateUi(visualInfoWidget);

        saveTabWidget->setCurrentIndex(0);
        optToolsStackedWidget->setCurrentIndex(6);


        QMetaObject::connectSlotsByName(visualInfoWidget);
    } // setupUi

    void retranslateUi(QWidget *visualInfoWidget)
    {
        visualInfoWidget->setWindowTitle(QCoreApplication::translate("visualInfoWidget", "Form", nullptr));
        mainGroupBox->setTitle(QString());
        groupBox_4->setTitle(QString());
        saveDataGroupBox->setTitle(QCoreApplication::translate("visualInfoWidget", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        dirSaveImageLabel->setText(QCoreApplication::translate("visualInfoWidget", "\320\237\321\203\321\202\321\214", nullptr));
        setDirSaveImgButton->setText(QCoreApplication::translate("visualInfoWidget", "...", nullptr));
        saveImgButton->setText(QCoreApplication::translate("visualInfoWidget", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        saveTabWidget->setTabText(saveTabWidget->indexOf(tab), QCoreApplication::translate("visualInfoWidget", "\320\230\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\320\265", nullptr));
        dirSaveMapLabel->setText(QCoreApplication::translate("visualInfoWidget", "\320\237\321\203\321\202\321\214", nullptr));
        setDirSaveMapButton->setText(QCoreApplication::translate("visualInfoWidget", "...", nullptr));
        saveMapButton->setText(QCoreApplication::translate("visualInfoWidget", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        saveTabWidget->setTabText(saveTabWidget->indexOf(tab_3), QCoreApplication::translate("visualInfoWidget", "\320\240\320\265\320\273\321\214\320\265\321\204", nullptr));
        typeVisObjGroupBox->setTitle(QCoreApplication::translate("visualInfoWidget", "\320\222\320\270\320\267\321\203\320\260\320\273\320\270\320\267\320\270\321\200\320\276\320\262\320\260\321\202\321\214:", nullptr));
        toolsGroupBox->setTitle(QCoreApplication::translate("visualInfoWidget", "\320\230\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202\321\213", nullptr));
#if QT_CONFIG(tooltip)
        moveMapToolButton->setToolTip(QCoreApplication::translate("visualInfoWidget", "<html><head/><body><p>\320\237\320\265\321\200\320\265\320\274\320\265\321\211\320\265\320\275\320\270\320\265 \320\272\320\260\321\200\321\202\321\204\320\276\320\275\320\260</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        moveMapToolButton->setText(QString());
#if QT_CONFIG(tooltip)
        setRLStoolButton->setToolTip(QCoreApplication::translate("visualInfoWidget", "<html><head/><body><p>\320\277\320\276\320\267\320\270\321\206\320\270\321\217 \320\240\320\233\320\241</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        setRLStoolButton->setText(QString());
#if QT_CONFIG(tooltip)
        zoomMapToolButton->setToolTip(QCoreApplication::translate("visualInfoWidget", "<html><head/><body><p>\320\243\320\262\320\265\320\273\320\265\321\207\320\265\320\275\320\270\320\265/\321\203\320\274\320\265\320\275\321\214\321\210\320\265\320\275\320\270\320\265 \320\274\320\260\321\201\321\210\321\202\320\260\320\261\320\260</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        zoomMapToolButton->setText(QString());
#if QT_CONFIG(tooltip)
        predictRectToolButton->setToolTip(QCoreApplication::translate("visualInfoWidget", "<html><head/><body><p>\320\237\320\276\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \320\221\320\237\320\233\320\220</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        predictRectToolButton->setText(QString());
#if QT_CONFIG(tooltip)
        predictTrailToolButton->setToolTip(QCoreApplication::translate("visualInfoWidget", "<html><head/><body><p>\320\237\320\276\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 \321\202\320\276\321\207\320\265\320\272 \320\274\320\260\321\200\321\210\321\200\321\203\321\202\320\260</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        predictTrailToolButton->setText(QString());
#if QT_CONFIG(tooltip)
        map3DToolButton->setToolTip(QCoreApplication::translate("visualInfoWidget", "<html><head/><body><p>\320\224\320\265\321\202\320\260\320\273\320\270\320\267\320\260\321\206\320\270\321\217 \321\200\320\265\320\273\321\214\320\265\321\204\320\260 \320\262 3D</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        map3DToolButton->setText(QString());
#if QT_CONFIG(tooltip)
        editEarthToolButton->setToolTip(QCoreApplication::translate("visualInfoWidget", "<html><head/><body><p>\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \321\200\320\265\320\273\321\214\320\265\321\204\320\260 </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        editEarthToolButton->setText(QString());
#if QT_CONFIG(tooltip)
        optToolsButton->setToolTip(QCoreApplication::translate("visualInfoWidget", "<html><head/><body><p>\320\236\321\202\320\272\321\200\321\213\321\202\321\214 / \320\267\320\260\320\272\321\200\321\213\321\202\321\214 \320\276\320\277\321\206\320\270\320\270 \320\270\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202\320\260</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        optToolsButton->setText(QString());
        coordsGroupBox->setTitle(QString());
        xTitleLabel->setText(QCoreApplication::translate("visualInfoWidget", "X:", nullptr));
        xValueLabel->setText(QCoreApplication::translate("visualInfoWidget", "---", nullptr));
        yTitleLabel->setText(QCoreApplication::translate("visualInfoWidget", "Y:", nullptr));
        yValueLabel->setText(QCoreApplication::translate("visualInfoWidget", "---", nullptr));
        hTitleLabel->setText(QCoreApplication::translate("visualInfoWidget", "H:", nullptr));
        hValueLabel->setText(QCoreApplication::translate("visualInfoWidget", "---", nullptr));
        optToolsGroupBox->setTitle(QCoreApplication::translate("visualInfoWidget", "\320\236\320\277\321\206\320\270\320\270 \320\270\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202\320\260", nullptr));
        groupBox->setTitle(QCoreApplication::translate("visualInfoWidget", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        textEdit->setHtml(QCoreApplication::translate("visualInfoWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">    <span style=\" font-size:14pt;\">\320\230\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202 \320\277\320\276\320\267\320\262\320\276\320\273\321\217\320\265\321\202 \320\277\320\265\321\200\320\265\320\274\320\265\321\211\320\260\321\202\321\214\321\201\321\217 \320\277\320\276 \320\272\320\260\321\200\321\202\321\204\320\276\320\275\321\203: </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">\320\267\320\260\320\266"
                        "\320\274\320\270\321\202\320\265 </span><span style=\" font-size:14pt; font-weight:600;\">\320\233\320\232\320\234</span><span style=\" font-size:14pt;\"> \320\270\320\273\320\270 </span><span style=\" font-size:14pt; font-weight:600;\">\320\237\320\232\320\234</span><span style=\" font-size:14pt;\">, \320\260 \320\267\320\260\321\202\320\265\320\274 \320\277\320\265\321\200\320\265\320\264\320\262\320\270\320\275\321\214\321\202\320\265 \320\272\321\203\321\200\321\201\320\276\321\200 \320\274\321\213\321\210\320\270 \320\262 \320\275\321\203\320\266\320\275\320\276\320\274 \320\262\320\260\320\274 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\270.</span></p></body></html>", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("visualInfoWidget", "\320\240\320\260\320\267\320\274\320\265\321\200 \320\272\320\270\321\201\321\202\320\270", nullptr));
        label->setText(QCoreApplication::translate("visualInfoWidget", "\320\261\320\273\320\276\320\272\320\276\320\262", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("visualInfoWidget", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265", nullptr));
        textEdit_2->setHtml(QCoreApplication::translate("visualInfoWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">    <span style=\" font-size:14pt;\">\320\230\320\275\321\201\321\202\321\200\321\203\320\274\320\265\320\275\321\202 \320\277\320\276\320\267\320\262\320\276\320\273\321\217\320\265\321\202 \320\270\320\267\320\274\320\265\320\275\321\217\321\202\321\214 \321\200\320\265\320\273\321\214\320\265\321\204 \320\272\320\260\321\200\321\202\321\213: </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">1) \320\267\320\260\320\266\320\274\320\270\321"
                        "\202\320\265 </span><span style=\" font-size:14pt; font-weight:600;\">\320\233\320\232\320\234</span><span style=\" font-size:14pt;\"> \321\207\321\202\320\276\320\261\321\213 \320\275\320\260\321\207\320\260\321\202\321\214 \321\203\320\262\320\265\320\273\320\270\321\207\320\270\320\262\320\260\321\202\321\214 \320\262\321\213\321\201\320\276\321\202\321\203 \320\262 \320\276\320\261\320\273\320\260\321\201\321\202\320\270 \320\272\321\203\321\200\321\201\320\276\321\200\320\260.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt;\">2) \320\267\320\260\320\266\320\274\320\270\321\202\320\265 </span><span style=\" font-size:14pt; font-weight:600;\">\320\237\320\232\320\234</span><span style=\" font-size:14pt;\"> \321\207\321\202\320\276\320\261\321\213 \320\275\320\260\321\207\320\260\321\202\321\214 \321\203\320\274\320\265\320\275\321\214\321\210\320\260\321\202\321\214 \320\262\321\213\321\201"
                        "\320\276\321\202\321\203 \320\262 \320\276\320\261\320\273\320\260\321\201\321\202\320\270 \320\272\321\203\321\200\321\201\320\276\321\200\320\260.</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class visualInfoWidget: public Ui_visualInfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISUALINFOWIDGET_H
