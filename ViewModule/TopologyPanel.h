#ifndef TOPOLOGYPANEL_H
#define TOPOLOGYPANEL_H
#include "ui_TopologyPanel.h"
#include <QMainWindow>

class TopologyPanel : public QMainWindow
{
public:
    explicit TopologyPanel(QWidget *parent);
    Ui::TopologyPanel *ui;
};
#endif // TOPOLOGYPANEL_H
