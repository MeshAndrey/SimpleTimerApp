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

private slots:
    void addButtonClicked();
    void showHideWindow();

protected:
    void showEvent(QShowEvent* event);
    void hideEvent(QHideEvent* event);
    void closeEvent(QCloseEvent* event);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void replaceWidget(QWidget* oldWidget,
                       QWidget* newWidget);

    void showMessageBox(QString message);
    void showNotification(QString title, QString message);
};
#endif // MAINWINDOW_H
