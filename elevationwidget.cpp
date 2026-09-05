// #include "elevationwidget.h"
// #include <QPainter>
// #include <QPen>

// ElevationWidget::ElevationWidget(QWidget *parent)
//     : QWidget(parent)
//     , elevation(0)
//     , fov(6)
// {
//     setMinimumSize(80, 140);
//     setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
// }

// QSize ElevationWidget::sizeHint() const
// {
//     return QSize(90, 155);
// }

// void ElevationWidget::setElevation(int degrees)
// {
//     // Clamp value between -90 and +90
//     if (degrees < -90) degrees = -90;
//     if (degrees >  90) degrees =  90;
//     elevation = degrees;
//     update();
// }

// void ElevationWidget::paintEvent(QPaintEvent *)
// {
//     QPainter painter(this);
//     painter.setRenderHint(QPainter::Antialiasing);

//     // Layout
//     int titleH  = 20;
//     int readoutH = 20;
//     int padding  = 6;

//     double barW = width() * 0.28;
//     double barX = (width() - barW) / 2.0;
//     double barTop    = titleH + padding;
//     double barBottom = height() - readoutH - padding;
//     double barHeight = barBottom - barTop;
//     double midY      = barTop + barHeight / 2.0;  // this is the 0 degree line
//     double pixPerDeg = barHeight / 180.0;          // how many pixels per degree

//     // --- Dark background ---
//     painter.fillRect(rect(), QColor("#800A120A"));

//     // --- Title
//     painter.setPen(QColor("#22cc22"));
//     painter.setFont(QFont("Consolas", 13, QFont::Bold));
//     painter.drawText(QRect(0, 2, width(), titleH), Qt::AlignCenter, "ELEVATION");

//     //  Bar background
//     painter.setPen(QPen(QColor("#1a4a1a"), 0.8));
//     painter.setBrush(QColor("#0a200a"));
//     painter.drawRect(QRectF(barX, barTop, barW, barHeight));

//     //  FOV window bracket (gold dashed box around current angle)
//     double elY      = midY - elevation * pixPerDeg;
//     double fovPixH  = fov * pixPerDeg;
//     double bracketX = barX - 5;
//     double bracketW = barW + 10;

//     painter.setPen(QPen(QColor("#d4a800"), 1.0, Qt::DashLine));
//     painter.setBrush(Qt::NoBrush);
//     painter.drawRect(QRectF(bracketX, elY - fovPixH, bracketW, fovPixH * 2));

//     //  Zero degree dashed line
//     painter.setPen(QPen(QColor("#1a6a1a"), 1.0, Qt::DashLine));
//     painter.drawLine(QPointF(barX - 6, midY), QPointF(barX + barW + 6, midY));

//     //  Tick marks and degree labels
//     painter.setFont(QFont("Courier New", 9, QFont::Bold));

//     for (int deg = -90; deg <= 90; deg += 30)
//     {
//         double y = midY - deg * pixPerDeg;
//         bool isMajor = (deg % 90 == 0);
//         double tickLen = isMajor ? 8 : 5;

//         painter.setPen(QPen(isMajor ? QColor("#26d426") : QColor("#157a15"),
//                             isMajor ? 1.4 : 0.7));

//         // Left tick
//         painter.drawLine(QPointF(barX - tickLen, y), QPointF(barX, y));
//         // Right tick
//         painter.drawLine(QPointF(barX + barW, y), QPointF(barX + barW + tickLen - 3, y));

//         // Label on left side
//         painter.setPen(QColor("#22cc22"));
//         painter.drawText(QRectF(0, y - 8, barX - tickLen - 1, 16),
//                          Qt::AlignRight | Qt::AlignVCenter,
//                          QString::number(deg));
//     }

//     //  Current elevation marker (orange line)
//     painter.setPen(QPen(QColor("#ff5500"), 1.8));
//     painter.drawLine(QPointF(barX - 3, elY), QPointF(barX + barW + 3, elY));

//     // Arrow pointer on the right side
//     QPolygonF arrow;
//     arrow << QPointF(barX + barW + 4, elY)
//           << QPointF(barX + barW + 10, elY - 4)
//           << QPointF(barX + barW + 10, elY + 4);
//     painter.setBrush(QColor("#ff5500"));
//     painter.setPen(Qt::NoPen);
//     painter.drawPolygon(arrow);

//     // Readout at bottom
//     painter.setPen(QColor("#22cc22"));
//     painter.setFont(QFont("Consolas", 13, QFont::Bold));
//     painter.drawText(QRect(0, height() - readoutH, width(), readoutH),
//                      Qt::AlignCenter,
//                      QString("EL: %1°").arg(elevation));
// }

#include "elevationwidget.h"
#include <QPainter>
#include <QPen>
#include <QPolygonF>

ElevationWidget::ElevationWidget(QWidget *parent)
    : QWidget(parent)
    , elevation(0)
    , fov(6)
{
    setMinimumSize(80, 140);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}

QSize ElevationWidget::sizeHint() const
{
    return QSize(90, 155);
}

void ElevationWidget::setElevation(int degrees)
{
    // Clamp elevation between -10 and +70 degrees
    if (degrees < -10)
        degrees = -10;

    if (degrees > 70)
        degrees = 70;

    elevation = degrees;
    update();
}

void ElevationWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Layout
    int titleH = 20;
    int readoutH = 20;
    int padding = 6;

    double barW = width() * 0.28;
    double barX = (width() - barW) / 2.0;

    double barTop = titleH + padding;
    double barBottom = height() - readoutH - padding;

    // Keep exactly the same physical bar height as the previous -90 to +90 degree scale.
    double barHeight = barBottom - barTop;

    // The elevation range is now:
    // -10 degrees at the bottom
    // +70 degrees at the top
    //
    // Total range = 80 degrees
    const double minElevation = -10.0;
    const double maxElevation = 70.0;
    const double elevationRange = maxElevation - minElevation;

    // Position corresponding to 0 degree
    double zeroY = barTop
                   + (maxElevation / elevationRange) * barHeight;

    // Pixels per degree
    double pixPerDeg = barHeight / elevationRange;

    // Dark background
    painter.fillRect(rect(), QColor("#800A120A"));

    // Title
    painter.setPen(QColor("#22cc22"));
    painter.setFont(QFont("Consolas", 13, QFont::Bold));
    painter.drawText(QRect(0, 2, width(), titleH),
                     Qt::AlignCenter,
                     "ELEVATION");

    // Bar background
    painter.setPen(QPen(QColor("#1a4a1a"), 0.8));
    painter.setBrush(QColor("#0a200a"));
    painter.drawRect(QRectF(barX, barTop, barW, barHeight));

    // Current elevation position
    double elY = zeroY - elevation * pixPerDeg;

    // FOV window bracket
    double fovPixH = fov * pixPerDeg;

    double bracketX = barX - 5;
    double bracketW = barW + 10;

    painter.setPen(QPen(QColor("#d4a800"), 1.0, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);

    painter.drawRect(QRectF(bracketX,
                            elY - fovPixH,
                            bracketW,
                            fovPixH * 2));

    // Zero degree dashed line
    painter.setPen(QPen(QColor("#1a6a1a"),
                        1.0,
                        Qt::DashLine));

    painter.drawLine(QPointF(barX - 6, zeroY),
                     QPointF(barX + barW + 6, zeroY));

    // Tick marks and degree labels
    painter.setFont(QFont("Courier New", 9, QFont::Bold));

    // Tick values for -10 to +70
    // 10 degree spacing gives:
    // -10, 0, 10, 20, 30, 40, 50, 60, 70
    for (int deg = -10; deg <= 70; deg += 10)
    {
        double y = zeroY - deg * pixPerDeg;

        // Major ticks at -10, 0, 10, 30, 50, 70
        bool isMajor = (deg == -10 ||
                        deg == 0 ||
                        deg == 10 ||
                        deg == 30 ||
                        deg == 50 ||
                        deg == 70);

        double tickLen = isMajor ? 8 : 5;

        painter.setPen(QPen(
            isMajor ? QColor("#26d426") : QColor("#157a15"),
            isMajor ? 1.4 : 0.7
            ));

        // Left tick
        painter.drawLine(QPointF(barX - tickLen, y),
                         QPointF(barX, y));

        // Right tick
        painter.drawLine(QPointF(barX + barW, y),
                         QPointF(barX + barW + tickLen - 3, y));

        // Degree label
        painter.setPen(QColor("#22cc22"));

        painter.drawText(
            QRectF(0,
                   y - 8,
                   barX - tickLen - 1,
                   16),
            Qt::AlignRight | Qt::AlignVCenter,
            QString::number(deg)
            );
    }

    // Current elevation marker
    painter.setPen(QPen(QColor("#ff5500"), 1.8));

    painter.drawLine(
        QPointF(barX - 3, elY),
        QPointF(barX + barW + 3, elY)
        );

    // Arrow pointer on the right side
    QPolygonF arrow;

    arrow << QPointF(barX + barW + 4, elY)
          << QPointF(barX + barW + 10, elY - 4)
          << QPointF(barX + barW + 10, elY + 4);

    painter.setBrush(QColor("#ff5500"));
    painter.setPen(Qt::NoPen);
    painter.drawPolygon(arrow);

    // Readout at bottom
    painter.setPen(QColor("#22cc22"));
    painter.setFont(QFont("Consolas", 13, QFont::Bold));

    painter.drawText(
        QRect(0,
              height() - readoutH,
              width(),
              readoutH),
        Qt::AlignCenter,
        QString("EL: %1°").arg(elevation)
        );
}