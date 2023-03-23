#include "MainWindow.h"
#include "widgets/InputWidget.h"
#include "widgets/SettingsWidget.h"
#include <QScrollArea>
#include <QCloseEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QVBoxLayout* leftLayout = new QVBoxLayout;
    rightLayout = new QVBoxLayout;
    QHBoxLayout* centralLayout = new QHBoxLayout;
    QWidget* centralWidget = new QWidget;
    QWidget* rightWidget = new QWidget;
    tableView = new QTableView;
    addButton = new QPushButton("+");

    leftLayout->addWidget(tableView);

    rightLayout->addWidget(new InputWidget(), 0, Qt::AlignCenter | Qt::AlignTop);
    rightLayout->addWidget(addButton, 1, Qt::AlignCenter | Qt::AlignTop);

    rightWidget->setLayout(rightLayout);

    connect(addButton, &QPushButton::clicked,
            this, &MainWindow::addButtonClicked);

    QScrollArea *area = new QScrollArea;
    area->setWidgetResizable(true);
    area->verticalScrollBar()->setVisible(true);
    area->horizontalScrollBar()->setVisible(false);
    area->setWidget(rightWidget);

    centralLayout->addLayout(leftLayout, 0);
    centralLayout->addWidget(area, 1);

    centralWidget->setLayout(centralLayout);

    setWindowIcon(QIcon(":/images/timer.png"));

    initTrayIcon();
    initMenuBar();
    initDB();

    setCentralWidget(centralWidget);
}

void MainWindow::initDB()
{
    if (!createDBConnection())
    {
        qApp->closeAllWindows();
    }

    model.setQuery("SELECT name "
                   "FROM timers "
                   "ORDER BY date DESC, time DESC;"
                  );

    if (model.lastError().isValid())
    {
        qDebug() << model.lastError();
    }

    tableView->setModel(&model);
}

void MainWindow::initMenuBar()
{
    QMenu* appMenu      = new QMenu("App");
    QMenu* timerMenu    = new QMenu("Timer");
    QMenu* settingsMenu = new QMenu("Settings");
    QMenu* helpMenu     = new QMenu("Help");

    this->menuBar()->addMenu(appMenu);
    this->menuBar()->addMenu(timerMenu);
    this->menuBar()->addMenu(settingsMenu);
    this->menuBar()->addMenu(helpMenu);

    QAction* showHideAction = new QAction("&Hide Application Window", this);
    showHideAction->setShortcut(Qt::CTRL + Qt::Key_H);

    QAction* quitAction = new QAction("&Quit", this);
    quitAction->setShortcut(Qt::CTRL + Qt::Key_Q);

    QAction* addTimerAction = new QAction("&Add timer", this);
    addTimerAction->setShortcut(Qt::CTRL + Qt::Key_E);

    QAction* settingsAction = new QAction("&Settings", this);
    settingsAction->setShortcut(Qt::CTRL + Qt::Key_T);

    connect(showHideAction, &QAction::triggered,
            this,           &MainWindow::showHideWindow);
    connect(quitAction,     &QAction::triggered,
            qApp,           &QApplication::quit);
    connect(addTimerAction, &QAction::triggered,
            this,           &MainWindow::addButtonClicked);
    connect(settingsAction, &QAction::triggered,
            this,           &MainWindow::showSettingsWindow);

    appMenu->addAction(showHideAction);
    appMenu->addAction(quitAction);
    timerMenu->addAction(addTimerAction);
    settingsMenu->addAction(settingsAction);
    helpMenu->addAction(tr("About Qt"), this, qApp->aboutQt);
}

void MainWindow::initTrayIcon()
{
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
}

void MainWindow::showSettingsWindow()
{
    SettingsWidget* settingsWidget = new SettingsWidget;
    settingsWidget->show();
}

void MainWindow::addButtonClicked()
{
    rightLayout->removeWidget(addButton);
    rightLayout->addWidget(new InputWidget(), 0, Qt::AlignCenter | Qt::AlignTop);
    rightLayout->addWidget(addButton, 1, Qt::AlignCenter | Qt::AlignTop);
}

void MainWindow::replaceWidget(QWidget* oldWidget,
                               QWidget* newWidget)
{
    if (!this->isVisible())
    {
        show();
    }

    auto old = rightLayout->replaceWidget(oldWidget,
                                          newWidget,
                                          Qt::FindDirectChildrenOnly)->widget();

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

void MainWindow::showNotification(QString title, QString message)
{
    trayIcon->showMessage(title, message, QSystemTrayIcon::Information, 5000);
}

void MainWindow::showErrorNotification(QString title, QString message)
{
    trayIcon->showMessage(title, message, QSystemTrayIcon::Critical, 5000);
}

void MainWindow::showHideWindow()
{
    setVisible(!isVisible());
}

void MainWindow::showEvent(QShowEvent* event)
{
    QMainWindow::showEvent(event);

    QSettings settings("MyCompany", "MyApp");
    this->restoreGeometry(settings.value("geometry").toByteArray());
    this->restoreState(settings.value("windowState").toByteArray());
}

void MainWindow::hideEvent(QHideEvent* event)
{
    QMainWindow::hideEvent(event);

    QSettings settings("MyCompany", "MyApp");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QMainWindow::closeEvent(event);

    if (this->isVisible()) {
        hide();
    }
    event->ignore();
}

bool MainWindow::createDBConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("timers");

    db.setUserName("timer"); // rewrite this // add to settings widget
    db.setHostName("timer");
    db.setPassword("timer");
    if (!db.open()) {
        qDebug() << "Cannot open database:" << db.lastError();
        return false;
    }

    if (db.tables().contains(QLatin1String("timers")))
    {
        return true;
    }

    QString   str  = "CREATE TABLE timers ( "
                         "date TEXT, "
                         "time TEXT, "
                         "name TEXT, "
                         "hours INTEGER NOT NULL, "
                         "minutes INTEGER NOT NULL, "
                         "seconds INTEGER NOT NULL, "
                         "shellcmd TEXT"
                     ");";

    QSqlQuery query = db.exec(str);

    if (!query.exec(str))
    {
        qDebug() << "Unable to create a table";
        return false;
    }

    return true;
}

MainWindow::~MainWindow()
{
}

