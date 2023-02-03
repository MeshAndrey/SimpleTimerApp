#include "MainWindow.h"
#include "widgets/InputWidget.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    layout = new QVBoxLayout;
    layout->addWidget(new InputWidget());
    layout->addWidget(new QPushButton("+"));
    centralWidget = new QWidget;
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);
}

void MainWindow::addButtonClicked()
{}

MainWindow::~MainWindow()
{
}

