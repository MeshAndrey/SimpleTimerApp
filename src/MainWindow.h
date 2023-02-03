#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QVBoxLayout *layout = nullptr;
    QWidget *centralWidget = nullptr;
    QPushButton* addButton = nullptr;

private slots:
    void addButtonClicked();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


};
#endif // MAINWINDOW_H
