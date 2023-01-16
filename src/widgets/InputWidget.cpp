#include "InputWidget.h"
#include "../MainWindow.h"
#include "TimerWidget.h"

InputWidget::InputWidget(QWidget *parent) : QWidget(parent)
{
    initWidgets();
    initLayout();
    initConnections();
}

void InputWidget::initWidgets()
{
    nameEdit  = new QLineEdit;
    hoursEdit = new QLineEdit;
    minsEdit  = new QLineEdit;
    secsEdit  = new QLineEdit;

    clearButton = new QPushButton("Clear");
    okButton = new QPushButton("Ok");
}

void InputWidget::initLayout()
{
    QHBoxLayout *nameLayout = new QHBoxLayout;
    QVBoxLayout *verLayout = new QVBoxLayout;
    QHBoxLayout *timeInputsLayout = new QHBoxLayout;
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

    nameLayout->addWidget(new QLabel("Name:"));
    nameLayout->addWidget(nameEdit);

    timeInputsLayout->addWidget(hoursEdit);
    timeInputsLayout->addWidget(new QLabel("H"));
    timeInputsLayout->addWidget(minsEdit);
    timeInputsLayout->addWidget(new QLabel("Min"));
    timeInputsLayout->addWidget(secsEdit);
    timeInputsLayout->addWidget(new QLabel("Sec"));

    bottomHorLayout->addWidget(clearButton);
    bottomHorLayout->addWidget(okButton);

    verLayout->addLayout(nameLayout);
    verLayout->addLayout(timeInputsLayout);
    verLayout->addLayout(gridLayout);
    verLayout->addLayout(bottomHorLayout);

    setLayout(verLayout);
}

void InputWidget::initConnections()
{
    connect(hoursEdit, &QLineEdit::textEdited,
            this, &InputWidget::textEdited);
    connect(minsEdit, &QLineEdit::textEdited,
            this, &InputWidget::textEdited);
    connect(secsEdit, &QLineEdit::textEdited,
            this, &InputWidget::textEdited);

    connect(clearButton, &QPushButton::clicked,
            this, &InputWidget::clearButtonClicked);
    connect(okButton, &QPushButton::clicked,
            this, &InputWidget::okButtonClicked);
}

void InputWidget::clearButtonClicked()
{
    nameEdit->setText("");
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

    if (secsEdit->text() == " " || secsEdit->text() == "  ")
        secsEdit->setText("");
    if (minsEdit->text() == " " || minsEdit->text() == "  ")
        minsEdit->setText("");
    if (hoursEdit->text() == " " || hoursEdit->text() == "  ")
        hoursEdit->setText("");

    int timerValue = getTimerValue();

    if (timerValue == 0)
        return;

    if (!this->close())
    {
        showMessageBox("Error to close input widget");
        return;
    }

    ((MainWindow*)parent())->setCentralWidget(new TimerWidget(nameEdit->text(),
                                                              timerValue));
}

int InputWidget::getTimerValue()
{
    if (secsEdit->text().isEmpty() &&
        minsEdit->text().isEmpty() &&
        hoursEdit->text().isEmpty())
        return 0;

    bool ok = false;

    int s = !secsEdit->text().isEmpty()  ? secsEdit->text().toInt(&ok)  : 0;
    int m = !minsEdit->text().isEmpty()  ? minsEdit->text().toInt(&ok)  : 0;
    int h = !hoursEdit->text().isEmpty() ? hoursEdit->text().toInt(&ok) : 0;

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

