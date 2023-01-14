#include "InputWidget.h"
#include "../MainWindow.h"
#include "TimerWidget.h"

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

    deleteButton = new QPushButton("Delete");
    okButton = new QPushButton("Ok");
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

    connect(hoursEdit, &QLineEdit::textEdited,
            this, &InputWidget::textEdited);
    connect(minsEdit, &QLineEdit::textEdited,
            this, &InputWidget::textEdited);
    connect(secsEdit, &QLineEdit::textEdited,
            this, &InputWidget::textEdited);

    bottomHorLayout->addWidget(deleteButton);
    bottomHorLayout->addWidget(okButton);

    connect(deleteButton, &QPushButton::clicked,
            this, &InputWidget::deleteButtonClicked);
    connect(okButton, &QPushButton::clicked,
            this, &InputWidget::okButtonClicked);

    verLayout->addLayout(topHorLayout);
    verLayout->addLayout(gridLayout);
    verLayout->addLayout(bottomHorLayout);

    setLayout(verLayout);
}

void InputWidget::deleteButtonClicked()
{
    secsEdit->setText("");
    minsEdit->setText("");
    hoursEdit->setText("");
}

void InputWidget::okButtonClicked()
{
    if (secsEdit->text().isEmpty() &&
        minsEdit->text().isEmpty() &&
        hoursEdit->text().isEmpty())
        return;

    if ( (secsEdit->text() == "00"  || secsEdit->text() == "0") &&
         (minsEdit->text() == "00"  || minsEdit->text() == "0") &&
         (hoursEdit->text() == "00" || hoursEdit->text() == "0") )
        return;

    int timerValue = getTimerValue();

    if (timerValue == 0)
        return;

    if (!this->close())
    {
        showMessageBox("Error to close input widget");
        return;
    }

    ((MainWindow*)parent())->setCentralWidget(new TimerWidget(timerValue));
}

int InputWidget::getTimerValue()
{
    if (secsEdit->text().isEmpty() &&
        minsEdit->text().isEmpty() &&
        hoursEdit->text().isEmpty())
        return 0;

    bool ok = false;

    int s = secsEdit->text().toInt(&ok);
    int m = minsEdit->text().toInt(&ok);
    int h = hoursEdit->text().toInt(&ok);

    if (!ok)
    {
        showMessageBox("Error to convert editLineWidget text to int");
        return 0;
    }

    int timerValue = (s + m * 60 + h * 60 * 60) * 1000;

    return timerValue;
}

void InputWidget::showMessageBox(QString message)
{
    if (message.isEmpty())
        return;

    QMessageBox msg;
    msg.setText(message);
    msg.exec();
}

void InputWidget::buttonClicked()
{
    QString digit = ((QPushButton*)sender())->text();

    if (secsEdit->text().length() < 2)
    {
        secsEdit->setText(secsEdit->text() + digit);
    }
    else if (minsEdit->text().length() < 2)
    {
        minsEdit->setText(minsEdit->text() + digit);
    }
    else if (hoursEdit->text().length() < 2)
    {
        hoursEdit->setText(hoursEdit->text() + digit);
    }
}

void InputWidget::textEdited(const QString &text)
{
    if (text.length() > 2)
    {
        ((QLineEdit*)sender())->setText(QStringRef(&text, 0, 2).toString());
    }
}

