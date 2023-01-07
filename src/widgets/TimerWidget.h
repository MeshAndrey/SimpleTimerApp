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
    void makeConnections();
    int round(int value);

private slots:
    void pauseResumeButtonCLicked();
    void stopButtonClicked();
    void timerTimeout();
    void updateTimerTimeout();

public:
    explicit TimerWidget(int timerValue, QWidget *parent = nullptr);

signals:

};

#endif // TIMERWIDGET_H
