#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSystemTrayIcon>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QVBoxLayout *leftLayout  = nullptr,
                *rightLayout = nullptr;
    QWidget *centralWidget = nullptr;
    QPushButton* addButton = nullptr;
    QTableView *tableView = nullptr;
    QSystemTrayIcon* trayIcon;
    QMenu*           trayIconMenu;
    void initMenuBar();
    void initTrayIcon();
    void showSettingsWindow();

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
    void showErrorNotification(QString title, QString message);
};
#endif // MAINWINDOW_H
