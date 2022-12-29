#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>

class InputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InputWidget(QWidget *parent = nullptr);

private slots:
    void buttonClicked();
};

#endif // INPUTWIDGET_H
