#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>

class InputWidget : public QWidget
{
    Q_OBJECT
private:
    QLineEdit *hoursEdit = nullptr,
              *minsEdit  = nullptr,
              *secsEdit  = nullptr;
    QPushButton *deleteButton = nullptr,
                *okButton     = nullptr;

    void initWidgets();
    void initLayout();
    void showMessageBox(QString message);
    int getTimerValue();

public:
    explicit InputWidget(QWidget *parent = nullptr);

private slots:
    void buttonClicked();
    void deleteButtonClicked();
    void okButtonClicked();
    void textEdited(const QString &text);
};

#endif // INPUTWIDGET_H
