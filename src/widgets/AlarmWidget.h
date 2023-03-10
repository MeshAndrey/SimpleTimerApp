#ifndef ALARMWIDGET_H
#define ALARMWIDGET_H

#include <QObject>
#include <QWidget>
#include <QSound>
#include <QtWidgets>

class AlarmWidget : public QWidget
{
    Q_OBJECT
private:
    int timerValue = 0;

    QString name;
    QPushButton *stopButton   = nullptr,
                *repeatButton = nullptr;
    QLabel *timeLabel = nullptr;
    QSound *alarmSound = nullptr;

    QElapsedTimer elapsedTimer;
    QTimer updateTimer;

    void initWidgets();
    void initLayout();
    void initConnections();

public:
    explicit AlarmWidget(QString name, int timerValue, QWidget *parent = nullptr);

private slots:
    void stopButtonClicked();
    void repeatButtonClicked();
    void updateTimerTimeout();
};

#endif // ALARMWIDGET_H
