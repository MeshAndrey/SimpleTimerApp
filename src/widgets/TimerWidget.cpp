#include "TimerWidget.h"
#include "AlarmWidget.h"
#include "InputWidget.h"

#include "../TimeUtils.h"

TimerWidget::TimerWidget(QString name, int timerValue,
                         QString shellCommand, bool autoStopAlarm,
                         QWidget *parent) : QWidget(parent)
{
    this->name = name;
    this->timerValue = timerValue;
    this->shellCommand = shellCommand;
    this->autoStopAlarm = autoStopAlarm;

    initWidgets();
    initConnections();
    initLayout();

    timer->setSingleShot(true);
    timer->setInterval(timerValue);

    updateTimer->setInterval(1000);

    timer->start();
    updateTimer->start();

    remainingTimeLabel->setText(TimeUtils::convertToReadable(
                                TimeUtils::round(timerValue)));
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
    QVBoxLayout * layout    = new QVBoxLayout;
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
            this,              &TimerWidget::pauseResumeButtonCLicked);
    connect(stopButton,        &QPushButton::clicked,
            this,              &TimerWidget::stopButtonClicked);

    connect(timer,             &QTimer::timeout,
            this,              &TimerWidget::timerTimeout);
    connect(updateTimer,       &QTimer::timeout,
            this,              &TimerWidget::updateTimerTimeout);
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

    auto mainWindow = getMainWindow();
    if (mainWindow == nullptr)
    {
        showMessageBox("MainWindow is nullptr");
        return;
    }

    mainWindow->replaceWidget(this, new InputWidget(static_cast<QWidget*>(this->parent())));
}

void TimerWidget::timerTimeout()
{
    auto mainWindow = getMainWindow();
    if (mainWindow == nullptr)
    {
        showMessageBox("MainWindow is nullptr");
        return;
    }

    if (!shellCommand.isEmpty())
    {
        if (!executeProcess(shellCommand))
        {
            const QString message = QString("Process \"%1\" not started")
                                        .arg(shellCommand);
            showMessageBox(message);
            mainWindow->showErrorNotification(name, message);
        }
        else
            mainWindow->showNotification(name, QString("\"%1\" was executed").arg(shellCommand));
    }

    if (autoStopAlarm)
    {
        mainWindow->replaceWidget(this,
                                  new InputWidget(static_cast<QWidget*>(this->parent())));
    }
    else
    {
        mainWindow->replaceWidget(this,
                                  new AlarmWidget(this->name,
                                                  this->timerValue,
                                                  static_cast<QWidget*>(this->parent())));
    }
}

bool TimerWidget::executeProcess(const QString program)
{
    if (program == "")
    {
        showMessageBox("Empty program param");
        return false;
    }

    QStringList splitedProgramCommand = program.split(" ");
    QString appName = splitedProgramCommand[0];
    splitedProgramCommand.removeAt(0);
    QStringList appArgs = splitedProgramCommand;

    QProcess* process = new QProcess;

    if (appArgs.length() == 0)
        process->start(appName, QStringList());
    else if (appArgs.length() == 1 && appArgs[0].isEmpty())
        process->start(appName, QStringList());
    else
        process->start(appName, appArgs);

    if (process->waitForStarted(3000)) // if ok
        return true;

    delete process;
    return false;
}

void TimerWidget::updateTimerTimeout()
{
    if (timer->isActive())
        remainingTimeLabel->setText(TimeUtils::convertToReadable(
                                    TimeUtils::round(timer->remainingTime())));
}

void TimerWidget::showMessageBox(const QString message)
{
    if (message.isEmpty())
        return;

    QMessageBox msg;
    msg.setText(message);
    msg.exec();
}

MainWindow* TimerWidget::getMainWindow()
{
    return static_cast<MainWindow*>(this->parent()->parent()->parent()->parent());
}
