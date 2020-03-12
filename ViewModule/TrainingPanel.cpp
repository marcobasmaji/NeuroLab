#include "TrainingPanel.h"
#include <QFileDialog>
#include <QDebug>
TrainingPanel::TrainingPanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrainingPanel)
{
    ui->setupUi(this);
    this->setFixedSize(380,120);
}



void TrainingPanel::setErrorMessage(string mes)
{
    ui->label->setText(QString::fromStdString(mes));
}


