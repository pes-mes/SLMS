// #ifndef ELEVATIONWIDGET_H
// #define ELEVATIONWIDGET_H

// #include <QWidget>

// // Task 3: Vertical bar showing elevation -90 to +90 degrees with a FOV window
// class ElevationWidget : public QWidget
// {
//     Q_OBJECT

// public:
//     explicit ElevationWidget(QWidget *parent = nullptr);
//     QSize sizeHint() const override;

// public slots:
//     void setElevation(int degrees); // called from mainwindow when data arrives

// private:
//     int elevation; // current elevation -90 to +90
//     int fov;       // field of view window size in degrees

// protected:
//     void paintEvent(QPaintEvent *event) override;
// };

// #endif


#ifndef ELEVATIONWIDGET_H
#define ELEVATIONWIDGET_H

#include <QWidget>

// Task 3: Vertical bar showing elevation -10 to +70 degrees with a FOV window
class ElevationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ElevationWidget(QWidget *parent = nullptr);
    QSize sizeHint() const override;

public slots:
    void setElevation(int degrees); // called from mainwindow when data arrives

private:
    int elevation; // current elevation -10 to +70
    int fov;       // field of view window size in degrees

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif
