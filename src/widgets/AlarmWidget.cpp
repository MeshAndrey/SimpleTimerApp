#include "AlarmWidget.h"
#include "InputWidget.h"
#include "../MainWindow.h"

AlarmWidget::AlarmWidget(QString name, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout * centralLayout = new QVBoxLayout;
    QHBoxLayout * buttonLayout = new QHBoxLayout;
    repeatButton = new QPushButton("Retry");
    stopButton = new QPushButton("Stop");

    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(repeatButton);

    centralLayout->addWidget(new QLabel(name),              0, Qt::AlignCenter);
    centralLayout->addWidget(new QLabel("Time is expired"), 0, Qt::AlignCenter);   
    centralLayout->addLayout(buttonLayout);

    connect(stopButton, &QPushButton::clicked,
            this,       &AlarmWidget::stopButtonClicked);
    connect(repeatButton, &QPushButton::clicked,
            this,       &AlarmWidget::repeatButtonClicked);

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

void AlarmWidget::repeatButtonClicked()
{

}
