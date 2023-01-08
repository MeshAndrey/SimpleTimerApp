#include "AlarmWidget.h"

AlarmWidget::AlarmWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout * layout = new QHBoxLayout;
    stopButton = new QPushButton("Stop");

    layout->addWidget(new QLabel("Time is expired"));
    layout->addWidget(stopButton);

    connect(stopButton, &QPushButton::clicked,
            this,       &AlarmWidget::stopButtonClicked);

    setLayout(layout);
}

void AlarmWidget::stopButtonClicked()
{

}
