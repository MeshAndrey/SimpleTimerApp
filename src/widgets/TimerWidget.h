#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>

#include "../MainWindow.h"

class TimerWidget : public QWidget
{
    Q_OBJECT
private:
    int timerValue = 0;
    bool autoStopAlarm = false;
    QString name,
            shellCommand;
    QLabel *remainingTimeLabel = nullptr;
    QPushButton *pauseResumeButton = nullptr,
                *stopButton        = nullptr;

    QTimer *timer       = nullptr,
           *updateTimer = nullptr;

    void initWidgets();
    void initLayout();
    void initConnections();
    void showMessageBox(const QString message);
    bool executeProcess(const QString program);

    MainWindow* getMainWindow();

private slots:
    void pauseResumeButtonCLicked();
    void stopButtonClicked();
    void timerTimeout();
    void updateTimerTimeout();

public:
    explicit TimerWidget(QString name, int timerValue,
                         QString shellCommand, bool autoStopAlarm,
                         QWidget *parent = nullptr);
};

#endif // TIMERWIDGET_H
