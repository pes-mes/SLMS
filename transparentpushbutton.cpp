#include "TransparentPushButton.h"

#include <QPainter>
#include <QStyle>
#include <QStyleOptionButton>

TransparentPushButton::TransparentPushButton(QWidget *parent)
    : QPushButton(parent)
{
    setCursor(Qt::PointingHandCursor);   //  A pointing hand cursor that is typically used for clickable elements such as hyperlinks.
    setFlat(true);
}

TransparentPushButton::TransparentPushButton(const QString &text,
                                             QWidget *parent)
    : QPushButton(text, parent)
{
    setCursor(Qt::PointingHandCursor);
    setFlat(true);
}

void TransparentPushButton::enterEvent(QEnterEvent *event)
{
    m_hovered = true;
    update();

    QPushButton::enterEvent(event);
}

void TransparentPushButton::leaveEvent(QEvent *event)
{
    m_hovered = false;
    update();

    QPushButton::leaveEvent(event);
}

void TransparentPushButton::paintEvent(QPaintEvent *)
{

    // qDebug() << "TransparentPushButton paintEvent";
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    QRect r = rect().adjusted(1,1,-1,-1);

    QColor bg(10,18,10,128);

    if (!isEnabled())
        bg = QColor(30,30,30,80);

    else if (isDown())
        bg = QColor(20,34,20,220);

    else if (isChecked())
        bg = QColor(20,34,20,180);

    else if (m_hovered)
        bg = QColor(20,34,20,170);

    painter.setPen(QPen(QColor(34,204,34,180),1));
    painter.setBrush(bg);

    painter.drawRoundedRect(r,6,6);

    QStyleOptionButton option;
    initStyleOption(&option);

    style()->drawControl(QStyle::CE_PushButtonLabel,
                         &option,
                         &painter,
                         this);
}