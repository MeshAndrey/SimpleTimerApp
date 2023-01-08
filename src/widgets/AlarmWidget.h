#ifndef ALARMWIDGET_H
#define ALARMWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>

class AlarmWidget : public QWidget
{
    Q_OBJECT
private:
    QPushButton *stopButton = nullptr;
public:
    explicit AlarmWidget(QWidget *parent = nullptr);

private slots:
    void stopButtonClicked();
signals:

};

#endif // ALARMWIDGET_H
