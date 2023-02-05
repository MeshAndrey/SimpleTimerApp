#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>

class InputWidget : public QWidget
{
    Q_OBJECT
private:
    QLineEdit *nameEdit  = nullptr,
              *hoursEdit = nullptr,
              *minsEdit  = nullptr,
              *secsEdit  = nullptr;
    QPushButton *clearButton  = nullptr,
                *okButton     = nullptr,
                *deleteButton = nullptr;

    void initWidgets();
    void initLayout();
    void initConnections();
    void showMessageBox(QString message);
    int getTimerValue();

public:
    explicit InputWidget(QWidget *parent = nullptr);

private slots:
    void buttonClicked();
    void clearButtonClicked();
    void okButtonClicked();
    void textEdited(const QString &text);
};

#endif // INPUTWIDGET_H
