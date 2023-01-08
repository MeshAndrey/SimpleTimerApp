#include "AlarmWidget.h"

AlarmWidget::AlarmWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout * layout = new QHBoxLayout;
    stopButton = new QPushButton("Stop");

    layout->addWidget(new QLabel("Time is expired"));
    layout->addWidget(stopButton);

    setLayout(layout);
}
