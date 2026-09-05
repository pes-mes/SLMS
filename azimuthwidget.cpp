#include "azimuthwidget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QtMath>

AzimuthWidget::AzimuthWidget(QWidget *parent)
    : QWidget(parent)
    , azimuth(0)
{
    // setMinimumSize(156, 180);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

QSize AzimuthWidget::sizeHint() const
{
    return QSize(162, 186);
}

void AzimuthWidget::setAzimuth(int degrees)
{
    azimuth = degrees;
    update(); // this tells Qt to call paintEvent again
}

void AzimuthWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int cx = width() / 2;               // for width=235 and for height=275
    int cy = (height() - 24) / 2 + 18; // leave space for title at top
    int radius = qMin(width(), height() - 50) / 2 - 10;

    //  Background
    painter.fillRect(rect(), QColor("#800A120A"));

    //  Title
    painter.setPen(QColor("#22cc22"));
    painter.setFont(QFont("Consolas", 13, QFont::Bold));
    painter.drawText(QRect(0, 4, width(), 18), Qt::AlignCenter, "AZIMUTH BEARING");

    //  Outer circle
    painter.setPen(QPen(QColor("#1a8a1a"), 2));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(QPoint(cx, cy), radius, radius);

    //  Draw tick marks every 10 degrees
    for (int i = 0; i < 360; i += 10)
    {
        // Convert degree to radians (subtract 90 so 0 deg is at top)
        double rad = qDegreesToRadians((double)(i - 90));

        bool isCardinal = (i % 90 == 0);   // N, E, S, W
        bool isMinor    = (i % 30 == 0);   // every 30 degrees

        int tickLen = isCardinal ? 14 : isMinor ? 9 : 5;
        double lw   = isCardinal ? 2.0 : 0.8;

        QColor tickColor = isCardinal ? QColor("#26d426") : QColor("#0d6a0d");

        double x1 = cx + (radius - tickLen) * qCos(rad);
        double y1 = cy + (radius - tickLen) * qSin(rad);
        double x2 = cx + radius * qCos(rad);
        double y2 = cy + radius * qSin(rad);

        painter.setPen(QPen(tickColor, lw));
        painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
    }

    //  Draw degree numbers every 30 degrees
    painter.setFont(QFont("Consolas", 9, QFont::Bold));
    painter.setPen(QColor("#22cc22"));
    double labelDist = radius - 24;

    for (int i = 0; i < 360; i += 30)
    {
        if (i % 90 == 0) continue; // skip cardinals, drawn separately below

        double rad = qDegreesToRadians((double)(i - 90));
        double lx  = cx + labelDist * qCos(rad);
        double ly  = cy + labelDist * qSin(rad);
        painter.drawText(QRectF(lx - 16, ly - 8, 32, 16), Qt::AlignCenter, QString::number(i));
    }

    //  Draw N, E, S, W labels
    painter.setFont(QFont("Consolas", 13, QFont::Bold));
    QStringList cardinals = {"N", "E", "S", "W"};

    for (int i = 0; i < 4; i++)
    {
        double rad = qDegreesToRadians((double)(i * 90 - 90));
        double lx  = cx + labelDist * qCos(rad);
        double ly  = cy + labelDist * qSin(rad);

        // N label is orange to show True North
        if (i == 0)
            painter.setPen(QColor("#ff5500"));
        else
            painter.setPen(QColor("#22cc22"));

        painter.drawText(QRectF(lx - 10, ly - 10, 20, 20), Qt::AlignCenter, cardinals[i]);
    }

    // Draw the arrow (rotated by azimuth)
    // save() and restore() so the rotation only affects the arrow
    painter.save();
    painter.translate(cx, cy);
    painter.rotate(azimuth); // rotate clockwise = compass direction

    // Arrow tip points up (toward N = 0 degrees)
    double tip    = -(radius - 18);
    double base   = -(radius * 0.15);
    double tail   = radius - 18;

    // RED arrow head pointing up (North direction)
    QPolygonF arrowHead;
    arrowHead << QPointF(0, tip)
              << QPointF(8, base)
              << QPointF(3, base)
              << QPointF(3, radius * 0.35)
              << QPointF(-3, radius * 0.35)
              << QPointF(-3, base)
              << QPointF(-8, base);

    painter.setBrush(QColor("#ff5500"));
    painter.setPen(QPen(QColor("#cc2200"), 0.8));
    painter.drawPolygon(arrowHead);

    // Gray tail pointing down (South direction)
    QPolygonF arrowTail;
    arrowTail << QPointF(0, tail)
              << QPointF(5, radius * 0.40)
              << QPointF(-5, radius * 0.40);

    painter.setBrush(QColor("#888888"));
    painter.setPen(Qt::NoPen);
    painter.drawPolygon(arrowTail);

    painter.restore();

    //  Center dot
    painter.setBrush(QColor("#d4a800"));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(QPoint(cx, cy), 6, 6);

    //  Readout at bottom
    painter.setPen(QColor("#22cc22"));
    painter.setFont(QFont("Consolas", 13, QFont::Bold));
    painter.drawText(QRect(0, cy + radius + 8, width(), 20),
                     Qt::AlignCenter,
                     QString("AZ:  %1°").arg(azimuth, 3));
}


// #include "azimuthwidget.h"
// #include <QPainter>
// #include <QPen>
// #include <QBrush>
// #include <QtMath>

// AzimuthWidget::AzimuthWidget(QWidget *parent)
//     : QWidget(parent)
//     , azimuth(0)
// {
//     // setMinimumSize(156, 180);
//     setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
// }

// QSize AzimuthWidget::sizeHint() const
// {
//     return QSize(162, 186);
// }

// void AzimuthWidget::setAzimuth(int degrees)
// {
//     azimuth = degrees;
//     update(); // this tells Qt to call paintEvent again
// }

// void AzimuthWidget::paintEvent(QPaintEvent *)
// {
//     QPainter painter(this);
//     painter.setRenderHint(QPainter::Antialiasing);

//     int cx = width() / 2;                                   // for width=235 and for height=275
//     int cy = (height() - 24) / 2 + 18; // leave space for title at top
//     int radius = qMin(width(), height() - 50) / 2 - 10;

//     // --- Background ---
//     painter.fillRect(rect(), QColor("#800A120A"));

//     // --- Title ---
//     painter.setPen(QColor("#22cc22"));
//     painter.setFont(QFont("Consolas", 13, QFont::Bold));
//     painter.drawText(QRect(0, 4, width(), 18), Qt::AlignCenter, "AZIMUTH BEARING");

//     // --- Outer circle ---
//     painter.setPen(QPen(QColor("#1a8a1a"), 2));
//     painter.setBrush(Qt::NoBrush);
//     painter.drawEllipse(QPoint(cx, cy), radius, radius);

//     // --- Draw tick marks every 10 degrees ---
//     for (int i = -170; i < 170; i += 10)
//     {
//         // Convert degree to radians (subtract 90 so 0 deg is at top)
//         double rad = qDegreesToRadians((double)(i - 90));

//         bool isCardinal = (i % 90 == 0);   // N, E, S, W
//         bool isMinor    = (i % 30 == 0);   // every 30 degrees

//         int tickLen = isCardinal ? 14 : isMinor ? 9 : 5;
//         double lw   = isCardinal ? 2.0 : 0.8;

//         QColor tickColor = isCardinal ? QColor("#26d426") : QColor("#0d6a0d");

//         double x1 = cx + (radius - tickLen) * qCos(rad);
//         double y1 = cy + (radius - tickLen) * qSin(rad);
//         double x2 = cx + radius * qCos(rad);
//         double y2 = cy + radius * qSin(rad);

//         painter.setPen(QPen(tickColor, lw));
//         painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
//     }

//     // --- Draw degree numbers every 30 degrees ---
//     painter.setFont(QFont("Consolas", 9, QFont::Bold));
//     painter.setPen(QColor("#22cc22"));
//     double labelDist = radius - 24;

//     for (int i = -170; i < 170; i += 30)
//     {
//         if (i % 90 == 0) continue; // skip cardinals, drawn separately below

//         double rad = qDegreesToRadians((double)(i - 90));
//         double lx  = cx + labelDist * qCos(rad);
//         double ly  = cy + labelDist * qSin(rad);
//         painter.drawText(QRectF(lx - 16, ly - 8, 32, 16), Qt::AlignCenter, QString::number(i));
//     }

//     // --- Draw N, E, S, W labels ---
//     painter.setFont(QFont("Consolas", 13, QFont::Bold));
//     QStringList cardinals = {"N", "E", "S", "W"};

//     for (int i = 0; i < 4; i++)
//     {
//         double rad = qDegreesToRadians((double)(i * 90 - 90));
//         double lx  = cx + labelDist * qCos(rad);
//         double ly  = cy + labelDist * qSin(rad);

//         // N label is orange to show True North
//         if (i == 0)
//             painter.setPen(QColor("#ff5500"));
//         else
//             painter.setPen(QColor("#22cc22"));

//         painter.drawText(QRectF(lx - 10, ly - 10, 20, 20), Qt::AlignCenter, cardinals[i]);
//     }

//     //  Draw the arrow (rotated by azimuth) ---
//     // save() and restore() so the rotation only affects the arrow
//     painter.save();
//     painter.translate(cx, cy);
//     painter.rotate(azimuth); // rotate clockwise = compass direction

//     // Arrow tip points up (toward N = 0 degrees)
//     double tip    = -(radius - 18);
//     double base   = -(radius * 0.15);
//     double tail   = radius - 18;

//     // RED arrow head pointing up (North direction)
//     QPolygonF arrowHead;
//     arrowHead << QPointF(0, tip)
//               << QPointF(8, base)
//               << QPointF(3, base)
//               << QPointF(3, radius * 0.35)
//               << QPointF(-3, radius * 0.35)
//               << QPointF(-3, base)
//               << QPointF(-8, base);

//     painter.setBrush(QColor("#ff5500"));
//     painter.setPen(QPen(QColor("#cc2200"), 0.8));
//     painter.drawPolygon(arrowHead);

//     // Gray tail pointing down (South direction)
//     QPolygonF arrowTail;
//     arrowTail << QPointF(0, tail)
//               << QPointF(5, radius * 0.40)
//               << QPointF(-5, radius * 0.40);

//     painter.setBrush(QColor("#888888"));
//     painter.setPen(Qt::NoPen);
//     painter.drawPolygon(arrowTail);

//     painter.restore();

//     // --- Center dot ---
//     painter.setBrush(QColor("#d4a800"));
//     painter.setPen(Qt::NoPen);
//     painter.drawEllipse(QPoint(cx, cy), 6, 6);

//     // --- Readout at bottom ---
//     painter.setPen(QColor("#22cc22"));
//     painter.setFont(QFont("Consolas", 13, QFont::Bold));
//     painter.drawText(QRect(0, cy + radius + 8, width(), 20),
//                      Qt::AlignCenter,
//                      QString("AZ:  %1°").arg(azimuth, 3));
// }
