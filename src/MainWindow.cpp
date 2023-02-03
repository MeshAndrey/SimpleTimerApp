#include "MainWindow.h"
#include "widgets/InputWidget.h"
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    layout = new QVBoxLayout;
    layout->addWidget(new InputWidget());

    addButton = new QPushButton("+");
    layout->addWidget(addButton);
    centralWidget = new QWidget;
    centralWidget->setLayout(layout);

    connect(addButton, &QPushButton::clicked,
            this, &MainWindow::addButtonClicked);

    QScrollArea *area = new QScrollArea;
    area->setWidgetResizable(true);
    area->verticalScrollBar()->setVisible(true);
    area->setWidget(centralWidget);

    setCentralWidget(area);
}

void MainWindow::addButtonClicked()
{
    layout->removeWidget(addButton);
    layout->addWidget(new InputWidget());
    layout->addWidget(addButton);
}

void MainWindow::replaceWidget(QWidget* oldWidget,
                               QWidget* newWidget)
{
    Q_UNUSED(oldWidget);
    Q_UNUSED(newWidget);
}

MainWindow::~MainWindow()
{
}

