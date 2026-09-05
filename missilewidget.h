#ifndef MISSILEWIDGET_H
#define MISSILEWIDGET_H

#include <QWidget>
#include <QTimer>

class MissileWidget : public QWidget
{
    Q_OBJECT

public:
    enum State { OFF = 0, Power_ON = 1, Health_Checks = 2,
                 HealthGood = 3, HealthNotGood = 4, TrackingMode = 5 };

    explicit MissileWidget(QWidget *parent = nullptr);
    QSize sizeHint() const override;

    void setLabel(const QString &text);

public slots:
    void setState(int index);

private slots:
    void onBlinkTimer();

private:
    State   currentState;
    QString label;
    QTimer *blinkTimer;
    bool    blinkVisible;

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif
