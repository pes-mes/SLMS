#ifndef TRANSPARENTPUSHBUTTON_H
#define TRANSPARENTPUSHBUTTON_H

#include <QPushButton>
#include <QEnterEvent>

class TransparentPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit TransparentPushButton(QWidget *parent = nullptr);
    explicit TransparentPushButton(const QString &text,
                                   QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    bool m_hovered = false;
};

#endif // TRANSPARENTPUSHBUTTON_H