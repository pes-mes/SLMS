#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "screenrecorder.h"

#include <QMainWindow>
#include <QTcpSocket>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QCamera>
#include <QMediaCaptureSession>
#include <QVideoSink>
#include <QVideoFrame>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QKeyEvent>
#include <QEvent>
#include <QDebug>
#include <QImage>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDate>
#include <QTime>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


//  CameraScene — QGraphicsScene with all overlay items
class CameraScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CameraScene(QObject *parent = nullptr);

    void setTargetBox(double azNorm, double elNorm, const QString &label);
    void setThermalMode(bool on);
    void setZoom(double z);
    void setBrightness(int b);
    void setFOV(int fov);
    void setConfidence(int pct);
    void setLaserRange(int m);
    void setEstimRange(int m);
    void setState(const QString &s);
    void setTargetType(const QString &t);
    void setHealth(int pct);
    void setAzEl(double az, double el);   // raw degrees for HUD readout

    void updateFrame(const QImage &img);
    void resizeOverlay(int w, int h);

    void setBoundingBoxSize(int w, int h);
    void setBoundingBoxVisible(bool visible);
    void setBoundingBoxLabel(const QString &text);

    double zoom() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void buildOverlay();
    void repositionItems();

    QGraphicsPixmapItem  *m_bg              = nullptr;
    QGraphicsLineItem    *m_hLine           = nullptr;
    QGraphicsLineItem    *m_vLine           = nullptr;
    QGraphicsItemGroup   *m_centerGroup     = nullptr;
    QGraphicsRectItem    *m_tgtBracketOuter = nullptr;
    QGraphicsRectItem    *m_tgtBracketInner = nullptr;
    QGraphicsTextItem    *m_tgtLabel        = nullptr;
    QGraphicsRectItem    *m_azElBg          = nullptr;
    QGraphicsTextItem    *m_azEl            = nullptr;
    QGraphicsRectItem    *m_zoomBg          = nullptr;
    QGraphicsTextItem    *m_zoomBrtFov      = nullptr;
    QGraphicsRectItem    *m_statusBar       = nullptr;
    QGraphicsRectItem    *m_stateBg         = nullptr;
    QGraphicsTextItem    *m_statusTI        = nullptr;
    QGraphicsTextItem    *m_statusTgt       = nullptr;
    QGraphicsTextItem    *m_statusZoom      = nullptr;
    QGraphicsTextItem    *m_statusConf      = nullptr;
    QGraphicsTextItem    *m_stateLabel      = nullptr;
    QGraphicsRectItem    *m_healthBarBg     = nullptr;
    QGraphicsRectItem    *m_healthBarFg     = nullptr;
    QGraphicsTextItem    *m_healthLabel     = nullptr;

    QGraphicsRectItem *m_boundingBox = nullptr;
    QGraphicsTextItem *m_bboxLabel   = nullptr;
    int m_bboxW = 384; // Width should be the larger number for 4:3
    int m_bboxH = 288; // Height should be the smaller number for 4:3

    // raw az/el in degrees (from Node2)
    double  m_azDeg     = 0.0;
    double  m_elDeg     = 0.0;

    // normalised (0..1) for target bracket position
    double  m_az        = 0.5;
    double  m_el        = 0.5;

    double  m_zoom      = 1.0;
    QImage m_lastFrame;

    int     m_brt       = 50;
    int     m_fov       = 15;
    int     m_conf      = 0;
    int     m_lr        = 0;
    int     m_er        = 0;
    QString m_state     = "OFFLINE";
    QString m_tgtType   = "UAV-1";
    bool    m_thermal   = false;
    int     m_health    = 0;

    // represents the total width and height of the camerascene only.
    int     m_sceneW    = 1040;
    int     m_sceneH    = 540;

    void updateHUD();
    void updateTargetPosition();

    // for the coordinates using the mouse pointer.
    QGraphicsTextItem *m_clickLabel = nullptr;

};

//  MainWindow
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *ev) override;
    bool eventFilter(QObject *obj, QEvent *ev) override;

private slots:
    void node1Connected();
    void node1Disconnected();
    void node1DataReceived();

    void node2Connected();
    void node2Disconnected();
    void node2DataReceived();

    void tryReconnect();

    void onNewVideoFrame(const QVideoFrame &frame);

    void onEngageClicked();
    void onFireClicked();
    void onZoomIn();
    void onZoomOut();
    void onZoomReset();
    void onBrightnessUp();
    void onBrightnessDown();
    void onFovUp();
    void onFovDown();
    void on_PB_LRF_clicked();
    void on_PB_Polarity_clicked();
    void on_PB_NUC_clicked();
    void on_PB_Home_clicked();
    void on_PB_Zoom_clicked();
    void on_PB_Fire_clicked();
    void on_PB_Plus_clicked();
    void on_PB_Minus_clicked();
    void on_PB_RequestRelease_clicked();
    void on_PB_EngageLauncher_clicked();
    void on_PB_MissileSelection_clicked();
    void on_PB_MissileEngage_clicked();
    void on_PB_Focus_clicked();
    void on_PB_ExposureGain_clicked();

    void on_PB_DayCamera_clicked();

    void on_PB_login_clicked();

    void on_PB_Cancel_clicked();


    void on_PB_View_clicked();


    void on_PB_LogOut_clicked();

    void on_PB_pageMaintenance_clicked();

    void on_PB_pageStatusPanel_clicked();

    void on_PB_PreviousPage_clicked();

    void on_PB_Logout_clicked();

    void on_PB_PreviousPage_2_clicked();

    void on_PB_Logout_2_clicked();

    void myfunction();

    void onRecordButtonClicked();
    void onRecordingStarted();
    void onRecordingStopped(const QString &filePath);
    void onRecordingError(const QString &errorMessage);

private:
    Ui::MainWindow *ui;

    QTcpSocket *node1Socket;
    QTcpSocket *node2Socket;
    QTimer     *reconnectTimer;
    QString     node1Buffer;
    QString     node2Buffer;



    void connectToNode1();
    void connectToNode2();
    void processNode1Line(const QString &line);
    void processNode2Line(const QString &line);
    int  stateTextToIndex(const QString &s);
    void syncSceneToView();

    QCamera              *m_camera         = nullptr;
    QMediaCaptureSession *m_captureSession = nullptr;
    QVideoSink           *m_videoSink      = nullptr;

    CameraScene          *m_scene          = nullptr;

    ScreenRecorder *m_screenRecorder;

    int     m_az         = 0;
    int     m_el         = 0;
    double  m_zoom       = 1.0;
    int     m_brt        = 50;
    int     m_fov        = 15;
    bool    m_thermal    = false;
    QString m_sysState   = "OFFLINE";

    bool isNightMode = false; // Tracks if night mode is active

    bool m_zoomMode = false;

    static constexpr quint8 ZOOM_IN  = 0x01;
    static constexpr quint8 ZOOM_OUT = 0x02;
    static constexpr quint8 ZOOM_STOP = 0x03;

    void zoomCommand(quint8 value);

    QTimer *m_zoomTimer = nullptr;
    int m_zoomDirection = 0;   // +1 = zoom in, -1 = zoom out

    QTimer *timer;
};

#endif // MAINWINDOW_H
