#include "targetwidget.h"
#include <QPainter>
#include <QPolygonF>
#include <QPainterPath>
#include <QtMath>

TargetWidget::TargetWidget(QWidget *parent)
    : QWidget(parent)
    , m_state(STANDBY)
    , m_type(DRONE)
    , m_label("TARGET")
    , m_rotation(0)
    , m_blinkVisible(true)
{
    setMinimumSize(100, 160);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    m_blinkTimer = new QTimer(this);
    m_blinkTimer->setInterval(400);
    connect(m_blinkTimer, &QTimer::timeout, this, &TargetWidget::onBlinkTimer);
}

QSize TargetWidget::sizeHint() const { return QSize(110, 170); }

void TargetWidget::setLabel(const QString &text) { m_label = text; update(); }

void TargetWidget::setState(int index)
{
    m_state = static_cast<State>(index);
    m_blinkVisible = true;
    if (m_state == FIRE) m_blinkTimer->start();
    else                 m_blinkTimer->stop();
    update();
}

//  Rotating the target type by the Azimuth received from the launcher.
void TargetWidget::setRotation(int degrees)
{
    m_rotation = degrees % 360;
    update();
}

void TargetWidget::setTargetType(int type)
{
    m_type = static_cast<TargetType>(type);
    update();
}

void TargetWidget::setTargetTypeByName(const QString &name)
{
    QString n = name.toUpper();
    if      (n == "DRONE")      m_type = DRONE;
    else if (n == "HELICOPTER") m_type = HELICOPTER;
    else if (n == "AIRCRAFT")   m_type = AIRCRAFT;
    update();
}

void TargetWidget::onBlinkTimer()
{
    m_blinkVisible = !m_blinkVisible;
    update();
}

//  paintEvent
void TargetWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const int W      = width();        //width=110 & height=170 taken on the UI(mainwindow.ui page).
    const int H      = height();
    const int topPad = 18;
    const int botPad = 18;
    const int drawH  = H - topPad - botPad;     // Area where target will appear after subtracting the topad and botpad.
    const double cx  = W / 2.0;                         // center point of the target for the x-axis.
    const double cy  = topPad + drawH / 2.0;            //center point of the target for the y-axis.

    const double R   = qMin((double)W, (double)drawH) / 2.0 - 6;            // Take whichever is smaller, widget width or drawing height, take half of it, and leave 6 pixels as margin.
    // (W=110 drawH = 134) smaller value = 110, 110 / 2 = 55 55 - 6 = 49;
    // R = 49; So, now the program can say things like: R * 0.88 R * 0.75 R * 0.42 R * 0.09
    // Instead of saying : 43 pixels 37 pixels 21 pixels 4 pixels


    //  State colours
    QColor bodyColor, outlineColor, stateColor;
    QString stateText;

    switch (m_state) {

    case OFF:
        // bodyColor   = QColor("#ffffff"); // Pure White background
        // outlineColor= QColor("#cccccc"); // Light Gray border (so it remains visible)
        // stateColor  = QColor("#333333"); // Dark Gray text (so you can read it)
        // stateText   = "OFF";

        bodyColor   = QColor("#ffffff"); // Pure White background
        outlineColor= QColor("#ffffff");
        stateColor  = QColor("#ffffff");
        stateText   = "OFF";
        break;

    case STANDBY:
        bodyColor   = QColor("#0a280a");
        outlineColor= QColor("#22cc22");
        stateColor  = QColor("#22cc22");
        stateText   = "STANDBY";
        break;

    case READY:
        bodyColor   = QColor("#2a1e00");
        outlineColor= QColor("#d4a800");
        stateColor  = QColor("#d4a800");
        stateText   = "READY";
        break;

    case FIRE:
    default:
        bodyColor   = m_blinkVisible ? QColor("#3a0000") : QColor("#100000");
        outlineColor= m_blinkVisible ? QColor("#ff2200") : QColor("#550000");
        stateColor  = m_blinkVisible ? QColor("#ff2200") : QColor("#550000");
        stateText   = "LOCKED";
        break;
    }

    // Background
    p.fillRect(rect(), QColor("#800A120A"));

    //  Rotated drawing area
    p.save();
    p.translate(cx, cy);
    p.rotate(m_rotation);     // You draw it once facing upward and rotate the painter.     // rotates the entire target around its center.

    switch (m_type) {
    case DRONE:      drawDrone(p,      0, 0, R, bodyColor, outlineColor, stateColor); break;
    case HELICOPTER: drawHelicopter(p, 0, 0, R, bodyColor, outlineColor, stateColor); break;
    case AIRCRAFT:   drawAircraft(p,   0, 0, R, bodyColor, outlineColor, stateColor); break;
    }

    p.restore();

    //  State dot top-right
    p.setPen(Qt::NoPen);
    p.setBrush(stateColor);
    p.drawEllipse(QPoint(W - 10, 10), 5, 5);

    //  Label at top
    p.setPen(QColor("#22cc22"));
    p.setFont(QFont("Consolas", 13, QFont::Bold));
    p.drawText(QRect(0, 0, W - 18, topPad), Qt::AlignCenter, m_label);

    //  State text at bottom
    p.setPen(stateColor);
    p.setFont(QFont("Consolas", 13, QFont::Bold));
    p.drawText(QRect(0, H - botPad, W, botPad), Qt::AlignCenter, stateText);
}

//  DRONE  — top-down X-config quadrotor
void TargetWidget::drawDrone(QPainter &p, int cx, int cy, double R,
                             const QColor &body, const QColor &outline, const QColor &stateCol)
{
    double bR      = R * 0.22;   // body hexagon radius (bR is the size of the central body.) defines the size of the central hexagon.
    double armLen  = R * 0.62;   // armLen is the distance from the center to each rotor.
    double rotorR  = R * 0.26;   // rotorR is the radius of each rotor.
    int    angles[4] = { -135, -45, 45, 135 };          // 4 rotor directions

    // Arms + rotors
    for (int i = 0; i < 4; ++i) {
        // Take the center and move armLen pixels in the selected direction.
        double rad = qDegreesToRadians((double)angles[i]);
        double ax  = cx + armLen * qCos(rad);
        double ay  = cy + armLen * qSin(rad);

        p.setPen(QPen(outline, 2.0));
        p.drawLine(QPointF(cx, cy), QPointF(ax, ay));       // draws the arm.

        p.setPen(QPen(outline, 1.0));
        p.setBrush(body.lighter(130));
        p.drawEllipse(QPointF(ax, ay), rotorR, rotorR);     // draws the rotor circle.

        // Blade cross (Inside the rotor of the drone cross)
        p.setPen(QPen(stateCol, 0.8));
        p.drawLine(QPointF(ax - rotorR*0.7, ay), QPointF(ax + rotorR*0.7, ay));
        p.drawLine(QPointF(ax, ay - rotorR*0.7), QPointF(ax, ay + rotorR*0.7));
    }

    // Central hexagonal body
    QPolygonF body6;
    for (int i = 0; i < 6; ++i) {                         // creates six points around the center.
        double a = qDegreesToRadians(i * 60.0 - 30.0);    // the angle changes by 60 degree each time.
        body6 << QPointF(cx + bR * qCos(a), cy + bR * qSin(a));
    }
    p.setPen(QPen(outline, 1.2));
    p.setBrush(body);
    p.drawPolygon(body6);           // giving the central hexagonal drone body.

    // Nose triangle (forward = up before rotation)
    // to show which direction the drone is facing.
    QPolygonF nose;
    nose << QPointF(cx,       cy - bR - 6)
         << QPointF(cx - 4,  cy - bR)
         << QPointF(cx + 4,  cy - bR);
    p.setPen(Qt::NoPen);
    p.setBrush(stateCol);
    p.drawPolygon(nose);        // joined those 3 points.
}

// //  HELICOPTER  — top-down view facing UP (fuselage + skids + 4-blade rotor + tail wing)
void TargetWidget::drawHelicopter(QPainter &p, int cx, int cy, double R,
                                  const QColor &body,
                                  const QColor &outline,
                                  const QColor &stateCol)
{
    // Overall helicopter scale
    const double S = 0.88;
    R *= S;                         // Scaling factor for the helicopter(making the helicopter slightly smaller).

    // 1. Landing Skids
    double skidH    = R * 0.75;     // controls the vertical length.
    double skidDist = R * 0.24;     // controls how far the left and right skids are from the center.

    p.setPen(QPen(outline, 1.0));
    p.setBrush(Qt::NoBrush);

    // For vertical skidline of helicap
    p.drawLine(QPointF(cx - skidDist, cy - skidH * 0.35),
               QPointF(cx - skidDist, cy + skidH * 0.45));

    p.drawLine(QPointF(cx + skidDist, cy - skidH * 0.35),
               QPointF(cx + skidDist, cy + skidH * 0.45));

    // For horizontal landing skid lines
    p.drawLine(QPointF(cx - skidDist, cy - skidH * 0.08),
               QPointF(cx + skidDist, cy - skidH * 0.08));

    p.drawLine(QPointF(cx - skidDist, cy + skidH * 0.18),
               QPointF(cx + skidDist, cy + skidH * 0.18));

    // 2. Tail Boom & Stabilizer
    QPolygonF tailBoom;
    tailBoom << QPointF(cx - R * 0.06, cy + R * 0.18)        // creates the tail boom(before the rectangel part)
             << QPointF(cx + R * 0.06, cy + R * 0.18)
             << QPointF(cx + R * 0.015, cy + R * 0.72)
             << QPointF(cx - R * 0.015, cy + R * 0.72);

    p.setPen(QPen(outline, 1.0));
    p.setBrush(body);
    p.drawPolygon(tailBoom);

    double tailWingW = R * 0.32;
    double tailWingH = R * 0.07;
    double tailWingY = cy + R * 0.62;

    // For drawing the rectangle for the helicap tail
    p.drawRect(QRectF(cx - tailWingW / 2.0,
                      tailWingY,
                      tailWingW,
                      tailWingH));

    p.drawLine(QPointF(cx, cy + R * 0.72),              // For the helicap tail after rectangle portion.
               QPointF(cx, cy + R * 0.82));

    // 3. Fuselage(outer cubical part of the helicap)
    QPainterPath fusePath;

    fusePath.moveTo(cx, cy - R * 0.48);     // near the top.

    fusePath.cubicTo(cx - R * 0.24, cy - R * 0.30,      // cubic shape for the helicap(creates the smooth curves)
                     cx - R * 0.20, cy + R * 0.15,
                     cx - R * 0.07, cy + R * 0.28);

    fusePath.lineTo(cx + R * 0.07, cy + R * 0.28);

    fusePath.cubicTo(cx + R * 0.20, cy + R * 0.15,
                     cx + R * 0.24, cy - R * 0.30,
                     cx, cy - R * 0.48);

    p.setPen(QPen(outline, 1.1));
    p.setBrush(body);
    p.drawPath(fusePath);

    // 4. Cockpit Canopy            // Transpart of the helicap for outside view
    QPainterPath canopyPath;

    canopyPath.moveTo(cx, cy - R * 0.40);

    canopyPath.cubicTo(cx - R * 0.14, cy - R * 0.28,
                       cx - R * 0.12, cy - R * 0.12,
                       cx - R * 0.09, cy - R * 0.05);

    canopyPath.lineTo(cx + R * 0.09, cy - R * 0.05);

    canopyPath.cubicTo(cx + R * 0.12, cy - R * 0.12,
                       cx + R * 0.14, cy - R * 0.28,
                       cx, cy - R * 0.40);

    p.setBrush(body.lighter(160));
    p.drawPath(canopyPath);

    // 5. Rotor Sweep Disc
    double mrRadius = R * 0.95;

    p.setPen(QPen(stateCol, 1.0, Qt::DashLine));
    p.setBrush(Qt::NoBrush);

    p.drawEllipse(QPointF(cx, cy - R * 0.02),
                  mrRadius,
                  mrRadius);

    // 6. Main Rotor
    double rx = cx;
    double ry = cy - R * 0.02;

    double offset = mrRadius * 0.90;

    p.setPen(QPen(stateCol, 2.5));

    p.drawLine(QPointF(rx - offset, ry - offset),
               QPointF(rx + offset, ry + offset));

    p.drawLine(QPointF(rx - offset, ry + offset),
               QPointF(rx + offset, ry - offset));

    p.setPen(QPen(outline, 1.0));
    p.setBrush(outline);

    p.drawEllipse(QPointF(rx, ry), 4.0, 4.0);

    // 7. Direction Arrow
    QPolygonF arrow;

    arrow << QPointF(cx,     cy - R * 0.50 - 5)
          << QPointF(cx - 4, cy - R * 0.50 + 3)
          << QPointF(cx + 4, cy - R * 0.50 + 3);

    p.setPen(Qt::NoPen);
    p.setBrush(stateCol);
    p.drawPolygon(arrow);
}

//  AIRCRAFT  — top-down fixed-wing fighter silhouette

void TargetWidget::drawAircraft(QPainter &p, int cx, int cy, double R,
                                const QColor &body, const QColor &outline, const QColor &stateCol)
{
    // --- Fuselage (narrow pointed body, top-down view) ---
    QPainterPath fuse;
    fuse.moveTo(cx,           cy - R * 0.88);          // nose tip
    fuse.quadTo(cx + R*0.13,  cy,
                cx + R*0.09,  cy + R * 0.75);          // right side
    fuse.lineTo(cx,            cy + R * 0.82);          // tail centre
    fuse.lineTo(cx - R*0.09,  cy + R * 0.75);          // left tail
    fuse.quadTo(cx - R*0.13,  cy,
                cx,            cy - R * 0.88);          // back to nose
    p.setPen(QPen(outline, 1.2));
    p.setBrush(body);
    p.drawPath(fuse);

    // --- Main wings (swept delta) ---
    QPolygonF leftWing;
    leftWing << QPointF(cx,           cy - R * 0.10)
             << QPointF(cx - R * 0.88, cy + R * 0.52)
             << QPointF(cx - R * 0.28, cy + R * 0.55)
             << QPointF(cx - R * 0.09, cy + R * 0.18);
    p.setPen(QPen(outline, 1.0));
    p.setBrush(body.lighter(115));
    p.drawPolygon(leftWing);

    QPolygonF rightWing;
    rightWing << QPointF(cx,           cy - R * 0.10)
              << QPointF(cx + R * 0.88, cy + R * 0.52)
              << QPointF(cx + R * 0.28, cy + R * 0.55)
              << QPointF(cx + R * 0.09, cy + R * 0.18);
    p.drawPolygon(rightWing);

    // --- Tail fins (small canards near tail) ---
    QPolygonF leftTail;
    leftTail << QPointF(cx - R*0.09, cy + R * 0.58)
             << QPointF(cx - R*0.38, cy + R * 0.80)
             << QPointF(cx - R*0.09, cy + R * 0.82);
    p.setBrush(body);
    p.drawPolygon(leftTail);

    QPolygonF rightTail;
    rightTail << QPointF(cx + R*0.09, cy + R * 0.58)
              << QPointF(cx + R*0.38, cy + R * 0.80)
              << QPointF(cx + R*0.09, cy + R * 0.82);
    p.drawPolygon(rightTail);

    // --- Cockpit canopy (small oval near nose) ---
    p.setPen(QPen(outline, 0.8));
    p.setBrush(body.lighter(180));
    p.drawEllipse(QPointF(cx, cy - R * 0.42), R * 0.07, R * 0.18);

    // --- Engine exhausts at tail ---
    p.setPen(QPen(stateCol, 1.5));
    p.drawLine(QPointF(cx - R*0.04, cy + R*0.78),
               QPointF(cx - R*0.04, cy + R*0.88));
    p.drawLine(QPointF(cx + R*0.04, cy + R*0.78),
               QPointF(cx + R*0.04, cy + R*0.88));

    // --- Nose dot ----
    p.setPen(Qt::NoPen);
    p.setBrush(stateCol);
    p.drawEllipse(QPointF(cx, cy - R * 0.84), 3, 3);
}
