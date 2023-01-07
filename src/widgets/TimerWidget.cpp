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
