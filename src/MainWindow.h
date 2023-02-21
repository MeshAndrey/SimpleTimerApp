#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSystemTrayIcon>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QVBoxLayout *layout = nullptr;
    QWidget *centralWidget = nullptr;
    QPushButton* addButton = nullptr;
    QSystemTrayIcon* trayIcon;
    QMenu*           trayIconMenu;
    void closeEvent(QCloseEvent* event);

private slots:
    void addButtonClicked();
    void showHideWindow();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void replaceWidget(QWidget* oldWidget,
                       QWidget* newWidget);

    void showMessageBox(QString message);
};
#endif // MAINWINDOW_H
