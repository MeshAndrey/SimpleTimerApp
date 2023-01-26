#include "AlarmWidget.h"
#include "InputWidget.h"
#include "TimerWidget.h"
#include "../MainWindow.h"

AlarmWidget::AlarmWidget(QString name, int timerValue, QWidget *parent) : QWidget(parent)
{
    this->timerValue = timerValue;
    this->name = name;

    initWidgets();
    initLayout();

    connect(stopButton, &QPushButton::clicked,
            this,       &AlarmWidget::stopButtonClicked);
    connect(repeatButton, &QPushButton::clicked,
            this,       &AlarmWidget::repeatButtonClicked);

    alarmSound = new QSound(":/sounds/mixkit-urgent-simple-tone-loop-2976.wav");
    alarmSound->setLoops(QSound::Infinite);
    alarmSound->play();
}

void AlarmWidget::initWidgets()
{
    repeatButton = new QPushButton("Repeat");
    stopButton = new QPushButton("Stop");
}

void AlarmWidget::initLayout()
{
    QVBoxLayout * centralLayout = new QVBoxLayout;
    QHBoxLayout * buttonLayout = new QHBoxLayout;

    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(repeatButton);

    centralLayout->addWidget(new QLabel(name),              0, Qt::AlignCenter);
    centralLayout->addWidget(new QLabel("Time is expired"), 0, Qt::AlignCenter);
    centralLayout->addLayout(buttonLayout);

    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::red);

    this->setAutoFillBackground(true);
    this->setPalette(pal);
    setLayout(centralLayout);
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

void AlarmWidget::repeatButtonClicked()
{
    alarmSound->stop();

    if (!this->close())
    {
        return;
    }

    ((MainWindow*)parent())->setCentralWidget(
                new TimerWidget(this->name, this->timerValue));
}
