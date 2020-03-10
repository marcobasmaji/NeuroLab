#ifndef WELCOMEPANEL_H
#define WELCOMEPANEL_H
#include "ui_TrainingPanel.h"
#include <QMainWindow>
#include "GUISettings.h"

class TrainingPanel : public QMainWindow
{
public:
    explicit TrainingPanel(QWidget *parent, GUISettings guiSettings);
    Ui::TrainingPanel *ui;
private slots:


    void on_load_data_set_dir_clicked();

    void on_pushButton_clicked();

private:
    GUISettings guiSettings;
};

#endif // WELCOMEPANEL_H
