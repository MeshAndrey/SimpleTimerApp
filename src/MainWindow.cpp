#include "MainWindow.h"
#include "widgets/InputWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setCentralWidget(new InputWidget());
}

MainWindow::~MainWindow()
{
}

