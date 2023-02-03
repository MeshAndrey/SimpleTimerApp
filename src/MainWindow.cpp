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

}

MainWindow::~MainWindow()
{
}

