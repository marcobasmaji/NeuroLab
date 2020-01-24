#include "MainWindow.h"
#include "ui_MainWindow.h"
#include<ControllerModule/ViewController.h>
#include<ControllerModule/HardwareElement.h>
#include <QFileDialog>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent, ViewController *partner)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->viewController = partner;
    resultsCounter = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkAll(){
    for (HardwareElement hw : viewController->availableHardware) {
        switch(hw){
        case MOV1 : ui->Mov1_checkbox->setCheckState(Qt::Checked);
            break;
        case MOV2 : ui->Mov2_checkbox->setCheckState(Qt::Checked);
            break;
        case MOV3: ui->Mov3_checkbox->setCheckState(Qt::Checked);
            break;
        case MOV4 : ui->Mov4_checkbox->setCheckState(Qt::Checked);
            break;
        case CPU: ui->CPU_checkbox->setCheckState(Qt::Checked);
            break;
        case GPU: ui->GPU_checkbox->setCheckState(Qt::Checked);
            break;
        case FPGA: ui->FPGA_checkbox->setCheckState(Qt::Checked);
            break;
        }
    }
}
void MainWindow::uncheckAll(){
    for (HardwareElement hw : viewController->availableHardware) {
        switch(hw){
        case MOV1 : ui->Mov1_checkbox->setCheckState(Qt::Unchecked);
            break;
        case MOV2 : ui->Mov2_checkbox->setCheckState(Qt::Unchecked);
            break;
        case MOV3: ui->Mov3_checkbox->setCheckState(Qt::Unchecked);
            break;
        case MOV4 : ui->Mov4_checkbox->setCheckState(Qt::Unchecked);
            break;
        case CPU: ui->CPU_checkbox->setCheckState(Qt::Unchecked);
            break;
        case GPU: ui->GPU_checkbox->setCheckState(Qt::Unchecked);
            break;
        case FPGA: ui->FPGA_checkbox->setCheckState(Qt::Unchecked);
            break;
        }
    }
}

void MainWindow::enableCheckbox(HardwareElement checkboxName)
{
    switch(checkboxName){
    case MOV1: ui->Mov1_checkbox->setEnabled(true);
        break;
    case MOV2: ui->Mov2_checkbox->setEnabled(true);
        break;
    case MOV3: ui->Mov3_checkbox->setEnabled(true);
        break;
    case MOV4: ui->Mov4_checkbox->setEnabled(true);
        break;
    case CPU: ui->CPU_checkbox->setEnabled(true);
        break;
    case GPU: ui->GPU_checkbox->setEnabled(true);
        break;
    case FPGA: ui->FPGA_checkbox->setEnabled(true);
        break;
    }

}

void MainWindow::disableHWCheckboxes()
{
    ui->Mov1_checkbox->setEnabled(false);
    ui->Mov2_checkbox->setEnabled(false);
    ui->Mov3_checkbox->setEnabled(false);
    ui->Mov4_checkbox->setEnabled(false);
    ui->CPU_checkbox->setEnabled(false);
    ui->GPU_checkbox->setEnabled(false);
    ui->FPGA_checkbox->setEnabled(false);
}


void MainWindow::on_LPC_radio_button_clicked()
{
    guiSettings.setMode("LowestPowerConsumption");
    bool hasMovidius = false;
    uncheckAll();
    for (HardwareElement hw : viewController->availableHardware) {
        if(hasMovidius){
            break;
        }
        switch(hw){
        case MOV1 : hasMovidius = true;
            this->disableHWCheckboxes();
            //this->enableCheckbox(MOV1);
            ui->Mov1_checkbox->setCheckState(Qt::Checked);
            guiSettings.setSelectedHardware({MOV1});
            break;
        case MOV2 : hasMovidius = true;
            this->disableHWCheckboxes();
            //this->enableCheckbox(MOV2);
            ui->Mov2_checkbox->setCheckState(Qt::Checked);
            guiSettings.setSelectedHardware({MOV2});
            break;
        case MOV3: hasMovidius = true;
            this->disableHWCheckboxes();
            //this->enableCheckbox(MOV3);
            ui->Mov3_checkbox->setCheckState(Qt::Checked);
            guiSettings.setSelectedHardware({MOV3});
            break;
        case MOV4 : hasMovidius = true;
            this->disableHWCheckboxes();
            //this->enableCheckbox(MOV4);
            ui->Mov4_checkbox->setCheckState(Qt::Checked);
            guiSettings.setSelectedHardware({MOV4});
            break;
        default:    this->disableHWCheckboxes();
            //this->enableCheckbox(CPU);
            ui->CPU_checkbox->setCheckState(Qt::Checked);

        }
    }
}


void MainWindow::on_HP_radio_button_clicked()
{
    guiSettings.setMode("HighestPerformance");
    viewController->displayAvailableHardware();
    uncheckAll();

}

void MainWindow::on_HEE_radio_button_clicked()
{
    guiSettings.setMode("HighestEfficiency");
    viewController->displayAvailableHardware();
    uncheckAll();

}

void MainWindow::on_AlexNet_radio_button_clicked()
{
    guiSettings.setNerualNet("AlexNet");
    viewController->displayAvailableHardware();
    uncheckAll();
}

void MainWindow::on_NeuroLabNet_radio_button_clicked()
{
    guiSettings.setNerualNet("NeuroLab");
    uncheckAll();
    disableHWCheckboxes();
    ui->CPU_checkbox->setCheckState(Qt::Checked);

}

void MainWindow::on_LoadButton_clicked()
{
    // when load is clicked. tab names should be changed
    QStringList filesList = QFileDialog::getOpenFileNames(this,
                                                          tr("Load Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug()<<"Images Loaded"<<endl;
    if (!filesList.isEmpty()){
        for(int i=0; i<filesList.length(); i++){
            // QString file = filesList.at(i) ;
            // only files are needed.
            //QImage image(file);
            // image = MainWindow::hasRightSize(image); // make sure its 224 * 224
            //imageList.push_front(image);
            qDebug()<<"1 Image added to list"<<endl;
            //qDebug()<<file<<endl; // debug

        }
        // has nothiung to do with classifying.
        // Turn Path into Icons
        displayPreviews();
    }

    ui->ClassifyButton->setEnabled(true);
    // turning Qstrings into std strings
    vector<string> vec;
    for(int i = 0;i<filesList.length();i++) {
        vec.push_back(filesList.front().toStdString());
    }
    // loading paths in GUI
    qDebug()<<"load in MainWindow"<<endl;
    this->viewController->updatePathList(vec);
    qDebug()<<"load"<<endl; // debug: working.
    //this->guiSettings.setNumImages(filesList.lenght());
    viewController->getPrediction(this->guiSettings);

}

void MainWindow::on_DeleteButton_clicked()
{

}

void MainWindow::on_ClassifyButton_clicked()
{
    // calling classify in GUI
    this->viewController->handleClassifyRequest();

    //resultsCounter++;

}

void MainWindow::on_StopButton_clicked()
{
    // maybe find a way to stop the classify() method  in here
}

void MainWindow::displayPreviews() {
    // TODO !
    QImage image;
    image.pixel(2,2);

    // ideen zum resizen von bilder, um previews zu erstellen
    /*QWidget wgt;
    QPalette p = wgt.palette();
    QImage px("/home/mo/Pictures/Wallpapers/cat.jpg");
    p.setBrush(QPalette::Window, QBrush(px));
    wgt.setPalette(p);
    wgt.show();
    wgt.resize(500, 500);




    QWidget wgt2;
    QPalette p2 = wgt2.palette();
    QImage px2 = px.scaled(224, 224, Qt::KeepAspectRatio,Qt::SmoothTransformation);
    p2.setBrush(QPalette::Window, QBrush(px2));
    wgt2.setPalette(p2);
    wgt2.show();
    wgt2.resize(500, 500);

    px2.save("/home/mo/Pictures/Wallpapers/cat2.jpg");

    */

    gridLayout = new QGridLayout();
    gridLayout->setSpacing(2);

    ui->scrollArea->setLayout(gridLayout);
    QPixmap pixmap;
    for(QImage image : imageList) {
        pixmap.convertFromImage(image,Qt::AutoColor);        //Display preview
        //QIcon icon(pixmap);
        QLabel *label = new QLabel();
        label->setFixedSize(100,100);
        //QCheckBox *imageCheckBox = new QCheckBox();
        label->setPixmap(pixmap);
        //label->setPixmap(pixmap);


        ui->scrollArea->layout()->addWidget(label);



    }

}
void MainWindow::displayResults(vector<Result> results)
{
    pair<string,float> p = results.back().getLabelsAndProb().front();
    QString qstr = QString::fromStdString(p.first);
    // moving into a new results tab
    QLabel *label = new QLabel(qstr);
    ui->tabWidget->insertTab(1,label,"result");
    ui->tabWidget->setCurrentIndex(1);

}

void MainWindow::on_SelectAllHardware_clicked()
{
    if(guiSettings.getNerualNet() == "AlexNet"){
        checkAll();
    }
}

void MainWindow::on_Refresh_hardware_clicked()
{

    viewController->displayAvailableHardware();
    uncheckAll();
    if(guiSettings.getMode() == "LowestPowerConsumption"){
        on_LPC_radio_button_clicked();
    }
    if(guiSettings.getNerualNet() == "NeuroLab"){
        on_NeuroLabNet_radio_button_clicked();
    }
}
