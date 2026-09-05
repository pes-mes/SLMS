#ifndef AZIMUTHWIDGET_H
#define AZIMUTHWIDGET_H

#include <QWidget>

// Task 1 & 2: Draws a compass circle with ticks and a rotating arrow
class AzimuthWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AzimuthWidget(QWidget *parent = nullptr);
    QSize sizeHint() const override;

public slots:
    void setAzimuth(int degrees); // call this from mainwindow when data arrives

private:
    int azimuth; // stores current angle 0-359

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif
