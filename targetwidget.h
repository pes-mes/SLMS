#ifndef TARGETWIDGET_H
#define TARGETWIDGET_H

#include <QWidget>
#include <QTimer>

// Unified target widget: draws Drone, Helicopter, or Aircraft silhouette.
// Replaces DroneWidget. Target type switches via setTargetType().
class TargetWidget : public QWidget
{
    Q_OBJECT

public:
    enum State      { OFF = 0, STANDBY = 1, READY = 2, FIRE = 3 };
    enum TargetType { DRONE = 0, HELICOPTER = 1, AIRCRAFT = 2 };

    explicit TargetWidget(QWidget *parent = nullptr);
    QSize sizeHint() const override;

    void setLabel(const QString &text);

public slots:
    void setState(int index);           // 0=OFF 1=STANDBY 2=READY 3=FIRE
    void setRotation(int degrees);      // 0-359, rotates the silhouette
    void setTargetType(int type);       // 0=DRONE 1=HELICOPTER 2=AIRCRAFT
    void setTargetTypeByName(const QString &name); // "DRONE","HELICOPTER","AIRCRAFT"

private slots:
    void onBlinkTimer();

private:
    State      m_state;
    TargetType m_type;
    QString    m_label;
    int        m_rotation;
    QTimer    *m_blinkTimer;
    bool       m_blinkVisible;

    // Painters for each target type
    void drawDrone(QPainter &p, int cx, int cy, double R,
                   const QColor &body, const QColor &outline, const QColor &state);
    void drawHelicopter(QPainter &p, int cx, int cy, double R,
                        const QColor &body, const QColor &outline, const QColor &state);
    void drawAircraft(QPainter &p, int cx, int cy, double R,
                      const QColor &body, const QColor &outline, const QColor &state);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // TARGETWIDGET_H
