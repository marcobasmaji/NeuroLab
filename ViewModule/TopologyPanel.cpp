#include "TopologyPanel.h"

TopologyPanel::TopologyPanel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TopologyPanel)
{
    ui->setupUi(this);
}
