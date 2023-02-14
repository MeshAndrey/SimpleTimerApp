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
    initConnections();

    updateTimer.setInterval(1 * 1000);
    elapsedTimer.start();

    updateTimer.start();

    alarmSound = new QSound(":/sounds/mixkit-urgent-simple-tone-loop-2976.wav");
    alarmSound->setLoops(QSound::Infinite);
    alarmSound->play();
}

void AlarmWidget::initWidgets()
{
    repeatButton = new QPushButton("Repeat");
    stopButton   = new QPushButton("Stop");
    timeLabel    = new QLabel;
}

void AlarmWidget::initLayout()
{
    QVBoxLayout* centralLayout = new QVBoxLayout;
    QHBoxLayout* buttonLayout  = new QHBoxLayout;

    buttonLayout->addWidget(repeatButton);
    buttonLayout->addWidget(stopButton);

    centralLayout->addWidget(new QLabel(name),              0, Qt::AlignCenter);
    centralLayout->addWidget(new QLabel("Time is expired"), 0, Qt::AlignCenter);
    centralLayout->addWidget(timeLabel,                     0, Qt::AlignCenter);
    centralLayout->addLayout(buttonLayout);

    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::red);

    this->setAutoFillBackground(true);
    this->setPalette(pal);
    setLayout(centralLayout);
}

void AlarmWidget::initConnections()
{
    connect(stopButton,   &QPushButton::clicked,
            this,         &AlarmWidget::stopButtonClicked);
    connect(repeatButton, &QPushButton::clicked,
            this,         &AlarmWidget::repeatButtonClicked);
    connect(&updateTimer, &QTimer::timeout,
            this,         &AlarmWidget::updateTimerTimeout);
}

void AlarmWidget::stopButtonClicked()
{
    alarmSound->stop();

    auto mainWindow = static_cast<MainWindow*>(this->parent()->parent()->parent()->parent());
    mainWindow->replaceWidget(this, new InputWidget(static_cast<QWidget*>(this->parent())));
}

void AlarmWidget::repeatButtonClicked()
{
    alarmSound->stop();

    auto mainWindow = static_cast<MainWindow*>(this->parent()->parent()->parent()->parent());
    mainWindow->replaceWidget(this,
                              new TimerWidget(this->name,
                                              this->timerValue,
                                              static_cast<QWidget*>(this->parent())));
}

void AlarmWidget::updateTimerTimeout()
{
    timeLabel->setText(convertToReadable(round(elapsedTimer.elapsed())).prepend("-- "));
}

int AlarmWidget::round(const int value)
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

QString AlarmWidget::convertToReadable(const int value)
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

QString AlarmWidget::makeTimeString(QString time) // don't know how to name this shit
{
    if (time.isEmpty())
        return time;

    return time.length() == 2 ? time : time.prepend("0");
}
