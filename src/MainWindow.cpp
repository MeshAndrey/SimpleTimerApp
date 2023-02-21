#include "MainWindow.h"
#include "widgets/InputWidget.h"
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    layout = new QVBoxLayout;
    layout->addWidget(new InputWidget(), 0, Qt::AlignCenter | Qt::AlignTop);

    addButton = new QPushButton("+");
    layout->addWidget(addButton, 1, Qt::AlignCenter | Qt::AlignTop);
    centralWidget = new QWidget;
    centralWidget->setLayout(layout);

    connect(addButton, &QPushButton::clicked,
            this, &MainWindow::addButtonClicked);

    QScrollArea *area = new QScrollArea;
    area->setWidgetResizable(true);
    area->verticalScrollBar()->setVisible(true);
    area->horizontalScrollBar()->setVisible(false);
    area->setWidget(centralWidget);

    setWindowIcon(QIcon(":/images/timer.png"));

    QAction* showHideAction =
        new QAction("&Show/Hide Application Window", this);

    connect(showHideAction, &QAction::triggered,
            this,           &MainWindow::showHideWindow);

    QAction* quitAction = new QAction("&Quit", this);
    connect(quitAction, &QAction::triggered,
            qApp,       &QApplication::quit);

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(showHideAction);
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setToolTip("Timer app");
    trayIcon->setIcon(QIcon(":/images/timer.png"));
    trayIcon->show();

    setCentralWidget(area);
}

void MainWindow::addButtonClicked()
{
    layout->removeWidget(addButton);
    layout->addWidget(new InputWidget(), 0, Qt::AlignCenter | Qt::AlignTop);
    layout->addWidget(addButton, 1, Qt::AlignCenter | Qt::AlignTop);
}

void MainWindow::replaceWidget(QWidget* oldWidget,
                               QWidget* newWidget)
{
    auto old = layout->replaceWidget(oldWidget, newWidget, Qt::FindDirectChildrenOnly)->widget();

    if (old == nullptr)
    {
        showMessageBox("replace widget returned nullptr");
        return;
    }

    if (!old->close())
    {
        showMessageBox("error closing old widget");
        return;
    }

    delete old;
}


void MainWindow::showMessageBox(QString message)
{
    if (message.isEmpty())
        return;

    QMessageBox msg;
    msg.setText(message);
    msg.exec();
}

void MainWindow::showHideWindow()
{
    setVisible(!isVisible());
}

void MainWindow::closeEvent(QCloseEvent*)
{
    if (trayIcon->isVisible()) {
        hide();
    }
}

MainWindow::~MainWindow()
{
}

