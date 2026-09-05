#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "screenrecorder.h"

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QColor>
#include <QtMath>
#include <QMediaDevices>
#include <QCameraDevice>
#include <QVideoFrame>
#include <QImage>
#include <QMessageBox>
#include <QResizeEvent>
#include <QShortcut>
#include <QToolButton>
#include <QStyle>
#include <QPixmap>
#include <QDebug>



//  Palette
static const QColor GN   ("#22cc22");
static const QColor GN_DK("#0d500d");
static const QColor GN_MK("#1a8a1a");
static const QColor OR   ("#ff5500");
static const QColor GOLD ("#d4a800");
static const QColor BG   ("#030803");
static const QColor BGDK ("#0a120a");

static QFont hudFont(int sz = 11, bool bold = true)
{                                                   // It is declared as static to restrict its visibility to the single .cpp file where it is written, preventing name clashes in other parts of your project.
    QFont f("Consolas", sz);
    f.setBold(bold);
    return f;
}

//  CameraScene
CameraScene::CameraScene(QObject *parent)
    : QGraphicsScene(parent)
{
    setBackgroundBrush(QBrush(BG));
    buildOverlay();
}

void CameraScene::buildOverlay()
{
    int W  = m_sceneW;
    int H  = m_sceneH;
    int cx = W / 2;
    int cy = H / 2;

    // Background placeholder
    m_bg = addPixmap(QPixmap());
    m_bg->setZValue(0);

    // Full crosshair
    QPen crossPen(GN, 0.8);
    m_hLine = addLine(0, cy, W, cy, crossPen);
    m_vLine = addLine(cx, 0, cx, H, crossPen);
    m_hLine->setZValue(2);
    m_vLine->setZValue(2);

    // Center dot + ring group
    m_centerGroup = new QGraphicsItemGroup();
    addItem(m_centerGroup);
    // -5,-5 represents (top left corner). the bounding starts 5 units to the left and 5 units above the origin. -10,-10 represents shape spans 10 unit width and 10 units height
    auto *dot   = addEllipse(-5, -5, 10, 10, QPen(GN, 1.2), QBrush(GN_DK));
    auto *cring = addEllipse(-18, -18, 36, 36, QPen(GN, 1.0), Qt::NoBrush);
    m_centerGroup->addToGroup(dot);
    m_centerGroup->addToGroup(cring);
    m_centerGroup->setPos(cx, cy);
    m_centerGroup->setZValue(3);

    // Centre bounding box (fixed rectangle at the middle of the camera view)    // boundingbox drawn using this here.
    QPen bboxPen(OR, 1.5);
    // -m_bboxW / 2.0, -m_bboxH / 2.0 represents the x and y coordinates. m_bboxW, m_bboxH represents the width and height.
    m_boundingBox = addRect(-m_bboxW / 2.0, -m_bboxH / 2.0, m_bboxW, m_bboxH,
                            bboxPen, Qt::NoBrush);
    m_boundingBox->setPos(cx, cy);
    m_boundingBox->setZValue(4);                            // controls the drawing order of your m_bboxLabel inside the QGraphicsScene
                                                            // Higher Z value generally means the item is drawn on top of items with lower Z values

    m_bboxLabel = addText("TARGET", hudFont(11));           // HUD: Heads-up display
    m_bboxLabel->setDefaultTextColor(OR);
    m_bboxLabel->setZValue(4);

    // Target bracket
    QPen tgtPen(GOLD, 1.2);
    m_tgtBracketOuter = addRect(0, 0, 38, 38, tgtPen, Qt::NoBrush);    // x and y coordinates(0,0) and 38,38 is width and height
    m_tgtBracketInner = addRect(0, 0, 18, 18, QPen(GOLD, 0.8), Qt::NoBrush);
    m_tgtBracketOuter->setZValue(5);
    m_tgtBracketInner->setZValue(5);

    m_tgtLabel = addText("", hudFont(11));
    m_tgtLabel->setDefaultTextColor(GOLD);
    m_tgtLabel->setZValue(5);

    //  Top-left HUD: AZ / EL / LR / ER / CONF
    m_azElBg = addRect(4, 4, 140, 90, Qt::NoPen, QBrush(QColor(0, 0, 0, 160)));

    m_azElBg->setZValue(5.5);

    m_azEl = addText("AZ:   0.0°\nEL:   0.0°\nLR:   0m\nER:   0m\nCONF: 0%", hudFont(11));
    m_azEl->setDefaultTextColor(GN);
    m_azEl->setPos(8, 6);
    m_azEl->setZValue(6);

    //  Top-right HUD: ZOOM / BRT / FOV
    m_zoomBg = addRect(W - 110, 4, 106, 52, Qt::NoPen, QBrush(QColor(0, 0, 0, 160)));  // Qt::NoPen0no line at all. For example, QPainter::drawRect() fills but does not draw any boundary line.
    m_zoomBg->setZValue(5.5);

    m_zoomBrtFov = addText("ZOOM 1.0x\nBRT  50\nFOV  15°", hudFont(11));
    m_zoomBrtFov->setDefaultTextColor(GN);
    m_zoomBrtFov->setZValue(6);

    //  Bottom-left status panel (4 lines)
    m_statusBar = addRect(4, H - 72, 260, 68, Qt::NoPen, QBrush(QColor(0, 0, 0, 160)));
    m_statusBar->setZValue(7);

    // It builds a semi-transparent black background box and then dynamically stacks four lines of text neatly inside it.

    const int panelBottom = H - 6;
    const int lineH       = 14;
    const int panelLeft   = 8;

    auto makeStatusV = [&](const QString &t, int lineIdx) {
        auto *item = addText(t, hudFont(11));
        item->setDefaultTextColor(GN);
        item->setPos(panelLeft, panelBottom - lineH * (4 - lineIdx));
        item->setZValue(8);
        return item;
    };

    // Initialize the Thermal Imaging status indicator as OFF.
    m_statusTI = makeStatusV("TI: OFF", 0);

    m_statusTgt  = makeStatusV("TGT: UAV-1",1);
    m_statusZoom = makeStatusV("ZOOM: 1.0x  BRT: 50  FOV: 15°",2);
    m_statusConf = makeStatusV("CONFIDENCE: 0%",3);

    // // ── Bottom-right STATE label ──────────────────────────────
    // m_stateBg   = addRect(0, 0, 10, 10, Qt::NoPen, QBrush(QColor(0, 0, 0, 160)));
    // m_stateBg->setZValue(7);

    // m_stateLabel = addText("STATE: OFFLINE", hudFont(11));
    // m_stateLabel->setDefaultTextColor(QColor("#cc3300"));
    // m_stateLabel->setZValue(8);

    // ── Health bar
    // int hbW = 160, hbH = 10;
    // int hbX = cx - hbW / 2;
    // int hbY = H - 20;
    // m_healthBarBg = addRect(hbX, hbY, hbW, hbH, QPen(GN_DK, 0.8), QBrush(QColor("#0a0a0a")));
    // m_healthBarBg->setZValue(7);
    // m_healthBarFg = addRect(hbX, hbY, 0, hbH, Qt::NoPen, QBrush(GN_DK));
    // m_healthBarFg->setZValue(8);
    // m_healthLabel = addText("HEALTH: 0%", hudFont(11));
    // m_healthLabel->setDefaultTextColor(GN);
    // m_healthLabel->setPos(hbX - 10, hbY - 15);
    // m_healthLabel->setZValue(8);

    repositionItems();
    updateHUD();
}

void CameraScene::repositionItems()
{
    int W  = m_sceneW;
    int H  = m_sceneH;
    int cx = W / 2;
    int cy = H / 2;

    setSceneRect(0, 0, W, H);

    // Crosshair is updated from here.(Not from the setCrosshairPos.
    // Crosshair + centre reticle
    if (m_hLine) m_hLine->setLine(0, cy, W, cy);    // m_hLine represents the horizontal crosshair line. 0,270 ───────────────────────────── 1040,270
    if (m_vLine) m_vLine->setLine(cx, 0, cx, H);    // represents the vertical crosshair line. Start X = 520  Start Y = 0 End X = 520  End Y = 540
    if (m_centerGroup) m_centerGroup->setPos(cx, cy);

    // Centre bounding box stays fixed at the middle of the view
    if (m_boundingBox) {
        m_boundingBox->setRect(-m_bboxW / 2.0, -m_bboxH / 2.0, m_bboxW, m_bboxH);
        m_boundingBox->setPos(cx, cy);
    }
    if (m_bboxLabel) {
        m_bboxLabel->setPos(cx - m_bboxW / 2.0, cy - m_bboxH / 2.0 - 16);
    }

    // Top-left backing rect tracks text size
    // This block of code completely overrides your manual width and height values.
    // It dynamically forces the background rectangle (m_azElBg) to stretch or shrink so it always perfectly fits the text box (m_azEl).
    if (m_azEl && m_azElBg) {
        QRectF br = m_azEl->boundingRect();
        m_azElBg->setRect(4, 4, br.width() + 8, br.height() + 4);
    }

    // Top-right text + backing rect
    if (m_zoomBrtFov) {
        QRectF br = m_zoomBrtFov->boundingRect();
        m_zoomBrtFov->setPos(W - br.width() - 6, 6);
        if (m_zoomBg)
            m_zoomBg->setRect(W - br.width() - 10, 4, br.width() + 8, br.height() + 4);
    }

    // Bottom-left 4-line panel
    {
        const int lH      = 14;
        const int pLeft   = 8;
        const int pBot    = H - 6;
        const int nLines  = 4;
        QGraphicsTextItem *lines[4] = { m_statusTI, m_statusTgt, m_statusZoom, m_statusConf };
        double maxW = 0;
        for (int i = 0; i < nLines; ++i) {
            if (!lines[i]) continue;
            lines[i]->setPos(pLeft, pBot - lH * (nLines - i));
            maxW = qMax(maxW, lines[i]->boundingRect().width());
        }
        if (m_statusBar)
            m_statusBar->setRect(4, pBot - lH * nLines - 4, maxW + 8, lH * nLines + 8);
    }

    // Bottom-right STATE label
    if (m_stateLabel) {
        QRectF br = m_stateLabel->boundingRect();
        m_stateLabel->setPos(W - br.width() - 10, H - br.height() - 6);
        if (m_stateBg)
            m_stateBg->setRect(W - br.width() - 14, H - br.height() - 10,
                               br.width() + 8, br.height() + 8);
    }

    // Health bar
    // int hbW = 160, hbH = 10;
    // int hbX = cx - hbW / 2;
    // int hbY = H - 20;
    // if (m_healthBarBg) m_healthBarBg->setRect(hbX, hbY, hbW, hbH);
    // if (m_healthBarFg) {
    //     QRectF bgR = m_healthBarBg->rect();
    //     m_healthBarFg->setRect(bgR.x(), bgR.y(), bgR.width() * m_health / 100.0, bgR.height());
    // }
    // if (m_healthLabel) m_healthLabel->setPos(hbX - 10, hbY - 15);
}

void CameraScene::resizeOverlay(int w, int h)
{
    m_sceneW = w;
    m_sceneH = h;
    repositionItems();
}

void CameraScene::updateFrame(const QImage &img)
{
    if (!m_bg)
        return;

    m_lastFrame = img;

    int zoomW = static_cast<int>(m_sceneW * m_zoom);
    int zoomH = static_cast<int>(m_sceneH * m_zoom);

    QPixmap pm = QPixmap::fromImage(img).scaled(
        zoomW,
        zoomH,
        Qt::KeepAspectRatioByExpanding,
        Qt::SmoothTransformation);      // Smooth Transformation blends pixels together when resizing an image to prevent jagged edges [Qt::SmoothTransformation: uses bilinear filtering algorithm.].

    m_bg->setPixmap(pm);

    m_bg->setPos(
        (m_sceneW - zoomW) / 2.0,
        (m_sceneH - zoomH) / 2.0);
}

// After using this code section for brightness control Video feed from the camera is getting buffered. Recheck the code and complete it.
// void CameraScene::updateFrame(const QImage &img)
// {
//     if (!m_bg)
//         return;

//     m_lastFrame = img;

//     // Create a copy of the camera frame for brightness adjustment.
//     QImage adjustedImg = img.convertToFormat(QImage::Format_RGB32);

//     // Brightness 50 is the normal level.
//     // Above 50 makes the image brighter.
//     // Below 50 makes the image darker.
//     const int adjustment = m_brt - 50;

//     for (int y = 0; y < adjustedImg.height(); ++y)
//     {
//         QRgb *line = reinterpret_cast<QRgb *>(adjustedImg.scanLine(y));

//         for (int x = 0; x < adjustedImg.width(); ++x)
//         {
//             int red   = qBound(0, qRed(line[x])   + adjustment, 255);
//             int green = qBound(0, qGreen(line[x]) + adjustment, 255);
//             int blue  = qBound(0, qBlue(line[x])  + adjustment, 255);

//             line[x] = qRgb(red, green, blue);
//         }
//     }

//     int zoomW = static_cast<int>(m_sceneW * m_zoom);
//     int zoomH = static_cast<int>(m_sceneH * m_zoom);

//     QPixmap pm = QPixmap::fromImage(adjustedImg).scaled(
//         zoomW,
//         zoomH,
//         Qt::KeepAspectRatioByExpanding,
//         Qt::SmoothTransformation);

//     m_bg->setPixmap(pm);

//     m_bg->setPos(
//         (m_sceneW - zoomW) / 2.0,
//         (m_sceneH - zoomH) / 2.0);
// }

void CameraScene::updateHUD()
{
    // Top-left: AZ / EL / LR / ER / CONF  — uses raw degree values
    if (m_azEl) {
        m_azEl->setPlainText(
            QString("AZ:  %1°\nEL:  %2°\nLR:  %3m\nER:  %4m\nCONF: %5%")
                .arg(m_azDeg, 6, 'f', 1)
                .arg(m_elDeg, 6, 'f', 1)
                .arg(m_lr)
                .arg(m_er)
                .arg(m_conf));
        if (m_azElBg) {
            QRectF br = m_azEl->boundingRect();
            m_azElBg->setRect(4, 4, br.width() + 8, br.height() + 4);
        }
    }

    // Top-right: ZOOM / BRT / FOV
    if (m_zoomBrtFov) {
        m_zoomBrtFov->setPlainText(
            QString("ZOOM %1x\nBRT  %2\nFOV  %3°")
                .arg(m_zoom, 0, 'f', 1)
                .arg(m_brt)
                .arg(m_fov));
        QRectF br = m_zoomBrtFov->boundingRect();
        m_zoomBrtFov->setPos(m_sceneW - br.width() - 6, 6);
        if (m_zoomBg)
            m_zoomBg->setRect(m_sceneW - br.width() - 10, 4,
                              br.width() + 8, br.height() + 4);
    }

    // Bottom-left panel
    // Update the Thermal Imaging status displayed in the bottom-left HUD panel.
    // Display ON when thermal mode is enabled, otherwise display OFF.
    if (m_statusTI)
        m_statusTI->setPlainText(m_thermal ? "TI: ON" : "TI: OFF");

    if (m_statusTgt)  m_statusTgt->setPlainText("TGT: " + m_tgtType);
    if (m_statusZoom) m_statusZoom->setPlainText(
        QString("ZOOM: %1x  BRT: %2  FOV: %3°")
            .arg(m_zoom, 0, 'f', 1).arg(m_brt).arg(m_fov));
    if (m_statusConf) m_statusConf->setPlainText(QString("CONFIDENCE: %1%").arg(m_conf));

    // // Bottom-right STATE
    // if (m_stateLabel) {
    //     m_stateLabel->setPlainText("STATE: " + m_state);
    //     QColor sc = (m_state == "OFFLINE")  ? QColor("#cc3300")
    //                 : (m_state == "STANDBY") ? GN
    //                 : (m_state == "READY")   ? GOLD
    //                                          : QColor("#ff2200");
    //     m_stateLabel->setDefaultTextColor(sc);
    //     QRectF br = m_stateLabel->boundingRect();
    //     m_stateLabel->setPos(m_sceneW - br.width() - 10, m_sceneH - br.height() - 6);
    //     if (m_stateBg)
    //         m_stateBg->setRect(m_sceneW - br.width() - 14, m_sceneH - br.height() - 10,
    //                            br.width() + 8, br.height() + 8);
    // }

    // Health bar
    // if (m_healthBarFg && m_healthBarBg) {
    //     QRectF bg = m_healthBarBg->rect();
    //     m_healthBarFg->setRect(bg.x(), bg.y(), bg.width() * m_health / 100.0, bg.height());
    // }
    // if (m_healthLabel)
    //     m_healthLabel->setPlainText(QString("HEALTH: %1%").arg(m_health));
}

void CameraScene::updateTargetPosition()
{
    if (!m_tgtBracketOuter) return;                  
    double tx = m_az  * m_sceneW;                                //  m_az = 0.5;  m_el = 0.5;(default normalized value) m_sceneW = 1040; m_sceneH = 540;
    double ty = (1.0 - m_el) * m_sceneH;                        // top-left coordinate system starts with origin(0,0)
    m_tgtBracketOuter->setPos(tx - 19, ty - 19);               // Position the outer target bracket so that it is centered at the target coordinates. if the inner bracket is 18 by 18: Half width  = 18 divided by 2 = 9 Half height = 18 divided by 2 = 9
    m_tgtBracketInner->setPos(tx - 9,  ty - 9);               // Position the inner target bracket so that it is centered at the target coordinates
    if (m_tgtLabel) m_tgtLabel->setPos(tx - 19, ty - 34);    // for showing the target label(eg.drone)
}

//  Public setters
void CameraScene::setAzEl(double az, double el)
{
    m_azDeg = az;
    m_elDeg = el;
    // Also update normalised position for target bracket (centre at 0.5)
    m_az = (az / 360.0);               // 0..1
    m_el = (el + 90.0) / 180.0;        // 0..1  (0=down, 1=up)
    updateHUD();
    updateTargetPosition();
}


// Set target position and label on the camera scene.
// azNorm and elNorm are normalized coordinates in the range 0 to 1.
void CameraScene::setTargetBox(double azNorm, double elNorm, const QString &label)
{
    // Store normalized target azimuth and elevation.
    m_az = azNorm;
    m_el = elNorm;

    // Update the target type/name displayed on the target box.
    if (m_tgtLabel)
        m_tgtLabel->setPlainText(label);

    // Recalculate and move the target box according to the new position.
    updateTargetPosition();
}


// Enable or disable Thermal Imaging mode.
// Stores the current thermal mode state and refreshes the HUD
// so that the TI status display shows ON or OFF.
void CameraScene::setThermalMode(bool on)
{
    // Store the thermal imaging mode state.
    m_thermal = on;

    // Refresh the HUD to reflect the updated thermal mode.
    updateHUD();
}


void CameraScene::setZoom(double z)
{
    m_zoom = qBound(1.0, z, 8.0);

    updateHUD();

    if (!m_lastFrame.isNull())
        updateFrame(m_lastFrame);
}

void CameraScene::setBrightness(int b)     { m_brt  = qBound(0, b, 100);   updateHUD(); }
void CameraScene::setFOV(int fov)          { m_fov  = qBound(5, fov, 60);  updateHUD(); }
void CameraScene::setConfidence(int pct)   { m_conf = qBound(0, pct, 100); updateHUD(); }
void CameraScene::setLaserRange(int m)     { m_lr   = m;                   updateHUD(); }
void CameraScene::setEstimRange(int m)     { m_er   = m;                   updateHUD(); }
void CameraScene::setState(const QString &s){ m_state = s;                  updateHUD(); }

void CameraScene::setTargetType(const QString &t)
{
    m_tgtType = t;
    if (m_tgtLabel) m_tgtLabel->setPlainText(t);
    updateHUD();
}
void CameraScene::setHealth(int pct) { m_health = qBound(0, pct, 100); updateHUD(); }

void CameraScene::setBoundingBoxSize(int w, int h)
{
    m_bboxW = qMax(4, w);               // returns the maximum for qMax
    m_bboxH = qMax(4, h);
    repositionItems();
}

void CameraScene::setBoundingBoxVisible(bool visible)
{
    if (m_boundingBox) m_boundingBox->setVisible(visible);
    if (m_bboxLabel)   m_bboxLabel->setVisible(visible);
}

void CameraScene::setBoundingBoxLabel(const QString &text)
{
    if (m_bboxLabel) m_bboxLabel->setPlainText(text);
}


double CameraScene::zoom() const
{
    return m_zoom;                 // Allows the mainwindow to ask the camerascene for the current zoom value.
}

//  MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_screenRecorder = new ScreenRecorder(this);
    connect(ui->pbRecord,
            &QPushButton::clicked,
            this,
            &MainWindow::onRecordButtonClicked);

    timer = new QTimer(this);         // In constructor we have taken the timer and initialized it with QTimer object and then we are going to give parent this.
    connect(timer,SIGNAL(timeout()),this,SLOT(myfunction()));  //defined the connect function which is taking 4 arguments.
    timer->start(1000);

    // Zoom controls
        auto *zoomInShortcut =
        new QShortcut(QKeySequence(Qt::Key_Up), this);

    connect(zoomInShortcut, &QShortcut::activated,
            this, &MainWindow::onZoomIn);

    auto *zoomOutShortcut =
        new QShortcut(QKeySequence(Qt::Key_Down), this);

    connect(zoomOutShortcut, &QShortcut::activated,
            this, &MainWindow::onZoomOut);

    auto *zoomResetShortcut =
        new QShortcut(QKeySequence("Ctrl+Z"), this);

    connect(zoomResetShortcut, &QShortcut::activated,
            this, &MainWindow::onZoomReset);


    // Brightness controls
    auto *brightnessUpShortcut =
        new QShortcut(QKeySequence("Ctrl+B"), this);

    connect(brightnessUpShortcut, &QShortcut::activated,
            this, &MainWindow::onBrightnessUp);

    auto *brightnessDownShortcut =
        new QShortcut(QKeySequence(Qt::Key_Minus), this);

    connect(brightnessDownShortcut, &QShortcut::activated,
            this, &MainWindow::onBrightnessDown);


    // FOV control
    auto *fovUpShortcut =
        new QShortcut(QKeySequence("Ctrl+F"), this);

    connect(fovUpShortcut, &QShortcut::activated,
            this, &MainWindow::onFovUp);



    // 1. Load the image from your resource file prefix path
    QPixmap pixmap_leftImage(":/icon/leftImage_SLMS_NoBg.png");

    // 2. Set the image onto your existing UI label
    ui->leftImageLabel->setPixmap(pixmap_leftImage);

    // 3. Force the image to scale nicely to fit the label's dimensions
    ui->leftImageLabel->setScaledContents(true);


    // 1. Load the image from your resource file prefix path
    QPixmap pixmap_rightImage(":/icon/Flipped_SLMS_RightImage.png");

    // 2. Set the image onto your existing UI label
    ui->rightImageLabel->setPixmap(pixmap_rightImage);

    // 3. Force the image to scale nicely to fit the label's dimensions
    ui->rightImageLabel->setScaledContents(true);

    ui->stackedWidget->setCurrentIndex(0);
    // setWindowTitle("MISSILE LAUNCHER CONTROL SYSTEM  v1.0");

    // Connects the nested combobox directly to your status bar feedback
    connect(ui->MissileSelectionCombo, &QComboBox::currentTextChanged, this, [this](const QString &text) {
        this->statusBar()->showMessage("Missile no. selected: " + text);
    });


    setStyleSheet(R"(
        QMainWindow, QWidget#centralWidget { background-color: #0a120a; }

        QGroupBox {
            color: #33ff33;
            border: 1.25px solid #1a5a1a;
            border-radius: 3px;
            margin-top: 18px;
            font-family: 'Consolas';
            font-size: 15px;
            font-weight: 700;
        }
        QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 2px 6px; }

        QLabel {
            color: #33ff33;
            font-family: 'Consolas';
            font-size: 15px;
            background: transparent;
        }
        QLabel#titleLabel {
            background-color: #051505;
            color: #66ff66;
            font-family: 'Consolas';
            font-size: 15px;
            font-weight: 700;
            padding: 6px;
            border: 1px solid #1a5a1a;
            border-radius: 3px;
        }

QPushButton
{
    color: rgb(34, 204, 34);

    font-family: "Consolas";
    font-size: 12px;
    font-weight: bold;

    padding: 10px;
    min-width: 40px;
    min-height: 40px;

    background: transparent;
    border: none;
}

/* Hover */
QPushButton:hover
{
    color: rgb(34, 220, 34);
}

/* Pressed */
QPushButton:pressed
{
    color: rgb(255,255,255);
}

/* Checked */
QPushButton:checked
{
    color: rgb(255,255,255);
}

/* Disabled */
QPushButton:disabled
{
    color: rgb(120,120,120);
}

/* ---------------- Engage Button ---------------- */

QPushButton#engageBtn
{
    color: rgb(255,214,51);
}

QPushButton#engageBtn:hover
{
    color: rgb(255,240,120);
}

/* ---------------- Fire Button ---------------- */

QPushButton#fireBtn
{
    color: rgb(255,60,60);
}

QPushButton#fireBtn:hover
{
    color: rgb(255,120,120);
}

/* ---------------- Tooltip ---------------- */

QToolTip
{
    background-color: rgb(30,30,30);
    color: white;

    border: 1px solid rgb(76,175,80);
    border-radius: 4px;

    padding: 6px;

    font-family: "Segoe UI";
    font-size: 13px;
    font-weight: bold;
}

        QComboBox {
            color: #33ff33;
            background-color: #800A120A;
            border: 1px solid #1a5a1a;
            font-family: 'Consolas';
            font-size: 15px;
            padding: 4px 8px;
            min-height: 30px;
        }
        QComboBox QAbstractItemView {
            color: #33ff33;
            background-color: #0a200a;
            selection-background-color: #123d12;
        }

        QStatusBar {
            background-color: #051505;
            color: #33ff33;
            font-family: 'Consolas';
            font-size: 15px;
        }
        QFrame#bottomBar { background-color: #051505; border-top: 1px solid #1a5a1a; }
    )");

    // Node status labels
    ui->node1StatusLabel->setStyleSheet("color: #cc0000;");
    ui->node2StatusLabel->setStyleSheet("color: #cc0000;");

    // Widget labels
    ui->missileWidget->setLabel("MISSILE");
    ui->targetWidget->setLabel("TARGET");

    // Set initial target type to match combo default (first item = DRONE)
    ui->targetWidget->setTargetTypeByName(ui->targetTypeCombo->currentText());

    // Build CameraScene and attach to view
    m_scene = new CameraScene(this);
    ui->cameraView->setScene(m_scene);
    ui->cameraView->setRenderHint(QPainter::Antialiasing);
    ui->cameraView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->cameraView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->cameraView->setFrameShape(QFrame::NoFrame);
    ui->cameraView->setBackgroundBrush(QBrush(BG));
    ui->cameraView->fitInView(m_scene->sceneRect(), Qt::IgnoreAspectRatio);
    ui->cameraView->viewport()->installEventFilter(this);

    // Camera
    const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
    if (!cameras.isEmpty()) {
        m_camera         = new QCamera(cameras.first(), this);
        m_captureSession = new QMediaCaptureSession(this);
        m_videoSink      = new QVideoSink(this);
        m_captureSession->setCamera(m_camera);
        m_captureSession->setVideoSink(m_videoSink);
        connect(m_videoSink, &QVideoSink::videoFrameChanged,
                this, &MainWindow::onNewVideoFrame);
        m_camera->start();
    }

    // TCP sockets
    node1Socket = new QTcpSocket(this);
    connect(node1Socket, &QTcpSocket::connected,    this, &MainWindow::node1Connected);
    connect(node1Socket, &QTcpSocket::disconnected, this, &MainWindow::node1Disconnected);
    connect(node1Socket, &QTcpSocket::readyRead,    this, &MainWindow::node1DataReceived);

    node2Socket = new QTcpSocket(this);
    connect(node2Socket, &QTcpSocket::connected,    this, &MainWindow::node2Connected);
    connect(node2Socket, &QTcpSocket::disconnected, this, &MainWindow::node2Disconnected);
    connect(node2Socket, &QTcpSocket::readyRead,    this, &MainWindow::node2DataReceived);

    connectToNode1();
    connectToNode2();

    reconnectTimer = new QTimer(this);
    reconnectTimer->setInterval(3000);
    connect(reconnectTimer, &QTimer::timeout, this, &MainWindow::tryReconnect);
    reconnectTimer->start();

    // Button wiring
    connect(ui->PB_MissileEngage, &QPushButton::clicked, this, &MainWindow::on_PB_MissileEngage_clicked);
    connect(ui->PB_Fire,          &QPushButton::clicked, this, &MainWindow::on_PB_Fire_clicked);

    // Target type combo — update both the scene HUD and the target widget silhouette
    connect(ui->targetTypeCombo, &QComboBox::currentTextChanged,
            this, [this](const QString &t){
                m_scene->setTargetType(t);
                ui->targetWidget->setTargetTypeByName(t);
            });

    statusBar()->showMessage("Connecting to Node1 (port 5001) and Node2 (port 5002)...");
    setFocusPolicy(Qt::StrongFocus);
    setFocus();


    ui->PB_Home->setToolTip("Home");
    ui->PB_DayCamera->setToolTip("Day Camera");
    ui->PB_NUC->setToolTip("Thermal Camera NUC");
    ui->PB_LRF->setToolTip("Laser Range Finder");
    ui->PB_Focus->setToolTip("Focus");
    ui->PB_Plus->setToolTip("Zoom In");
    ui->PB_Minus->setToolTip("Zoom Out");
    ui->PB_RequestRelease->setToolTip("Request");
    ui->PB_MissileSelection->setToolTip("Missile Selection");
    ui->PB_MissileEngage->setToolTip("Missile Engage");
    ui->PB_EngageLauncher->setToolTip("Engage Launcher");
    ui->PB_Fire->setToolTip("Firing Mode");
    ui->PB_Polarity->setToolTip("Polarity");
    ui->PB_ExposureGain->setToolTip("Exposure");
    ui->PB_Fire->setToolTip("Fire");
    ui->PB_Zoom->setToolTip("Zoom");

    // Added by me for zoom functionality.
    m_zoomTimer = new QTimer(this);

    connect(m_zoomTimer, &QTimer::timeout,
            this, [this]()
            {
                if (!m_scene)
                    return;

                double z = m_scene->zoom();

                z += (m_zoomDirection * 0.1);

                m_scene->setZoom(z);
            });
    connect(ui->PB_Plus, &QPushButton::pressed,
            this, [this]()
            {
                if (!m_zoomMode)
                    return;

                m_zoomDirection = 1;
                m_zoomTimer->start(50);
            });

    connect(ui->PB_Plus, &QPushButton::released,
            this, [this]()
            {
                m_zoomTimer->stop();
            });



    connect(ui->PB_Minus, &QPushButton::pressed,
            this, [this]()
            {
                if (!m_zoomMode)
                    return;

                m_zoomDirection = -1;
                m_zoomTimer->start(50);
            });

    connect(ui->PB_Minus, &QPushButton::released,
            this, [this]()
            {
                m_zoomTimer->stop();
            });


    connect(m_screenRecorder,
            &ScreenRecorder::recordingStarted,
            this,
            &MainWindow::onRecordingStarted);

    connect(m_screenRecorder,
            &ScreenRecorder::recordingStopped,
            this,
            &MainWindow::onRecordingStopped);

    connect(m_screenRecorder,
            &ScreenRecorder::recordingError,
            this,
            &MainWindow::onRecordingError);

}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::resizeEvent(QResizeEvent *ev)
{
    QMainWindow::resizeEvent(ev);
    syncSceneToView();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == ui->cameraView->viewport() && ev->type() == QEvent::Resize)
        syncSceneToView();
    return QMainWindow::eventFilter(obj, ev);
}

void MainWindow::syncSceneToView()
{
    if (!m_scene || !ui->cameraView) return;
    const QSize vp = ui->cameraView->viewport()->size();        // The viewport is the actual internal area through which the scene is visible.  Width  = 1040;     Height = 540;
    if (vp.isEmpty()) return;
    m_scene->resizeOverlay(vp.width(), vp.height());
    ui->cameraView->fitInView(m_scene->sceneRect(), Qt::IgnoreAspectRatio);
}

void MainWindow::onNewVideoFrame(const QVideoFrame &frame)
{
    QImage img = frame.toImage();
    if (!img.isNull()) m_scene->updateFrame(img);
}

//  Control actions
void MainWindow::onZoomIn()        { m_zoom = qBound(0.5, m_zoom+0.5, 8.0); m_scene->setZoom(m_zoom); }
void MainWindow::onZoomOut()       { m_zoom = qBound(0.5, m_zoom-0.5, 8.0); m_scene->setZoom(m_zoom); }
void MainWindow::onZoomReset()     { m_zoom = 1.0;                           m_scene->setZoom(m_zoom); }
void MainWindow::onBrightnessUp()  { m_brt  = qBound(0, m_brt+5, 100);      m_scene->setBrightness(m_brt); }
void MainWindow::onBrightnessDown(){ m_brt  = qBound(0, m_brt-5, 100);      m_scene->setBrightness(m_brt); }
void MainWindow::onFovUp()         { m_fov  = qBound(5, m_fov+5, 60);       m_scene->setFOV(m_fov); }
void MainWindow::onFovDown()       { m_fov  = qBound(5, m_fov-5, 60);       m_scene->setFOV(m_fov); }
// void MainWindow::onToggleThermal() { m_thermal = !m_thermal;                 m_scene->setThermalMode(m_thermal); }
void MainWindow::onEngageClicked() { m_sysState = "READY"; m_scene->setState(m_sysState); statusBar()->showMessage("ENGAGE command sent."); }
void MainWindow::onFireClicked()   { m_sysState = "FIRE";  m_scene->setState(m_sysState); statusBar()->showMessage("FIRE command sent."); }

//  TCP helpers
void MainWindow::connectToNode1() { node1Buffer.clear(); node1Socket->connectToHost("127.0.0.1", 5001); }
void MainWindow::connectToNode2() { node2Buffer.clear(); node2Socket->connectToHost("127.0.0.1", 5002); }

void MainWindow::tryReconnect()
{
    if (node1Socket->state() == QAbstractSocket::UnconnectedState) connectToNode1();
    if (node2Socket->state() == QAbstractSocket::UnconnectedState) connectToNode2();
}

//  Node1 slots
void MainWindow::node1Connected()
{
    ui->node1StatusLabel->setText("● N1:ON");
    ui->node1StatusLabel->setStyleSheet("color: #22cc22;");
    statusBar()->showMessage("Node1 connected.");
}

void MainWindow::node1Disconnected()
{
    ui->node1StatusLabel->setText("● N1:OFF");
    ui->node1StatusLabel->setStyleSheet("color: #cc0000;");
    ui->targetWidget->setState(0);
    m_sysState = "OFFLINE";
    m_scene->setState(m_sysState);
}

void MainWindow::node1DataReceived()
{
    node1Buffer += QString::fromUtf8(node1Socket->readAll());
    while (node1Buffer.contains('\n')) {
        int p = node1Buffer.indexOf('\n');
        QString line = node1Buffer.left(p).trimmed();       // Returns a string that has whitespace removed from the start and the end.
        node1Buffer  = node1Buffer.mid(p + 1);
        if (!line.isEmpty()) processNode1Line(line);
    }
}

//  Node2 slots
void MainWindow::node2Connected()
{
    ui->node2StatusLabel->setText("● N2:ON");
    ui->node2StatusLabel->setStyleSheet("color: #22cc22;");
    statusBar()->showMessage("Node2 connected.");
}

void MainWindow::node2Disconnected()
{
    ui->node2StatusLabel->setText("● N2:OFF");
    ui->node2StatusLabel->setStyleSheet("color: #cc0000;");
    ui->azimuthWidget->setAzimuth(0);
    ui->elevationWidget->setElevation(0);
    ui->missileWidget->setState(0);
    m_scene->setState("OFFLINE");
}

void MainWindow::node2DataReceived()
{
    node2Buffer += QString::fromUtf8(node2Socket->readAll());
    while (node2Buffer.contains('\n')) {
        int p = node2Buffer.indexOf('\n');
        QString line = node2Buffer.left(p).trimmed();
        node2Buffer  = node2Buffer.mid(p + 1);
        if (!line.isEmpty()) processNode2Line(line);
    }
}

void MainWindow::processNode1Line(const QString &line)
{
    // Format: KEY=VALUE  (one key per line from Node1)
    QStringList parts = line.split("=");
    if (parts.size() != 2) return;
    QString key = parts[0].trimmed();
    QString val = parts[1].trimmed();


    if (key == "STATE") {
        int idx = stateTextToIndex(val);
        ui->missileWidget->setState(idx);
        m_scene->setState(val);
        m_scene->setHealth(idx * 33);
    }
    else if (key == "CONF") {
        m_scene->setConfidence(val.toInt());
    }
    else if (key == "LR") {
        m_scene->setLaserRange(val.toInt());
    }
    else if (key == "ER") {
        m_scene->setEstimRange(val.toInt());
    }
}
void MainWindow::processNode2Line(const QString &line)
{
    // Format: AZ=nnn,EL=nnn,STATE=xxx,BAT=nnn,HEALTH=nnn,TI=0/1
    QStringList pairs = line.split(",");
    int az = 0, el = 0, health = 0;
    bool tiActive = false;
    QString state = "OFF";

    for (const QString &pair : pairs) {
        QStringList kv = pair.split("=");
        if (kv.size() != 2) continue;
        QString k = kv[0].trimmed();
        QString v = kv[1].trimmed();
        if      (k == "AZ")     az       = v.toInt();
        else if (k == "EL")     el       = v.toInt();
        else if (k == "STATE")  state    = v;
        else if (k == "HEALTH") health   = v.toInt();
        else if (k == "TI")     tiActive = (v.toInt() != 0);
    }

    // Update widgets
    ui->azimuthWidget->setAzimuth(az);
    ui->elevationWidget->setElevation(el);
    ui->targetWidget->setState(stateTextToIndex(state));

    // Rotate target silhouette with azimuth (drone/heli/aircraft all rotate)
    ui->targetWidget->setRotation(az);

    // Update scene: raw degrees for HUD, normalised for bracket
    m_scene->setAzEl((double)az, (double)el);


    // Convert azimuth from 0 to 360 degrees into normalized 0 to 1 range.
    // Convert elevation from -90 to +90 degrees into normalized 0 to 1 range.
    // Pass the currently selected target type to the camera scene.
    m_scene->setTargetBox(
        az / 360.0,
        (el + 40.0) / 80.0,
        ui->targetTypeCombo->currentText()
        );

    m_scene->setThermalMode(tiActive);
    m_scene->setHealth(health);
}


int MainWindow::stateTextToIndex(const QString &s)
{
    if (s == "STANDBY") return 1;
    if (s == "READY")   return 2;
    if (s == "FIRE")    return 3;
    return 0;
}

//  Button slots
// void MainWindow::on_PB_Day_Thermal_clicked()  { onToggleThermal(); statusBar()->showMessage("Day/Thermal toggled"); }
void MainWindow::on_PB_LRF_clicked()          { statusBar()->showMessage("LRF button clicked"); }
void MainWindow::on_PB_Polarity_clicked()     { statusBar()->showMessage("Polarity button clicked"); }
void MainWindow::on_PB_NUC_clicked()          { statusBar()->showMessage("NUC button clicked"); }
void MainWindow::on_PB_Home_clicked()         { statusBar()->showMessage("Home button clicked"); }

void MainWindow::on_PB_Zoom_clicked()
{
    m_zoomMode = !m_zoomMode;

    statusBar()->showMessage(
        m_zoomMode ?
            "Zoom Mode Enabled" :
            "Zoom Mode Disabled");
}
void MainWindow::on_PB_Fire_clicked()         { onFireClicked(); }
void MainWindow::on_PB_Plus_clicked()         { onZoomIn(); statusBar()->showMessage("Zoom +"); }
void MainWindow::on_PB_Minus_clicked()        { onZoomOut(); statusBar()->showMessage("Zoom -"); }
void MainWindow::on_PB_RequestRelease_clicked(){ statusBar()->showMessage("Request/Release clicked"); }
void MainWindow::on_PB_EngageLauncher_clicked(){ onEngageClicked(); }
void MainWindow::on_PB_MissileSelection_clicked(){ statusBar()->showMessage("Missile Selection clicked"); }
void MainWindow::on_PB_MissileEngage_clicked() { onEngageClicked(); }
void MainWindow::on_PB_Focus_clicked()         { statusBar()->showMessage("Focus clicked"); }
void MainWindow::on_PB_ExposureGain_clicked()  { statusBar()->showMessage("Exposure/Gain clicked"); }


void MainWindow::on_PB_DayCamera_clicked()
{
    // Toggle the camera state
    isNightMode = !isNightMode;

    if (isNightMode)
    {
        // Switch to Night Mode
        ui->PB_DayCamera->setIcon(QIcon(":/icon/Night_moon_purewhite.svg"));
        statusBar()->showMessage("Night Camera Mode selected");
    }
    else
    {
        // Switch to Day Mode
        ui->PB_DayCamera->setIcon(QIcon(":/icon/Day_cam_svg.svg"));
        statusBar()->showMessage("Day Camera Mode Selected");
    }
}

void MainWindow::zoomCommand(quint8 value)
{
    switch (value)
    {
    case ZOOM_IN:
        qDebug() << "Zoom In Command";
        break;

    case ZOOM_OUT:
        qDebug() << "Zoom Out Command";
        break;

    case ZOOM_STOP:
        qDebug() << "Zoom Stop Command";
        break;
    }
}

void CameraScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Direct scene position coordinates (no mapping function needed!)
        QPointF scenePos = event->scenePos();

        QString text = QString("X: %1, Y: %2").arg(scenePos.x(), 0, 'f', 0)
                           .arg(scenePos.y(), 0, 'f', 0);

        if (!m_clickLabel) {
            // "this->" points directly to the active CameraScene instance
            m_clickLabel = addText(text, hudFont(10));
            m_clickLabel->setDefaultTextColor(GN);
            m_clickLabel->setZValue(9);
        } else {
            m_clickLabel->setPlainText(text);
        }

        m_clickLabel->setPos(scenePos.x() + 10, scenePos.y() + 10); //
    }

    // Call the base class implementation so standard click actions remain unbroken
    QGraphicsScene::mousePressEvent(event);
}


// For the login page.
void MainWindow::on_PB_login_clicked()
{
    QString username = ui->LE_Username->text();
    QString password = ui->LE_Password->text();


    //  Validation checks for password for minimum number charracters we want
    if(password.length() < 8) {
        QMessageBox::warning(this, "Invalid Password",
                             "Password must be at least 8 characters long.");
        return;
    }

    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSymbol = false;

    for (QChar c : password) {
        if (c.isUpper())          hasUpper = true;
        else if (c.isLower())     hasLower = true;
        else if (c.isDigit())     hasDigit = true;
        else                      hasSymbol = true;  // Any non-alphanumeric char
    }

    if (!hasUpper) {
        QMessageBox::warning(this, "Invalid Password",
                             "Password must contain at least one uppercase letter.");
        return;
    }
    if (!hasLower) {
        QMessageBox::warning(this, "Invalid Password",
                             "Password must contain at least one lowercase letter.");
        return;
    }
    if (!hasDigit) {
        QMessageBox::warning(this, "Invalid Password",
                             "Password must contain at least one number.");
        return;
    }
    if (!hasSymbol) {
        QMessageBox::warning(this, "Invalid Password",
                             "Password must contain at least one special symbol (e.g. @, #, !, %, $).");
        return;
    }

    //  Actual login credential check
    if (username == "test" && password == "Pass@123") {
        // QMessageBox::information(this, "Login", "Login Successful.");
        ui->stackedWidget->setCurrentIndex(1);
    }
    else {
        QMessageBox::warning(this, "Login", "Incorrect username or password.");
    }
}



void MainWindow::on_PB_Cancel_clicked()
{
    // qApp->quit();
    this->close();
}

void MainWindow::on_PB_View_clicked()
{
    if (ui->LE_Password->echoMode() == QLineEdit::Password)
    {
        ui->LE_Password->setEchoMode(QLineEdit::Normal);
        ui->PB_View->setIcon(QIcon(":/icon/openeye_green.svg"));
    }
    else
    {
        ui->LE_Password->setEchoMode(QLineEdit::Password);
        ui->PB_View->setIcon(QIcon(":/icon/CloseEye_Green.svg"));
    }
}


void MainWindow::on_PB_LogOut_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_PB_pageMaintenance_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}



void MainWindow::on_PB_pageStatusPanel_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_PB_PreviousPage_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_PB_Logout_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_PB_PreviousPage_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_PB_Logout_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}



//This function is used to update time on the label
void MainWindow::myfunction()
{
    // qDebug() <<"Update..";        // myfunction is called in every 2 seconds in the application output section.
    // QTime time = QTime::currentTime();
    QTime time = QTime::currentTime();   // we can use the Qtime which will return the currectTime using the static function. Take a label in the mainwindow.ui
    //    page and keep it empty to print the label as per our convinienance and also in property rename it label_date_time.

    QString time_text = time.toString("hh: mm: ss AP");    // Converting the QTime in string format and formatting it also with our convinienance.

    // if(time.second() % 2 == 0){   // to make the colon disappeared after every even number of seconds.
    //     time_text[3] = ' ';
    //     time_text[8] = ' ';
    // }


    QDate date = QDate::currentDate();
    QString date_text = date.toString("dd-MM-yyyy");

    // QString date_text = date.toString("dddd, dd MMMM yyyy");

    QString final_text = time_text + "| " + date_text;
    ui->L_DateTime->setText(final_text);

    // ui->label_date_time->setText(time_text);   // Setting up our string to the label to print it.
}

void MainWindow::onRecordButtonClicked()
{
    if (!m_screenRecorder)
        return;

    if (!m_screenRecorder->isRecording())
    {
        if (m_screenRecorder->startRecording())
        {
            ui->pbRecord->setText("STOP");
        }
    }
    else
    {
        m_screenRecorder->stopRecording();
    }
}

void MainWindow::onRecordingStarted()
{
    ui->pbRecord->setText("STOP");

    qDebug() << "Screen recording started.";
}

void MainWindow::onRecordingStopped(
    const QString &filePath)
{
    ui->pbRecord->setText("REC");

    qDebug() << "Screen recording saved at:"
             << filePath;
}

void MainWindow::onRecordingError(
    const QString &errorMessage)
{
    ui->pbRecord->setText("REC");

    QMessageBox::critical(
        this,
        "Screen Recording Error",
        errorMessage);
}

