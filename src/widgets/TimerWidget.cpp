#include "TimerWidget.h"
#include "AlarmWidget.h"
#include "InputWidget.h"
#include "../MainWindow.h"

TimerWidget::TimerWidget(int timerValue, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout;
    QHBoxLayout * horLayout = new QHBoxLayout;

    allocateMemory();
    makeConnections();

    horLayout->addWidget(pauseResumeButton);
    horLayout->addWidget(stopButton);

    layout->addWidget(remainingTimeLabel, 0, Qt::AlignCenter);
    layout->addLayout(horLayout);

    timer->setSingleShot(true);
    timer->setInterval(timerValue);

    updateTimer->setInterval(1000);

    timer->start();
    updateTimer->start();

    remainingTimeLabel->setText(convertToReadable(round(timerValue)));

    setLayout(layout);
}

void TimerWidget::allocateMemory()
{
    pauseResumeButton = new QPushButton("Pause");
    stopButton = new QPushButton("Stop");
    remainingTimeLabel = new QLabel("Text");

    timer = new QTimer;
    updateTimer = new QTimer;
}

void TimerWidget::makeConnections()
{
    connect(pauseResumeButton, &QPushButton::clicked,
            this, &TimerWidget::pauseResumeButtonCLicked);
    connect(stopButton, &QPushButton::clicked,
            this, &TimerWidget::stopButtonClicked);

    connect(timer, &QTimer::timeout, this, &TimerWidget::timerTimeout);
    connect(updateTimer, &QTimer::timeout,
            this, &TimerWidget::updateTimerTimeout);
}

void TimerWidget::pauseResumeButtonCLicked()
{
    showMessageBox("Pause button clicked");
}

void TimerWidget::stopButtonClicked()
{
    updateTimer->stop();
    timer->stop();

    this->close();

    ((MainWindow*)parent())->setCentralWidget(new InputWidget);
}

void TimerWidget::timerTimeout()
{
    this->close();

    ((MainWindow*)parent())->setCentralWidget(new AlarmWidget);
}

void TimerWidget::updateTimerTimeout()
{
    if (timer->isActive())
        remainingTimeLabel->setText(convertToReadable(round(timer->remainingTime())));
}

int TimerWidget::round(int value)
{
    if (value == 0)
        return value; // zero
    if ((value >= 1000) && (value % 1000 == 0))
        return value; // already round

    if (((value % 1000) > 500) && ((value % 1000) <= 999))
    {
        return (value - (value % 1000) + 1000);
    }
    else if (((value % 1000) >= 1) && ((value % 1000) <= 500))
    {
        return (value - (value % 1000));
    }

    return value;
}

QString TimerWidget::convertToReadable(int value)
{
    if (value < 0)
        return "Error value";

    int h = value / (1000 * 60 * 60);                                 // hours
    int m = (value - (h  * 1000 * 60 * 60)) / (1000 * 60);            // minutes
    int s = (value - (h  * 1000 * 60 * 60) - (m * 1000 * 60)) / 1000; // seconds

    if (h > 0)
        return QString("%1:%2:%3").arg(makeTimeString(QString::number(h)),
                                       makeTimeString(QString::number(m)),
                                       makeTimeString(QString::number(s)));

    if (m > 0)
        return QString("%1:%2").arg(makeTimeString(QString::number(m)),
                                    makeTimeString(QString::number(s)));

    if (s > 0)
        return makeTimeString(QString::number(s));

    return "00";
}

QString TimerWidget::makeTimeString(QString time) // don't know how to name this shit
{
    if (time.isEmpty())
        return time;

    return time.length() == 2 ? time : time.prepend("0");
}

void TimerWidget::showMessageBox(QString message)
{
    if (message.isEmpty())
        return;

    QMessageBox msg;
    msg.setText(message);
    msg.exec();
}
