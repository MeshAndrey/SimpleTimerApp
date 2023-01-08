#include "AlarmWidget.h"

AlarmWidget::AlarmWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout * layout = new QHBoxLayout;
    stopButton = new QPushButton("Stop");

    layout->addWidget(new QLabel("Time is expired"));
    layout->addWidget(stopButton);

    connect(stopButton, &QPushButton::clicked,
            this,       &AlarmWidget::stopButtonClicked);

    alarmSound = new QSound(":/sounds/mixkit-urgent-simple-tone-loop-2976.wav");
    alarmSound->setLoops(QSound::Infinite);
    alarmSound->play();

    setLayout(layout);
}

void AlarmWidget::stopButtonClicked()
{
    alarmSound->stop();
}
