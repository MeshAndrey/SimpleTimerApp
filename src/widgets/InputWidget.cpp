#include "InputWidget.h"

InputWidget::InputWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout ();
    layout->addWidget(new QLabel("Placeholder"));
    setLayout(layout);
}
