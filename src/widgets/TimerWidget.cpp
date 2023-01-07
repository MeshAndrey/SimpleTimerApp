#include "TimerWidget.h"

TimerWidget::TimerWidget(QWidget *parent) : QWidget(parent)
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
    timer->setInterval(3000);
    timer->start();

    connect(timer, &QTimer::timeout, this, &TimerWidget::timerTimeout);

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

void TimerWidget::showMessageBox(QString message)
{
    if (message.isEmpty())
        return;

    QMessageBox msg;
    msg.setText(message);
    msg.exec();
}
