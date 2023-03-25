#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>

#include "../MainWindow.h"

class InputWidget : public QWidget
{
    Q_OBJECT
private:
    QLineEdit *nameEdit  = nullptr,
              *hoursEdit = nullptr,
              *minsEdit  = nullptr,
              *secsEdit  = nullptr,
              *shellCommandEdit = nullptr;
    QPushButton *clearButton  = nullptr,
                *okButton     = nullptr,
                *deleteButton = nullptr;
    QCheckBox *execShellCommandCheckBox = nullptr,
              *autoStopAlarmCheckBox    = nullptr;

    void initWidgets();
    void initLayout();
    void initConnections();
    void showMessageBox(QString message);
    void insertToDB(QString name, QString h, QString m, QString s, QString timerTime, QString shellcmd);
    int getTimerValue();
    int parseLineEdit(QLineEdit* edit, bool &ok);
    MainWindow* getMainWindow();

public:
    explicit InputWidget(QWidget *parent = nullptr);

private slots:
    void buttonClicked();
    void clearButtonClicked();
    void okButtonClicked();
    void deleteButtonClicked();
    void textEdited(const QString &text);
    void execShellCheckBoxStateChanged(int state);
};

#endif // INPUTWIDGET_H
