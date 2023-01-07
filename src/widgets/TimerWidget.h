#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>

class TimerWidget : public QWidget
{
    Q_OBJECT
private:
    QLabel *remainingTimeLabel = nullptr;
    QPushButton *pauseResumeButton = nullptr,
                *stopButton        = nullptr;

    QTimer *timer       = nullptr,
           *updateTimer = nullptr;

    void allocateMemory();
    void showMessageBox(QString message);

private slots:
    void pauseResumeButtonCLicked();
    void stopButtonClicked();
    void timerTimeout();

public:
    explicit TimerWidget(QWidget *parent = nullptr);

signals:

};

#endif // TIMERWIDGET_H
