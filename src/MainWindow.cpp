#include "MainWindow.h"
#include "widgets/InputWidget.h"


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

    setCentralWidget(centralWidget);
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

