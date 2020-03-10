#include "TrainingPanel.h"
#include <QFileDialog>
#include <QDebug>
TrainingPanel::TrainingPanel(QWidget *parent, GUISettings guiSet)
    : QMainWindow(parent)
    , ui(new Ui::TrainingPanel)
{
    ui->setupUi(this);
    this->guiSettings = guiSet;
}



void TrainingPanel::on_load_data_set_dir_clicked()
{
    QStringList filesList = QFileDialog::getOpenFileNames(this,
                                                          tr("Load Image"), "/home", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
    if(filesList.isEmpty()){
        return;
    }
}

void TrainingPanel::on_pushButton_clicked()
{
    qDebug()<<"endlich auf gerufen"<<endl;
}
