#ifndef WELCOMEPANEL_H
#define WELCOMEPANEL_H
#include "ui_TrainingPanel.h"
#include <QMainWindow>

class TrainingPanel : public QMainWindow
{
public:
    explicit TrainingPanel(QWidget *parent);
    Ui::TrainingPanel *ui;
};

#endif // WELCOMEPANEL_H
