#include "missilewidget.h"
#include <QPainter>
#include <QPolygonF>

MissileWidget::MissileWidget(QWidget *parent)
    : QWidget(parent)
    , currentState(Power_ON)
    , label("MISSILE")
    , blinkVisible(true)
{
    setMinimumSize(100, 160);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    blinkTimer = new QTimer(this);
    blinkTimer->setInterval(500);
    connect(blinkTimer, &QTimer::timeout, this, &MissileWidget::onBlinkTimer);

    // Constructor default is Power_ON, so start the timer immediately.
    // setState() has an early-return guard (same-state check), so if
    // MainWindow calls setState(Power_ON) at startup it returns without
    // starting the timer — this line covers that gap.
    blinkTimer->start();
}

QSize MissileWidget::sizeHint() const
{
    return QSize(110, 170);
}

void MissileWidget::setLabel(const QString &text)
{
    label = text;
    update();
}

void MissileWidget::setState(int index)
{
    State newState = static_cast<State>(index);

    // CRITICAL: Keep the same-state early-return guard.
    // Node2 broadcasts every 200 ms. Without this guard, every incoming
    // packet resets blinkVisible=true and restarts the timer, so the
    // missile is stuck permanently in the bright phase and never blinks.
    if (currentState == newState)
        return;

    currentState = newState;

    if (currentState == Power_ON)
    {
        blinkVisible = true;   // start from the bright (white) phase
        blinkTimer->start();   // start fresh — interval already set
    }
    else
    {
        blinkTimer->stop();
        blinkVisible = true;   // non-blinking states always paint fully
    }

    update();
}

void MissileWidget::onBlinkTimer()
{
    blinkVisible = !blinkVisible;
    update();
}

void MissileWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // width=100 and height=165
    int W  = width();
    int H  = height();
    int cx = W / 2;

    QColor bodyColor, outlineColor, stateColor, stateTextColor;
    QString stateText;

    if (currentState == OFF)
    {
        bodyColor      = QColor("#ffffff");
        outlineColor   = QColor("#cccccc");
        stateColor     = QColor("#aaaaaa");
        stateTextColor = QColor("#555555");
        stateText      = "OFF";
    }
    else if (currentState == Power_ON)
    {
        stateText = "Power_ON";

        if (blinkVisible)
        {
            // Bright phase — full white missile
            bodyColor      = QColor("#ffffff");
            outlineColor   = QColor("#999999");
            stateColor     = QColor("#aaaaaa");
            stateTextColor = QColor("#ffffff");
        }
        else
        {
            // Dark phase — near-black so the blink contrast is obvious
            bodyColor      = QColor("#111111");
            outlineColor   = QColor("#444444");
            stateColor     = QColor("#222222");
            stateTextColor = QColor("#888888");
        }
    }
    else if (currentState == Health_Checks)
    {
        bodyColor      = QColor("#3a2d00");
        outlineColor   = QColor("#ffff00");
        stateColor     = QColor("#ffff00");
        stateTextColor = QColor("#ffff00");
        stateText      = "Health_Checks";
    }
    else if (currentState == HealthGood)
    {
        bodyColor      = QColor("#0a280a");
        outlineColor   = QColor("#22cc22");
        stateColor     = QColor("#22cc22");
        stateTextColor = QColor("#22cc22");
        stateText      = "HealthGood";
    }
    else if (currentState == HealthNotGood)
    {
        bodyColor      = QColor("#3a0000");
        outlineColor   = QColor("#ff0000");
        stateColor     = QColor("#ff0000");
        stateTextColor = QColor("#ff0000");
        stateText      = "HealthNotGood";
    }
    else  // TrackingMode
    {
        bodyColor      = QColor("#001a3a");
        outlineColor   = QColor("#0088ff");
        stateColor     = QColor("#0088ff");
        stateTextColor = QColor("#0088ff");
        stateText      = "TrackingMode";
    }

    // Background
    painter.fillRect(rect(), QColor("#800A120A"));

    // Missile dimensions
    int topPad   = 18;
    int botPad   = 18;
    int drawH    = H - topPad - botPad;         // drawing area for the missile dimension. (165-18-18 = 129)
    int noseH    = drawH * 0.25;                // 129*0.25 = 32.25
    int bodyTop  = topPad + noseH;
    int bodyBot  = topPad + drawH * 0.72;
    int bodyW    = 12;
    int finSpan  = 18;
    int finTop   = bodyBot - noseH * 0.6;
    int nozzleBot = topPad + drawH * 0.88;
    int launchTop = nozzleBot + 2;
    int launchBot = H - botPad - 2;
    int launchW   = 20;

    painter.setPen(QPen(outlineColor, 1.0));
    painter.setBrush(bodyColor);

    // Nose cone
    QPolygonF nose;
    nose << QPointF(cx, topPad)
         << QPointF(cx + bodyW, bodyTop)
         << QPointF(cx - bodyW, bodyTop);
    painter.drawPolygon(nose);

    // Missile body
    painter.drawRect(QRect(cx - bodyW, bodyTop, bodyW * 2, bodyBot - bodyTop));

    // Left fin
    QPolygonF leftFin;
    leftFin << QPointF(cx - bodyW, finTop)
            << QPointF(cx - finSpan, bodyBot)
            << QPointF(cx - bodyW, bodyBot);
    painter.drawPolygon(leftFin);

    // Right fin
    QPolygonF rightFin;
    rightFin << QPointF(cx + bodyW, finTop)
             << QPointF(cx + finSpan, bodyBot)
             << QPointF(cx + bodyW, bodyBot);
    painter.drawPolygon(rightFin);

    // Nozzle
    QPolygonF nozzle;
    nozzle << QPointF(cx - bodyW,       bodyBot)
           << QPointF(cx + bodyW,       bodyBot)
           << QPointF(cx + bodyW * 0.5, nozzleBot)
           << QPointF(cx - bodyW * 0.5, nozzleBot);
    painter.setBrush(bodyColor.darker(150));
    painter.drawPolygon(nozzle);

    // Launcher base
    painter.setPen(QPen(outlineColor, 0.8));
    painter.setBrush(stateColor);
    QPolygonF launcher;
    launcher << QPointF(cx - launchW * 0.6, launchTop)
             << QPointF(cx + launchW * 0.6, launchTop)
             << QPointF(cx + launchW,       launchBot)
             << QPointF(cx - launchW,       launchBot);
    painter.drawPolygon(launcher);

    // Ground line
    painter.setPen(QPen(outlineColor, 1.0));
    painter.drawLine(cx - launchW - 4, launchBot, cx + launchW + 4, launchBot);

    // State dot (top-right corner)
    painter.setPen(Qt::NoPen);
    painter.setBrush(stateColor);
    painter.drawEllipse(QPoint(W - 10, 10), 5, 5);

    // Label at top
    painter.setPen(QColor("#22cc22"));
    painter.setFont(QFont("Consolas", 13, QFont::Bold));
    painter.drawText(QRect(0, 0, W - 18, topPad), Qt::AlignCenter, label);

    // State text at bottom — always readable regardless of blink phase
    painter.setPen(stateTextColor);
    painter.setFont(QFont("Consolas", 10, QFont::Bold));
    painter.drawText(QRect(0, H - botPad, W, botPad), Qt::AlignCenter, stateText);
}
