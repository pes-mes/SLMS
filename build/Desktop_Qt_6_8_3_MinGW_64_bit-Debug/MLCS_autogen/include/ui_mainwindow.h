/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <transparentpushbutton.h>
#include "azimuthwidget.h"
#include "elevationwidget.h"
#include "missilewidget.h"
#include "targetwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *pageLogin;
    QGroupBox *groupBox;
    QPushButton *PB_View;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *PB_login;
    QPushButton *PB_Cancel;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *LE_Username;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *LE_Password;
    QLabel *label_5;
    QLabel *leftImageLabel;
    QLabel *rightImageLabel;
    QWidget *pageMainWindow;
    QLabel *L_FunctionKeys_Left;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    TransparentPushButton *PB_Home;
    TransparentPushButton *PB_RequestRelease;
    TransparentPushButton *PB_Fire;
    TransparentPushButton *PB_MissileSelection;
    TransparentPushButton *PB_EngageLauncher;
    TransparentPushButton *PB_MissileEngage;
    TransparentPushButton *PB_Plus;
    TransparentPushButton *PB_Minus;
    TransparentPushButton *PB_LogOut;
    QWidget *layoutWidget3;
    QHBoxLayout *nodeStatusLayout;
    QLabel *node1StatusLabel;
    QLabel *node2StatusLabel;
    QWidget *layoutWidget4;
    QGroupBox *cameraGroup;
    QGraphicsView *cameraView;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout;
    MissileWidget *missileWidget;
    TargetWidget *targetWidget;
    QWidget *layoutWidget6;
    QGridLayout *gridLayout_3;
    AzimuthWidget *azimuthWidget;
    ElevationWidget *elevationWidget;
    QGroupBox *targetTypeGroup;
    QGridLayout *gridLayout;
    QComboBox *targetTypeCombo;
    QGroupBox *missileSelectionCombo;
    QGridLayout *gridLayout_2;
    QComboBox *MissileSelectionCombo;
    QWidget *layoutWidget31;
    QVBoxLayout *verticalLayout_2;
    TransparentPushButton *PB_DayCamera;
    TransparentPushButton *PB_LRF;
    TransparentPushButton *PB_Zoom;
    TransparentPushButton *PB_Focus;
    TransparentPushButton *PB_ExposureGain;
    TransparentPushButton *PB_Polarity;
    TransparentPushButton *PB_NUC;
    TransparentPushButton *PB_pageMaintenance;
    TransparentPushButton *PB_pageStatusPanel;
    QLabel *L_FunctionKeys_Left_2;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *pbRecord;
    QWidget *pageMaintenance;
    QLabel *label_2;
    QWidget *layoutWidget7;
    QVBoxLayout *verticalLayout_3;
    TransparentPushButton *PB_PreviousPage;
    TransparentPushButton *PB_Logout;
    QWidget *pageStatusPanel;
    QLabel *label_3;
    QWidget *layoutWidget8;
    QVBoxLayout *verticalLayout_4;
    TransparentPushButton *PB_PreviousPage_2;
    TransparentPushButton *PB_Logout_2;
    QWidget *layoutWidget9;
    QVBoxLayout *verticalLayout_5;
    QPushButton *PB_Up;
    QPushButton *PB_Down;
    QPushButton *PB_DI;
    QPushButton *PB_DO;
    QLabel *L_DateTime;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1536, 832);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1024, 768));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 1531, 761));
        pageLogin = new QWidget();
        pageLogin->setObjectName("pageLogin");
        groupBox = new QGroupBox(pageLogin);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(550, 240, 451, 311));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        groupBox->setFont(font);
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"font-size: 22px;\n"
"}"));
        PB_View = new QPushButton(groupBox);
        PB_View->setObjectName("PB_View");
        PB_View->setEnabled(true);
        PB_View->setGeometry(QRect(380, 146, 61, 31));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setBold(true);
        PB_View->setFont(font1);
        PB_View->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    color: #66ff66;\n"
"    background-color: #0f2a0f;\n"
"    border: 1px solid #33ff33;\n"
"    font-family: 'Arial';\n"
"    font-size: 14px;\n"
"    font-weight: 700;\n"
"    padding: 4px 8px;\n"
"    min-height: 14px;\n"
"    border-radius: 2px;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/CloseEye_Green.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_View->setIcon(icon);
        PB_View->setIconSize(QSize(20, 20));
        layoutWidget_3 = new QWidget(groupBox);
        layoutWidget_3->setObjectName("layoutWidget_3");
        layoutWidget_3->setGeometry(QRect(120, 220, 195, 42));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        PB_login = new QPushButton(layoutWidget_3);
        PB_login->setObjectName("PB_login");
        PB_login->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    color: #66ff66;\n"
"    background-color: #0f2a0f;\n"
"    border: 1px solid #33ff33;\n"
"    font-family: 'Arial';\n"
"    font-size: 14px;\n"
"    font-weight: 700;\n"
"    padding: 4px 8px;\n"
"    min-height: 15px;\n"
"    border-radius: 2px;\n"
"}"));

        horizontalLayout_4->addWidget(PB_login);

        PB_Cancel = new QPushButton(layoutWidget_3);
        PB_Cancel->setObjectName("PB_Cancel");
        PB_Cancel->setFont(font1);
        PB_Cancel->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    color: #66ff66;\n"
"    background-color: #0f2a0f;\n"
"    border: 1px solid #33ff33;\n"
"    font-family: 'Arial';\n"
"    font-size: 14px;\n"
"    font-weight: 700;\n"
"    padding: 4px 8px;\n"
"    min-height: 15px;\n"
"    border-radius: 2px;\n"
"}"));

        horizontalLayout_4->addWidget(PB_Cancel);

        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(14, 71, 362, 39));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"font-size: 18px;\n"
"}"));

        horizontalLayout_2->addWidget(label);

        LE_Username = new QLineEdit(layoutWidget);
        LE_Username->setObjectName("LE_Username");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(14);
        LE_Username->setFont(font2);

        horizontalLayout_2->addWidget(LE_Username);

        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(15, 145, 359, 35));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName("label_4");
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("QLabel {\n"
"font-size: 18px;\n"
"}"));

        horizontalLayout_3->addWidget(label_4);

        LE_Password = new QLineEdit(layoutWidget1);
        LE_Password->setObjectName("LE_Password");
        LE_Password->setFont(font2);
        LE_Password->setEchoMode(QLineEdit::EchoMode::Password);
        LE_Password->setClearButtonEnabled(true);

        horizontalLayout_3->addWidget(LE_Password);

        label_5 = new QLabel(pageLogin);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(560, 40, 410, 69));
        label_5->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #66ff66;\n"
"    background-color: #0b220b;\n"
"    border: 1px solid #33ff33;\n"
"    font-family: 'Noto Sans';\n"
"    font-size: 45px;\n"
"    font-weight: 700;\n"
"    padding: 4px 8px;\n"
"    min-height: 15px;\n"
"    border-radius: 2px;\n"
"}"));
        leftImageLabel = new QLabel(pageLogin);
        leftImageLabel->setObjectName("leftImageLabel");
        leftImageLabel->setGeometry(QRect(70, 140, 431, 501));
        rightImageLabel = new QLabel(pageLogin);
        rightImageLabel->setObjectName("rightImageLabel");
        rightImageLabel->setGeometry(QRect(1040, 160, 431, 501));
        stackedWidget->addWidget(pageLogin);
        pageMainWindow = new QWidget();
        pageMainWindow->setObjectName("pageMainWindow");
        L_FunctionKeys_Left = new QLabel(pageMainWindow);
        L_FunctionKeys_Left->setObjectName("L_FunctionKeys_Left");
        L_FunctionKeys_Left->setGeometry(QRect(0, 40, 111, 41));
        L_FunctionKeys_Left->setMinimumSize(QSize(0, 25));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Noto Sans")});
        font3.setBold(true);
        L_FunctionKeys_Left->setFont(font3);
        L_FunctionKeys_Left->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #66ff66;\n"
"    background-color: #0f2a0f;\n"
"    border: 1px solid #33ff33;\n"
"    font-family: 'Noto Sans';\n"
"    font-size: 15px;\n"
"    font-weight: 700;\n"
"    padding: 4px 8px;\n"
"    min-height: 15px;\n"
"    border-radius: 2px;\n"
"    qproperty-alignment: AlignCenter;\n"
"}"));
        layoutWidget2 = new QWidget(pageMainWindow);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(20, 90, 61, 621));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        PB_Home = new TransparentPushButton(layoutWidget2);
        PB_Home->setObjectName("PB_Home");
        QFont font4;
        font4.setPointSize(11);
        font4.setBold(true);
        PB_Home->setFont(font4);
        PB_Home->setStyleSheet(QString::fromUtf8(""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/home_greencolour.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_Home->setIcon(icon1);
        PB_Home->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(PB_Home);

        PB_RequestRelease = new TransparentPushButton(layoutWidget2);
        PB_RequestRelease->setObjectName("PB_RequestRelease");
        PB_RequestRelease->setFont(font4);
        PB_RequestRelease->setStyleSheet(QString::fromUtf8(""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/Request_g.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_RequestRelease->setIcon(icon2);
        PB_RequestRelease->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(PB_RequestRelease);

        PB_Fire = new TransparentPushButton(layoutWidget2);
        PB_Fire->setObjectName("PB_Fire");
        PB_Fire->setFont(font4);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/Firing_Mode_svg.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_Fire->setIcon(icon3);
        PB_Fire->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(PB_Fire);

        PB_MissileSelection = new TransparentPushButton(layoutWidget2);
        PB_MissileSelection->setObjectName("PB_MissileSelection");
        PB_MissileSelection->setFont(font4);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/missile_green.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_MissileSelection->setIcon(icon4);
        PB_MissileSelection->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(PB_MissileSelection);

        PB_EngageLauncher = new TransparentPushButton(layoutWidget2);
        PB_EngageLauncher->setObjectName("PB_EngageLauncher");
        PB_EngageLauncher->setFont(font4);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/Engage_Launcher.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_EngageLauncher->setIcon(icon5);
        PB_EngageLauncher->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(PB_EngageLauncher);

        PB_MissileEngage = new TransparentPushButton(layoutWidget2);
        PB_MissileEngage->setObjectName("PB_MissileEngage");
        PB_MissileEngage->setFont(font4);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/Missile_Engage.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_MissileEngage->setIcon(icon6);
        PB_MissileEngage->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(PB_MissileEngage);

        PB_Plus = new TransparentPushButton(layoutWidget2);
        PB_Plus->setObjectName("PB_Plus");
        PB_Plus->setFont(font4);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icon/Plus_s.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_Plus->setIcon(icon7);
        PB_Plus->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(PB_Plus);

        PB_Minus = new TransparentPushButton(layoutWidget2);
        PB_Minus->setObjectName("PB_Minus");
        PB_Minus->setFont(font4);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icon/minus_s.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_Minus->setIcon(icon8);
        PB_Minus->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(PB_Minus);

        PB_LogOut = new TransparentPushButton(layoutWidget2);
        PB_LogOut->setObjectName("PB_LogOut");
        PB_LogOut->setFont(font4);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icon/logout.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_LogOut->setIcon(icon9);
        PB_LogOut->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(PB_LogOut);

        layoutWidget3 = new QWidget(pageMainWindow);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(0, 0, 194, 20));
        nodeStatusLayout = new QHBoxLayout(layoutWidget3);
        nodeStatusLayout->setSpacing(12);
        nodeStatusLayout->setObjectName("nodeStatusLayout");
        nodeStatusLayout->setContentsMargins(10, 2, 10, 2);
        node1StatusLabel = new QLabel(layoutWidget3);
        node1StatusLabel->setObjectName("node1StatusLabel");
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Courier New")});
        font5.setPointSize(8);
        font5.setBold(true);
        node1StatusLabel->setFont(font5);

        nodeStatusLayout->addWidget(node1StatusLabel);

        node2StatusLabel = new QLabel(layoutWidget3);
        node2StatusLabel->setObjectName("node2StatusLabel");
        node2StatusLabel->setFont(font5);

        nodeStatusLayout->addWidget(node2StatusLabel);

        layoutWidget4 = new QWidget(layoutWidget3);
        layoutWidget4->setObjectName("layoutWidget4");
        QFont font6;
        font6.setPointSize(12);
        layoutWidget4->setFont(font6);

        nodeStatusLayout->addWidget(layoutWidget4);

        cameraGroup = new QGroupBox(pageMainWindow);
        cameraGroup->setObjectName("cameraGroup");
        cameraGroup->setGeometry(QRect(110, 30, 1311, 721));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cameraGroup->sizePolicy().hasHeightForWidth());
        cameraGroup->setSizePolicy(sizePolicy1);
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Consolas")});
        font7.setBold(true);
        cameraGroup->setFont(font7);
        cameraGroup->setAlignment(Qt::AlignmentFlag::AlignCenter);
        cameraView = new QGraphicsView(cameraGroup);
        cameraView->setObjectName("cameraView");
        cameraView->setGeometry(QRect(0, 0, 1311, 721));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(cameraView->sizePolicy().hasHeightForWidth());
        cameraView->setSizePolicy(sizePolicy2);
        cameraView->setMinimumSize(QSize(600, 420));
        cameraView->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 127);"));
        cameraView->setFrameShape(QFrame::Shape::NoFrame);
        layoutWidget5 = new QWidget(cameraGroup);
        layoutWidget5->setObjectName("layoutWidget5");
        layoutWidget5->setGeometry(QRect(130, 0, 211, 152));
        horizontalLayout = new QHBoxLayout(layoutWidget5);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        missileWidget = new MissileWidget(layoutWidget5);
        missileWidget->setObjectName("missileWidget");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(missileWidget->sizePolicy().hasHeightForWidth());
        missileWidget->setSizePolicy(sizePolicy3);
        missileWidget->setMinimumSize(QSize(90, 150));
        missileWidget->setMaximumSize(QSize(100, 165));

        horizontalLayout->addWidget(missileWidget);

        targetWidget = new TargetWidget(layoutWidget5);
        targetWidget->setObjectName("targetWidget");
        sizePolicy.setHeightForWidth(targetWidget->sizePolicy().hasHeightForWidth());
        targetWidget->setSizePolicy(sizePolicy);
        targetWidget->setMinimumSize(QSize(90, 150));
        targetWidget->setMaximumSize(QSize(110, 170));

        horizontalLayout->addWidget(targetWidget);

        layoutWidget6 = new QWidget(cameraGroup);
        layoutWidget6->setObjectName("layoutWidget6");
        layoutWidget6->setGeometry(QRect(980, 410, 331, 311));
        gridLayout_3 = new QGridLayout(layoutWidget6);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        azimuthWidget = new AzimuthWidget(layoutWidget6);
        azimuthWidget->setObjectName("azimuthWidget");
        sizePolicy3.setHeightForWidth(azimuthWidget->sizePolicy().hasHeightForWidth());
        azimuthWidget->setSizePolicy(sizePolicy3);
        azimuthWidget->setMaximumSize(QSize(235, 275));
        azimuthWidget->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 127);"));

        gridLayout_3->addWidget(azimuthWidget, 0, 0, 1, 1);

        elevationWidget = new ElevationWidget(layoutWidget6);
        elevationWidget->setObjectName("elevationWidget");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(1);
        sizePolicy4.setHeightForWidth(elevationWidget->sizePolicy().hasHeightForWidth());
        elevationWidget->setSizePolicy(sizePolicy4);
        elevationWidget->setMinimumSize(QSize(45, 140));
        elevationWidget->setMaximumSize(QSize(100, 275));

        gridLayout_3->addWidget(elevationWidget, 0, 1, 1, 1);

        targetTypeGroup = new QGroupBox(layoutWidget6);
        targetTypeGroup->setObjectName("targetTypeGroup");
        QFont font8;
        font8.setFamilies({QString::fromUtf8("Segoe UI")});
        font8.setPointSize(11);
        font8.setBold(true);
        targetTypeGroup->setFont(font8);
        targetTypeGroup->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);"));
        gridLayout = new QGridLayout(targetTypeGroup);
        gridLayout->setObjectName("gridLayout");
        targetTypeCombo = new QComboBox(targetTypeGroup);
        targetTypeCombo->addItem(QString());
        targetTypeCombo->addItem(QString());
        targetTypeCombo->addItem(QString());
        targetTypeCombo->setObjectName("targetTypeCombo");
        QFont font9;
        font9.setPointSize(10);
        targetTypeCombo->setFont(font9);

        gridLayout->addWidget(targetTypeCombo, 0, 0, 1, 1);


        gridLayout_3->addWidget(targetTypeGroup, 1, 0, 1, 2);

        missileSelectionCombo = new QGroupBox(cameraGroup);
        missileSelectionCombo->setObjectName("missileSelectionCombo");
        missileSelectionCombo->setGeometry(QRect(650, 640, 329, 76));
        missileSelectionCombo->setFont(font8);
        missileSelectionCombo->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);"));
        gridLayout_2 = new QGridLayout(missileSelectionCombo);
        gridLayout_2->setObjectName("gridLayout_2");
        MissileSelectionCombo = new QComboBox(missileSelectionCombo);
        MissileSelectionCombo->addItem(QString());
        MissileSelectionCombo->addItem(QString());
        MissileSelectionCombo->addItem(QString());
        MissileSelectionCombo->addItem(QString());
        MissileSelectionCombo->setObjectName("MissileSelectionCombo");
        MissileSelectionCombo->setFont(font9);

        gridLayout_2->addWidget(MissileSelectionCombo, 0, 0, 1, 1);

        layoutWidget31 = new QWidget(pageMainWindow);
        layoutWidget31->setObjectName("layoutWidget31");
        layoutWidget31->setGeometry(QRect(1450, 80, 61, 641));
        verticalLayout_2 = new QVBoxLayout(layoutWidget31);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        PB_DayCamera = new TransparentPushButton(layoutWidget31);
        PB_DayCamera->setObjectName("PB_DayCamera");
        PB_DayCamera->setFont(font4);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icon/Day_cam_svg.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_DayCamera->setIcon(icon10);
        PB_DayCamera->setIconSize(QSize(40, 40));

        verticalLayout_2->addWidget(PB_DayCamera);

        PB_LRF = new TransparentPushButton(layoutWidget31);
        PB_LRF->setObjectName("PB_LRF");
        PB_LRF->setFont(font4);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icon/LRF_png1.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_LRF->setIcon(icon11);
        PB_LRF->setIconSize(QSize(40, 40));

        verticalLayout_2->addWidget(PB_LRF);

        PB_Zoom = new TransparentPushButton(layoutWidget31);
        PB_Zoom->setObjectName("PB_Zoom");
        PB_Zoom->setFont(font4);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/icon/Zoom_svgL.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_Zoom->setIcon(icon12);
        PB_Zoom->setIconSize(QSize(40, 40));

        verticalLayout_2->addWidget(PB_Zoom);

        PB_Focus = new TransparentPushButton(layoutWidget31);
        PB_Focus->setObjectName("PB_Focus");
        PB_Focus->setFont(font4);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/icon/Focus_svg.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_Focus->setIcon(icon13);
        PB_Focus->setIconSize(QSize(40, 40));

        verticalLayout_2->addWidget(PB_Focus);

        PB_ExposureGain = new TransparentPushButton(layoutWidget31);
        PB_ExposureGain->setObjectName("PB_ExposureGain");
        PB_ExposureGain->setFont(font4);
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/icon/exposure_svg.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_ExposureGain->setIcon(icon14);
        PB_ExposureGain->setIconSize(QSize(40, 40));

        verticalLayout_2->addWidget(PB_ExposureGain);

        PB_Polarity = new TransparentPushButton(layoutWidget31);
        PB_Polarity->setObjectName("PB_Polarity");
        PB_Polarity->setFont(font4);
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/icon/Polarity.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_Polarity->setIcon(icon15);
        PB_Polarity->setIconSize(QSize(40, 40));

        verticalLayout_2->addWidget(PB_Polarity);

        PB_NUC = new TransparentPushButton(layoutWidget31);
        PB_NUC->setObjectName("PB_NUC");
        PB_NUC->setFont(font4);
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/icon/infrared (1).svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_NUC->setIcon(icon16);
        PB_NUC->setIconSize(QSize(40, 40));

        verticalLayout_2->addWidget(PB_NUC);

        PB_pageMaintenance = new TransparentPushButton(layoutWidget31);
        PB_pageMaintenance->setObjectName("PB_pageMaintenance");
        PB_pageMaintenance->setFont(font4);
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/icon/pageMaintenance.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_pageMaintenance->setIcon(icon17);
        PB_pageMaintenance->setIconSize(QSize(40, 40));

        verticalLayout_2->addWidget(PB_pageMaintenance);

        PB_pageStatusPanel = new TransparentPushButton(layoutWidget31);
        PB_pageStatusPanel->setObjectName("PB_pageStatusPanel");
        PB_pageStatusPanel->setFont(font4);
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/icon/pageStatusPanel.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_pageStatusPanel->setIcon(icon18);
        PB_pageStatusPanel->setIconSize(QSize(40, 40));

        verticalLayout_2->addWidget(PB_pageStatusPanel);

        L_FunctionKeys_Left_2 = new QLabel(pageMainWindow);
        L_FunctionKeys_Left_2->setObjectName("L_FunctionKeys_Left_2");
        L_FunctionKeys_Left_2->setGeometry(QRect(1420, 40, 111, 41));
        L_FunctionKeys_Left_2->setMinimumSize(QSize(0, 25));
        L_FunctionKeys_Left_2->setFont(font3);
        L_FunctionKeys_Left_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    color: #66ff66;\n"
"    background-color: #0f2a0f;\n"
"    border: 1px solid #33ff33;\n"
"    font-family: 'Noto Sans';\n"
"    font-size: 15px;\n"
"    font-weight: 700;\n"
"    padding: 4px 8px;\n"
"    min-height: 15px;\n"
"    border-radius: 2px;\n"
"    qproperty-alignment: AlignCenter;\n"
"}"));
        label_6 = new QLabel(pageMainWindow);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(710, 0, 91, 20));
        label_7 = new QLabel(pageMainWindow);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(840, 0, 121, 20));
        pbRecord = new QPushButton(pageMainWindow);
        pbRecord->setObjectName("pbRecord");
        pbRecord->setGeometry(QRect(20, 720, 61, 31));
        stackedWidget->addWidget(pageMainWindow);
        pageMaintenance = new QWidget();
        pageMaintenance->setObjectName("pageMaintenance");
        label_2 = new QLabel(pageMaintenance);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(690, 290, 461, 171));
        QFont font10;
        font10.setPointSize(15);
        label_2->setFont(font10);
        layoutWidget7 = new QWidget(pageMaintenance);
        layoutWidget7->setObjectName("layoutWidget7");
        layoutWidget7->setGeometry(QRect(10, 600, 61, 141));
        verticalLayout_3 = new QVBoxLayout(layoutWidget7);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        PB_PreviousPage = new TransparentPushButton(layoutWidget7);
        PB_PreviousPage->setObjectName("PB_PreviousPage");
        PB_PreviousPage->setFont(font4);
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/icon/Back_button.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        PB_PreviousPage->setIcon(icon19);
        PB_PreviousPage->setIconSize(QSize(40, 40));

        verticalLayout_3->addWidget(PB_PreviousPage);

        PB_Logout = new TransparentPushButton(layoutWidget7);
        PB_Logout->setObjectName("PB_Logout");
        PB_Logout->setFont(font4);
        PB_Logout->setIcon(icon9);
        PB_Logout->setIconSize(QSize(40, 40));

        verticalLayout_3->addWidget(PB_Logout);

        stackedWidget->addWidget(pageMaintenance);
        pageStatusPanel = new QWidget();
        pageStatusPanel->setObjectName("pageStatusPanel");
        label_3 = new QLabel(pageStatusPanel);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(620, 370, 571, 141));
        label_3->setFont(font10);
        layoutWidget8 = new QWidget(pageStatusPanel);
        layoutWidget8->setObjectName("layoutWidget8");
        layoutWidget8->setGeometry(QRect(10, 596, 61, 141));
        verticalLayout_4 = new QVBoxLayout(layoutWidget8);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        PB_PreviousPage_2 = new TransparentPushButton(layoutWidget8);
        PB_PreviousPage_2->setObjectName("PB_PreviousPage_2");
        PB_PreviousPage_2->setFont(font4);
        PB_PreviousPage_2->setIcon(icon19);
        PB_PreviousPage_2->setIconSize(QSize(40, 40));

        verticalLayout_4->addWidget(PB_PreviousPage_2);

        PB_Logout_2 = new TransparentPushButton(layoutWidget8);
        PB_Logout_2->setObjectName("PB_Logout_2");
        PB_Logout_2->setFont(font4);
        PB_Logout_2->setIcon(icon9);
        PB_Logout_2->setIconSize(QSize(40, 40));

        verticalLayout_4->addWidget(PB_Logout_2);

        layoutWidget9 = new QWidget(pageStatusPanel);
        layoutWidget9->setObjectName("layoutWidget9");
        layoutWidget9->setGeometry(QRect(1080, 320, 95, 211));
        verticalLayout_5 = new QVBoxLayout(layoutWidget9);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        PB_Up = new QPushButton(layoutWidget9);
        PB_Up->setObjectName("PB_Up");

        verticalLayout_5->addWidget(PB_Up);

        PB_Down = new QPushButton(layoutWidget9);
        PB_Down->setObjectName("PB_Down");

        verticalLayout_5->addWidget(PB_Down);

        PB_DI = new QPushButton(layoutWidget9);
        PB_DI->setObjectName("PB_DI");

        verticalLayout_5->addWidget(PB_DI);

        PB_DO = new QPushButton(layoutWidget9);
        PB_DO->setObjectName("PB_DO");

        verticalLayout_5->addWidget(PB_DO);

        stackedWidget->addWidget(pageStatusPanel);
        L_DateTime = new QLabel(centralWidget);
        L_DateTime->setObjectName("L_DateTime");
        L_DateTime->setGeometry(QRect(1230, 755, 301, 21));
        MainWindow->setCentralWidget(centralWidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1536, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Sign In", nullptr));
        PB_View->setText(QString());
        PB_login->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        PB_Cancel->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "UserName ", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Password ", nullptr));
        LE_Password->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "SLMS for P044", nullptr));
        leftImageLabel->setText(QString());
        rightImageLabel->setText(QString());
        L_FunctionKeys_Left->setText(QCoreApplication::translate("MainWindow", "Function", nullptr));
        PB_Home->setText(QString());
        PB_RequestRelease->setText(QString());
        PB_Fire->setText(QString());
        PB_MissileSelection->setText(QString());
        PB_EngageLauncher->setText(QString());
        PB_MissileEngage->setText(QString());
        PB_Plus->setText(QString());
        PB_Minus->setText(QString());
        PB_LogOut->setText(QString());
        node1StatusLabel->setText(QCoreApplication::translate("MainWindow", "\342\227\217 N1:OFF", nullptr));
        node2StatusLabel->setText(QCoreApplication::translate("MainWindow", "\342\227\217 N2:OFF", nullptr));
        cameraGroup->setTitle(QString());
        targetTypeGroup->setTitle(QCoreApplication::translate("MainWindow", "Target Type", nullptr));
        targetTypeCombo->setItemText(0, QCoreApplication::translate("MainWindow", "DRONE", nullptr));
        targetTypeCombo->setItemText(1, QCoreApplication::translate("MainWindow", "HELICOPTER", nullptr));
        targetTypeCombo->setItemText(2, QCoreApplication::translate("MainWindow", "AIRCRAFT", nullptr));

        missileSelectionCombo->setTitle(QCoreApplication::translate("MainWindow", "Missile Selection", nullptr));
        MissileSelectionCombo->setItemText(0, QCoreApplication::translate("MainWindow", "Missile 1", nullptr));
        MissileSelectionCombo->setItemText(1, QCoreApplication::translate("MainWindow", "Missile 2", nullptr));
        MissileSelectionCombo->setItemText(2, QCoreApplication::translate("MainWindow", "Missile 3", nullptr));
        MissileSelectionCombo->setItemText(3, QCoreApplication::translate("MainWindow", "Missile 4", nullptr));

        PB_DayCamera->setText(QString());
        PB_LRF->setText(QString());
        PB_Zoom->setText(QString());
        PB_Focus->setText(QString());
        PB_ExposureGain->setText(QString());
        PB_Polarity->setText(QString());
        PB_NUC->setText(QString());
        PB_pageMaintenance->setText(QString());
        PB_pageStatusPanel->setText(QString());
        L_FunctionKeys_Left_2->setText(QCoreApplication::translate("MainWindow", "Function", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Active: FCS", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Active: EOSS", nullptr));
        pbRecord->setText(QCoreApplication::translate("MainWindow", "REC", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Maintenance Page", nullptr));
        PB_PreviousPage->setText(QString());
        PB_Logout->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "Status Panel Page", nullptr));
        PB_PreviousPage_2->setText(QString());
        PB_Logout_2->setText(QString());
        PB_Up->setText(QCoreApplication::translate("MainWindow", "UP", nullptr));
        PB_Down->setText(QCoreApplication::translate("MainWindow", "DOWN", nullptr));
        PB_DI->setText(QCoreApplication::translate("MainWindow", "DI", nullptr));
        PB_DO->setText(QCoreApplication::translate("MainWindow", "DO", nullptr));
        L_DateTime->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
