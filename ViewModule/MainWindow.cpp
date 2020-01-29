#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <ControllerModule/ViewController.h>
#include <ControllerModule/HardwareElement.h>
#include <QFileDialog>
#include <QDebug>
#include <QScrollArea>
#include <QVBoxLayout>



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
        case MOV : ui->Mov1_checkbox->setCheckState(Qt::Checked);
            break;
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
        case MOV : ui->Mov1_checkbox->setCheckState(Qt::Unchecked);
            break;
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
    case MOV: ui->Mov1_checkbox->setEnabled(true);
        break;
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

void MainWindow::setEnabledModes(bool value)
{
    ui->LPC_radio_button->setEnabled(value);
    ui->HEE_radio_button->setEnabled(value);
    ui->HP_radio_button->setEnabled(value);

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
    if(guiSettings.getNn().compare("NeuroLab") == 0){
        return;
    }

    guiSettings.setMode("LowestPowerConsumption");
    bool hasMovidius = false;
    uncheckAll();
    for (HardwareElement hw : viewController->availableHardware) {
        if(hasMovidius){
            break;
        }
        switch(hw){
        case MOV : hasMovidius = true;
            this->disableHWCheckboxes();
            //this->enableCheckbox(MOV1);
            ui->Mov1_checkbox->setCheckState(Qt::Checked);
            guiSettings.setHardware({MOV});
            break;
        case MOV1 : hasMovidius = true;
            this->disableHWCheckboxes();
            //this->enableCheckbox(MOV1);
            ui->Mov1_checkbox->setCheckState(Qt::Checked);
            guiSettings.setHardware({MOV1});
            break;
        case MOV2 : hasMovidius = true;
            this->disableHWCheckboxes();
            //this->enableCheckbox(MOV2);
            ui->Mov2_checkbox->setCheckState(Qt::Checked);
            guiSettings.setHardware({MOV2});
            break;
        case MOV3: hasMovidius = true;
            this->disableHWCheckboxes();
            //this->enableCheckbox(MOV3);
            ui->Mov3_checkbox->setCheckState(Qt::Checked);
            guiSettings.setHardware({MOV3});
            break;
        case MOV4 : hasMovidius = true;
            this->disableHWCheckboxes();
            //this->enableCheckbox(MOV4);
            ui->Mov4_checkbox->setCheckState(Qt::Checked);
            guiSettings.setHardware({MOV4});
            break;
        default:    this->disableHWCheckboxes();
            //this->enableCheckbox(CPU);
            ui->CPU_checkbox->setCheckState(Qt::Checked);

        }
    }
}


void MainWindow::on_HP_radio_button_clicked()
{
    if(guiSettings.getNn().compare("NeuroLab")==0){
        return;
    }
    guiSettings.setMode("HighestPerformance");
    viewController->displayAvailableHardware();
    uncheckAll();

}

void MainWindow::on_HEE_radio_button_clicked()
{
    if(guiSettings.getNn().compare("NeuroLab")==0){
        return;
    }

    guiSettings.setMode("HighestEfficiency");
    viewController->displayAvailableHardware();
    uncheckAll();
}

void MainWindow::on_AlexNet_radio_button_clicked()
{
    guiSettings.setNn("AlexNet");
    setEnabledModes(true);
    viewController->displayAvailableHardware();
    uncheckAll();
}

void MainWindow::on_NeuroLabNet_radio_button_clicked()
{
    guiSettings.setNn("NeuroLab");
    uncheckAll();
    disableHWCheckboxes();
    setEnabledModes(false);
    ui->CPU_checkbox->setCheckState(Qt::Checked);

}

void MainWindow::displayPreview(const QIcon imageIcon, const QString imagePath) {

    QListWidgetItem *newItem;
    newItem  = new QListWidgetItem(imageIcon, imagePath);
    ui->previewArea->addItem(newItem);
}


void MainWindow::on_LoadButton_clicked()
{
    // when load is clicked. tab names should be changed
    QStringList filesList = QFileDialog::getOpenFileNames(this,
                                                          tr("Load Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug()<<"Images Loaded"<<endl;


    for(int i = 0; i < filesList.length() && !filesList.isEmpty(); i++){
        qDebug()<<"1 Image added to list: "<<filesList.at(i)<<endl;
        QIcon newIcon = QIcon(filesList.at(i));
        displayPreview(newIcon, filesList.at(i));
    }

    if(!filesList.isEmpty()){
        ui->ClassifyButton->setEnabled(true);
    }
    // turning Qstrings into std strings
    vector<string> vec;
    for(int i = 0; i < filesList.length(); i++) {
        vec.push_back(filesList.at(i).toStdString());
    }

    qDebug()<<"load in MainWindow"<<endl;
    this->viewController->updatePathList(vec);
    qDebug()<<"load"<<endl; // debug: working.
    this->guiSettings.setNrImages(filesList.size());
    //viewController->getPrediction(this->guiSettings);

}

void MainWindow::on_previewArea_itemClicked(QListWidgetItem *item)
{
    ui->DeleteButton->setEnabled(true);
    imageToBeRemoved = item;
}

void MainWindow::on_DeleteButton_clicked()
{
    if(imageToBeRemoved == NULL){
         //nothing to delete
        return;
    }
    string imagePath = imageToBeRemoved->text().toStdString();
    //remove image path stored in ViewController
    viewController->removeImage(imagePath);

    //remove image from main window
    int row = ui->previewArea->row(imageToBeRemoved);
    ui->previewArea->takeItem(row);

    //decrease total nr of images stored in guiSettings
    guiSettings.setNrImages(-1);

    imageToBeRemoved = NULL;
    ui->DeleteButton->setEnabled(false);

    //if there are no more images left, gray out classify button
    if(guiSettings.getNrImages() == 0){
        ui->ClassifyButton->setEnabled(false);
    }
}

void MainWindow::on_ClassifyButton_clicked()
{
    // calling classify in GUI
    this->viewController->handleClassifyRequest();

    //resultsCounter++;

}

void MainWindow::on_StopButton_clicked()
{

}

/*QLabel *createImageLabel(QString path) {
    QLabel *imageLabel = new QLabel();
    QPixmap image(path);
    imageLabel->setPixmap(image);
    imageLabel->setScaledContents(true);
    return imageLabel;
}*/

int MainWindow::createTab(){

    QVBoxLayout *layout = new QVBoxLayout();
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setLayout(layout);

    int currentIndex = ui->tabWidget->currentIndex();
    currentIndex++;
    ui->tabWidget->insertTab(currentIndex, scrollArea, "Results");
    ui->tabWidget->setCurrentIndex(currentIndex);

    return currentIndex;
}

void MainWindow::displayResults(vector<Result> results)
{
    qDebug()<<"Results size: "<<results.size()<<endl; // debug:

    //pair<string,float> p = results.back().getLabelsAndProb().front();
    //QString qstr = QString::fromStdString(p.first);
    // moving into a new results tab
    //QLabel *label = new QLabel(qstr);

    //int newTabIndex = createTab();
    QVBoxLayout *layout = new QVBoxLayout();
    QScrollArea *scrollArea = new QScrollArea(this);

    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setLayout(layout);

    int currentIndex = ui->tabWidget->currentIndex();
    currentIndex++;
    ui->tabWidget->insertTab(currentIndex, scrollArea, "Results");
    ui->tabWidget->setCurrentIndex(currentIndex);

    for(Result result : results){

        QString path = QString::fromStdString(result.getPath());
        QHBoxLayout *resultLayout = new QHBoxLayout;
        QVBoxLayout *labelsLayout = new QVBoxLayout;


        QLabel *imageLabel = new QLabel();
        QPixmap image(path);

        vector<pair<string, float>> labelsAndprob = result.getLabelsAndProb();
        for(int i = 0; i < 5; i++){
            int probPercent = (int) (labelsAndprob[i].second * 100);
            string prob = to_string(probPercent);
            QString label = QString::fromStdString(labelsAndprob[i].first + ' ' + prob + '%');
            labelsLayout->addWidget(new QLabel(label));
        }

        imageLabel->setPixmap(image);
        imageLabel->setScaledContents(true);
        resultLayout->addWidget(imageLabel);
        resultLayout->addLayout(labelsLayout);
        layout->addLayout(resultLayout);

    }
}

void MainWindow::on_SelectAllHardware_clicked()
{
    if(guiSettings.getNn() == "AlexNet"){
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
    if(guiSettings.getNn() == "NeuroLab"){
        on_NeuroLabNet_radio_button_clicked();
    }
}

void MainWindow::displayPredictionValues(double value, string valueType){

}

void MainWindow::displayPrediction(vector<double> timeConsumption, vector<double> powerConsumption, double bandwidth, double flops)
{
    displayPredictionValues(bandwidth, "Bandwith");
    displayPredictionValues(flops, "Flops");
    for(double time : timeConsumption){
        displayPredictionValues(time, "Time Consumption");
    }
    for(double power : powerConsumption){
        displayPredictionValues(power, "Power Consumption");
    }
}

void MainWindow::on_prediction_button_clicked()
{
    viewController->getPrediction(this->guiSettings);
}
