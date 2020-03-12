#ifndef WELCOMEPANEL_H
#define WELCOMEPANEL_H
#include "ui_TrainingPanel.h"
#include <QMainWindow>
#include "GUISettings.h"

class TrainingPanel : public QMainWindow
{
public:
    explicit TrainingPanel(QWidget *parent);
    Ui::TrainingPanel *ui;
    void setErrorMessage(string mes);
};

#endif // WELCOMEPANEL_H
