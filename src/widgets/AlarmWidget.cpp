#include "AlarmWidget.h"
#include "InputWidget.h"
#include "../MainWindow.h"

AlarmWidget::AlarmWidget(QString name, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout * centralLayout = new QVBoxLayout;
    stopButton = new QPushButton("Stop");

    centralLayout->addWidget(new QLabel(name),              0, Qt::AlignCenter);
    centralLayout->addWidget(new QLabel("Time is expired"), 0, Qt::AlignCenter);
    centralLayout->addWidget(stopButton,                    0, Qt::AlignCenter);

    connect(stopButton, &QPushButton::clicked,
            this,       &AlarmWidget::stopButtonClicked);

    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::red);

    this->setAutoFillBackground(true);
    this->setPalette(pal);

    alarmSound = new QSound(":/sounds/mixkit-urgent-simple-tone-loop-2976.wav");
    alarmSound->setLoops(QSound::Infinite);
    alarmSound->play();

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
