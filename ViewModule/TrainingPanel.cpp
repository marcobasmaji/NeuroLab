#include "TrainingPanel.h"
#include <QFileDialog>

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
