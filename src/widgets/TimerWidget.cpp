#include "TimerWidget.h"
#include "AlarmWidget.h"
#include "InputWidget.h"
#include "../MainWindow.h"

TimerWidget::TimerWidget(QString name, int timerValue, QWidget *parent) : QWidget(parent)
{
    this->name = name;
    this->timerValue = timerValue;

    initWidgets();
    initConnections();
    initLayout();

    timer->setSingleShot(true);
    timer->setInterval(timerValue);

    updateTimer->setInterval(1000);

    timer->start();
    updateTimer->start();

    remainingTimeLabel->setText(convertToReadable(round(timerValue)));
}

void TimerWidget::initWidgets()
{
    pauseResumeButton  = new QPushButton("Pause");
    stopButton         = new QPushButton("Stop");
    remainingTimeLabel = new QLabel("Text");

    timer       = new QTimer;
    updateTimer = new QTimer;
}

void TimerWidget::initLayout()
{
    QVBoxLayout * layout = new QVBoxLayout;
    QHBoxLayout * horLayout = new QHBoxLayout;

    horLayout->addWidget(pauseResumeButton);
    horLayout->addWidget(stopButton);

    layout->addWidget(new QLabel(name),   0, Qt::AlignCenter);
    layout->addWidget(remainingTimeLabel, 1, Qt::AlignCenter);
    layout->addLayout(horLayout);

    setLayout(layout);
}

void TimerWidget::initConnections()
{
    connect(pauseResumeButton, &QPushButton::clicked,
            this, &TimerWidget::pauseResumeButtonCLicked);
    connect(stopButton, &QPushButton::clicked,
            this, &TimerWidget::stopButtonClicked);

    connect(timer, &QTimer::timeout, this, &TimerWidget::timerTimeout);
    connect(updateTimer, &QTimer::timeout,
            this, &TimerWidget::updateTimerTimeout);
}

void TimerWidget::pauseResumeButtonCLicked()
{
    if (timer->isActive())
    {
        updateTimer->stop();
        timer->stop();

        pauseResumeButton->setText("Resume");
        return;
    }

    const QStringList splitedList = remainingTimeLabel->text().split(":");
    if (splitedList.isEmpty())
        return;

    const int lenght = splitedList.length();

    bool ok = false;

    const int s = splitedList[lenght - 1].toInt(&ok);
    const int m = lenght > 1 ? splitedList[lenght - 2].toInt(&ok) : 0;
    const int h = lenght > 2 ? splitedList[lenght - 3].toInt(&ok) : 0;

    if (!ok) return;

    timer->setInterval( (s + m * 60 + h * 60 * 60) * 1000 );
    updateTimer->setInterval(1000);

    timer->start();
    updateTimer->start();
    pauseResumeButton->setText("Stop");
}

void TimerWidget::stopButtonClicked()
{
    updateTimer->stop();
    timer->stop();

    this->close();

    ((MainWindow*)parent())->setCentralWidget(new InputWidget);
}

void TimerWidget::timerTimeout()
{
    this->close();

    ((MainWindow*)parent())->setCentralWidget(new AlarmWidget(this->name));
}

void TimerWidget::updateTimerTimeout()
{
    if (timer->isActive())
        remainingTimeLabel->setText(convertToReadable(round(timer->remainingTime())));
}

int TimerWidget::round(const int value)
{
    if (value == 0)
        return value; // zero
    if ((value >= 1000) && (value % 1000 == 0))
        return value; // already round

    if (((value % 1000) > 500) && ((value % 1000) <= 999))
    {
        return (value - (value % 1000) + 1000);
    }
    else if (((value % 1000) >= 1) && ((value % 1000) <= 500))
    {
        return (value - (value % 1000));
    }

    return value;
}

QString TimerWidget::convertToReadable(const int value)
{
    if (value < 0)
        return "Error value";

    const int h = value / (1000 * 60 * 60);                                 // hours
    const int m = (value - (h  * 1000 * 60 * 60)) / (1000 * 60);            // minutes
    const int s = (value - (h  * 1000 * 60 * 60) - (m * 1000 * 60)) / 1000; // seconds

    if (h > 0)
        return QString("%1:%2:%3").arg(makeTimeString(QString::number(h)),
                                       makeTimeString(QString::number(m)),
                                       makeTimeString(QString::number(s)));

    if (m > 0)
        return QString("%1:%2").arg(makeTimeString(QString::number(m)),
                                    makeTimeString(QString::number(s)));

    if (s > 0)
        return makeTimeString(QString::number(s));

    return "00";
}

QString TimerWidget::makeTimeString(QString time) // don't know how to name this shit
{
    if (time.isEmpty())
        return time;

    return time.length() == 2 ? time : time.prepend("0");
}

void TimerWidget::showMessageBox(const QString message)
{
    if (message.isEmpty())
        return;

    QMessageBox msg;
    msg.setText(message);
    msg.exec();
}
