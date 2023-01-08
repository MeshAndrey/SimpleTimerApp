#include "AlarmWidget.h"
#include "InputWidget.h"
#include "../MainWindow.h"

AlarmWidget::AlarmWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout * layout = new QHBoxLayout;
    stopButton = new QPushButton("Stop");

    layout->addWidget(new QLabel("Time is expired"));
    layout->addWidget(stopButton);

    connect(stopButton, &QPushButton::clicked,
            this,       &AlarmWidget::stopButtonClicked);

    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::red);

    this->setAutoFillBackground(true);
    this->setPalette(pal);

    alarmSound = new QSound(":/sounds/mixkit-urgent-simple-tone-loop-2976.wav");
    alarmSound->setLoops(QSound::Infinite);
    alarmSound->play();

    setLayout(layout);
}

void AlarmWidget::stopButtonClicked()
{
    alarmSound->stop();

    if (!this->close())
    {
        return;
    }

    ((MainWindow*)parent())->setCentralWidget(new InputWidget);
}
