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
    void showHideWindow();

protected:
    virtual void closeEvent(QCloseEvent*);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void replaceWidget(QWidget* oldWidget,
                       QWidget* newWidget);

    void showMessageBox(QString message);
};
#endif // MAINWINDOW_H
