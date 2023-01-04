#include "InputWidget.h"

InputWidget::InputWidget(QWidget *parent) : QWidget(parent)
{
    initWidgets();
    initLayout();
}

void InputWidget::initWidgets()
{
    hoursEdit = new QLineEdit;
    minsEdit  = new QLineEdit;
    secsEdit  = new QLineEdit;
}

void InputWidget::initLayout()
{
    QVBoxLayout *verLayout = new QVBoxLayout;
    QHBoxLayout *topHorLayout = new QHBoxLayout;
    QGridLayout *gridLayout = new QGridLayout;
    QHBoxLayout *bottomHorLayout = new QHBoxLayout;

    int buttonCounter = 0;
    for (int row = 0; row < 3 ; row++)
    {
        for (int column = 0; column < 3; column++)
        {
            QPushButton * btn = new QPushButton(QString::number(++buttonCounter));
            gridLayout->addWidget(btn, row, column);
            connect(btn, &QPushButton::clicked,
                    this, &InputWidget::buttonClicked);
        }
    }

    QPushButton* zeroButton = new QPushButton("0");
    gridLayout->addWidget(zeroButton, 3, 1);
    connect(zeroButton, &QPushButton::clicked,
            this, &InputWidget::buttonClicked);
    topHorLayout->addWidget(hoursEdit);
    topHorLayout->addWidget(new QLabel("H"));
    topHorLayout->addWidget(minsEdit);
    topHorLayout->addWidget(new QLabel("Min"));
    topHorLayout->addWidget(secsEdit);
    topHorLayout->addWidget(new QLabel("Sec"));

    bottomHorLayout->addWidget(new QPushButton("Delete"));
    bottomHorLayout->addWidget(new QPushButton("Ok"));

    verLayout->addLayout(topHorLayout);
    verLayout->addLayout(gridLayout);
    verLayout->addLayout(bottomHorLayout);

    setLayout(verLayout);
}

void InputWidget::buttonClicked()
{
    QMessageBox msg;
    msg.setText(((QPushButton*)sender())->text());
    msg.exec();
}

