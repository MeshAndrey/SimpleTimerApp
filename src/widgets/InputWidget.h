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

    void initWidgets();
    void initLayout();

public:
    explicit InputWidget(QWidget *parent = nullptr);

private slots:
    void buttonClicked();
};

#endif // INPUTWIDGET_H
