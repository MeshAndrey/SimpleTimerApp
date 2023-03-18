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
    shellCommandEdit = new QLineEdit;

    clearButton  = new QPushButton("Clear");
    okButton     = new QPushButton("Ok");
    deleteButton = new QPushButton("Delete");

    execShellCommandCheckBox = new QCheckBox("Exec shell command on alarm");
    autoStopAlarmCheckBox = new QCheckBox("Auto stop alarm");
}

void InputWidget::initLayout()
{
    QVBoxLayout *centralLayout    = new QVBoxLayout;

    QHBoxLayout *nameLayout       = new QHBoxLayout,
                *timeInputsLayout = new QHBoxLayout,
                *bottomHorLayout  = new QHBoxLayout;

    QGridLayout *gridLayout       = new QGridLayout;

    int buttonCounter = 0;
    for (int row = 0; row < 3 ; row++)
    {
        for (int column = 0; column < 3; column++)
        {
            QPushButton* btn = new QPushButton(QString::number(++buttonCounter));
            gridLayout->addWidget(btn, row, column);
            connect(btn,  &QPushButton::clicked,
                    this, &InputWidget::buttonClicked);
        }
    }

    QPushButton* zeroButton = new QPushButton("0");
    gridLayout->addWidget(zeroButton, 3, 1);

    connect(zeroButton, &QPushButton::clicked,
            this,       &InputWidget::buttonClicked);

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

    centralLayout->addLayout(nameLayout);
    centralLayout->addLayout(timeInputsLayout);
    centralLayout->addLayout(gridLayout);
    centralLayout->addWidget(execShellCommandCheckBox);
    centralLayout->addWidget(shellCommandEdit);
    centralLayout->addWidget(autoStopAlarmCheckBox);
    centralLayout->addLayout(bottomHorLayout);
    centralLayout->addWidget(deleteButton);

    shellCommandEdit->setVisible(false);
    autoStopAlarmCheckBox->setVisible(false);

    setMinimumSize(400, 250);
    setMaximumSize(400, 400);
    setLayout(centralLayout);
}

void InputWidget::initConnections()
{
    connect(hoursEdit, &QLineEdit::textEdited,
            this,      &InputWidget::textEdited);
    connect(minsEdit,  &QLineEdit::textEdited,
            this,      &InputWidget::textEdited);
    connect(secsEdit,  &QLineEdit::textEdited,
            this,      &InputWidget::textEdited);

    connect(clearButton,  &QPushButton::clicked,
            this,         &InputWidget::clearButtonClicked);
    connect(okButton,     &QPushButton::clicked,
            this,         &InputWidget::okButtonClicked);
    connect(deleteButton, &QPushButton::clicked,
            this,         &InputWidget::deleteButtonClicked);

    connect(execShellCommandCheckBox, &QCheckBox::stateChanged,
            this,                     &InputWidget::execShellCheckBoxStateChanged);
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

    if ( (secsEdit->text()  == "00" || secsEdit->text()  == "0") &&
         (minsEdit->text()  == "00" || minsEdit->text()  == "0") &&
         (hoursEdit->text() == "00" || hoursEdit->text() == "0") )
        return;

    if (secsEdit->text() == " "  || secsEdit->text()  == "  ")
        secsEdit->setText("");
    if (minsEdit->text() == " "  || minsEdit->text()  == "  ")
        minsEdit->setText("");
    if (hoursEdit->text() == " " || hoursEdit->text() == "  ")
        hoursEdit->setText("");

    int timerValue = getTimerValue();

    if (timerValue == 0)
        return;

    auto mainWindow = qobject_cast<MainWindow*>(this->parent()->parent()->parent()->parent());

    mainWindow->replaceWidget(this,
                              new TimerWidget(nameEdit->text(),
                                              timerValue,
                                              shellCommandEdit->text(),
                                              autoStopAlarmCheckBox->isChecked(),
                                              qobject_cast<QWidget*>(this->parent())));
}

void InputWidget::deleteButtonClicked()
{
    this->close();
}

int InputWidget::getTimerValue()
{
    if (secsEdit->text().isEmpty() &&
        minsEdit->text().isEmpty() &&
        hoursEdit->text().isEmpty())
        return 0;

    int s = 0, m = 0, h = 0;

    for (int i = 0; i < 3; i++)
    {
        bool ok = true;
        switch (i)
        {
            case 0:
                s = parseLineEdit(secsEdit, ok);  break;
            case 1:
                m = parseLineEdit(minsEdit, ok);  break;
            case 2:
                h = parseLineEdit(hoursEdit, ok); break;
        }
        if (!ok)
        {
            showMessageBox("Error to convert editLineWidget text to int");
            return 0;
        }
    }

    int timerValue = (s + m * 60 + h * 60 * 60) * 1000;

    return timerValue;
}

int InputWidget::parseLineEdit(QLineEdit* edit, bool &ok)
{
    return !edit->text().isEmpty() ? edit->text().toInt(&ok) : 0;
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
    QString digit = qobject_cast<QPushButton*>(sender())->text();

    if (hoursEdit->text().length() < 2)
    {
        hoursEdit->setText(hoursEdit->text() + digit);
    }
    else if (minsEdit->text().length() < 2)
    {
        minsEdit->setText(minsEdit->text() + digit);
    }
    else if (secsEdit->text().length() < 2)
    {
        secsEdit->setText(secsEdit->text() + digit);
    }
}

void InputWidget::textEdited(const QString &text)
{
    if (text.length() > 2)
    {
        qobject_cast<QLineEdit*>(sender())->setText(QStringRef(&text, 0, 2).toString());
    }
}

void InputWidget::execShellCheckBoxStateChanged(int state)
{
    bool visibility = false;

    if (state == Qt::Checked)
    {
        visibility = true;
    }
    else if (state == Qt::Unchecked)
    {
        visibility = false;
    }

    shellCommandEdit->setVisible(visibility);
    autoStopAlarmCheckBox->setVisible(visibility);
}

