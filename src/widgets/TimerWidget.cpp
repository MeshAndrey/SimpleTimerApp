#include "TimerWidget.h"

TimerWidget::TimerWidget(int timerValue, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout;
    QHBoxLayout * horLayout = new QHBoxLayout;

    allocateMemory();

    horLayout->addWidget(pauseResumeButton);
    horLayout->addWidget(stopButton);

    layout->addWidget(remainingTimeLabel);
    layout->addLayout(horLayout);

    connect(pauseResumeButton, &QPushButton::clicked,
            this, &TimerWidget::pauseResumeButtonCLicked);
    connect(stopButton, &QPushButton::clicked,
            this, &TimerWidget::stopButtonClicked);

    timer->setSingleShot(true);
    timer->setInterval(timerValue);

    updateTimer->setInterval(1000);

    timer->start();
    updateTimer->start();

    connect(timer, &QTimer::timeout, this, &TimerWidget::timerTimeout);
    connect(updateTimer, &QTimer::timeout,
            this, &TimerWidget::updateTimerTimeout);

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

void TimerWidget::pauseResumeButtonCLicked()
{
    showMessageBox("Pause button clicked");
}

void TimerWidget::stopButtonClicked()
{
    showMessageBox("Stop button clicked");
}

void TimerWidget::timerTimeout()
{
    showMessageBox("Timer timeout");
}

void TimerWidget::updateTimerTimeout()
{
    if (timer->isActive())
        remainingTimeLabel->setText(QString::number(round(timer->remainingTime())));
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

void TimerWidget::showMessageBox(QString message)
{
    if (message.isEmpty())
        return;

    QMessageBox msg;
    msg.setText(message);
    msg.exec();
}
