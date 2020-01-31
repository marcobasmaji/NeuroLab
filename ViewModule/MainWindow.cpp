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

    ui->tabWidget->hide();
    ui->HardwareOptions->hide();
    ui->NeuralNetOptions->hide();
    ui->ModeOptions->hide();
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
            guiSettings.setSelectedHardware({MOV});
            break;
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
    if(guiSettings.getNn().compare("NEUROLAB")==0){
        return;
    }
    guiSettings.setMode("HIGHEST_EFFICIENCY");
    viewController->displayAvailableHardware();
    uncheckAll();

}

void MainWindow::on_HEE_radio_button_clicked()
{
    if(guiSettings.getNn().compare("NEUROLAB")==0){
        return;
    }

    guiSettings.setMode("HIGHEST_EFFICIENCY");
    viewController->displayAvailableHardware();
    uncheckAll();
}

void MainWindow::on_AlexNet_radio_button_clicked()
{
    guiSettings.setNn("ALEXNET");
    setEnabledModes(true);
    viewController->displayAvailableHardware();
    uncheckAll();
}

void MainWindow::on_NeuroLabNet_radio_button_clicked()
{
    guiSettings.setNn("NEUROLAB");
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
                                                          tr("Load Image"), "/home", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
    if(filesList.isEmpty()){
        return;
    }

    qDebug()<<"Images Loaded"<<endl;


    for(int i = 0; i < filesList.length() && !filesList.isEmpty(); i++){
        qDebug()<<"1 Image added to list: "<<filesList.at(i)<<endl;
        QIcon newIcon = QIcon(filesList.at(i));
        displayPreview(newIcon, filesList.at(i));
    }

    if(!filesList.isEmpty() && !guiSettings.getSelectedHardware().empty()){
        ui->ClassifyButton->setEnabled(true);
    }
    // turning Qstrings into std strings
    vector<string> vec;
    for(int i = 0; i < filesList.length(); i++) {
        vec.push_back(filesList.at(i).toStdString());
    }
    //load in mainwindow
    this->guiSettings.setPaths(vec);
    //this->viewController->updatePathList(guiSettings.getPaths());
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
    //viewController->removeImage(imagePath);

    //remove image from main window
    int row = ui->previewArea->row(imageToBeRemoved);
    ui->previewArea->takeItem(row);

    //decrease total nr of images stored in guiSettings
    guiSettings.removePath(imagePath);
    //viewController->updatePathList(guiSettings.getPaths());

    imageToBeRemoved = NULL;
    ui->DeleteButton->setEnabled(false);

    //if there are no more images left, gray out classify button
    if(guiSettings.getPaths().empty()){
        ui->ClassifyButton->setEnabled(false);
    }
}

void MainWindow::on_ClassifyButton_clicked()
{
    // calling classify in GUI
    this->viewController->handleClassifyRequest(guiSettings);

}

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

    QWidget *controlsRestrictorWidget = new QWidget();
    controlsRestrictorWidget->setLayout(layout);
    controlsRestrictorWidget->setMinimumHeight(results.size() * 200);


    int currentIndex = ui->tabWidget->currentIndex();
    currentIndex++;
    ui->tabWidget->insertTab(currentIndex, scrollArea, "Results");
    ui->tabWidget->setCurrentIndex(currentIndex);


    for(Result result : results){

        QString path = QString::fromStdString(result.getPath());
        QHBoxLayout *resultLayout = new QHBoxLayout;
        QVBoxLayout *labelsLayout = new QVBoxLayout;


        QLabel *imageLabel = new QLabel();
        imageLabel->setMaximumWidth(200);
        imageLabel->setMaximumHeight(200);
        QPixmap image(path);
        image.scaled(200, 200, Qt::KeepAspectRatio);



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
        resultLayout->addSpacing(5);
        resultLayout->addLayout(labelsLayout);
        layout->addLayout(resultLayout);
        scrollArea->setWidget(controlsRestrictorWidget);

    }
}

void MainWindow::on_SelectAllHardware_clicked()
{
    if(guiSettings.getNn() == "ALEXNET"){
        checkAll();
    }
}

void MainWindow::on_Refresh_hardware_clicked()
{

    viewController->displayAvailableHardware();
    guiSettings.clearHardware();
    uncheckAll();
    if(guiSettings.getMode() == "LOWEST_POWER_CONSUMPTION"){
        on_LPC_radio_button_clicked();
    }
    if(guiSettings.getNn() == "NEUROLAB"){
        on_NeuroLabNet_radio_button_clicked();
    }
}


void MainWindow::setPredictionValue(PredictionValues *values){
    ui->flops_value->setText(QString::fromStdString(values->flops));
    ui->bandwidth_value->setText(QString::fromStdString(values->bandwidth));
    ui->powerCons_value->setText(QString::fromStdString(values->power_consumption));
    ui->time_value->setText(QString::fromStdString(values->time));
}

void MainWindow::displayPrediction(string totalTime, string totalPowerConsumption, PredictionValues *cpu, PredictionValues *gpu, PredictionValues *mov1,
                                   PredictionValues *mov2, PredictionValues *mov3, PredictionValues *mov4,
                                   PredictionValues *fpga)
{
    ui->totalTime_label->setText(QString::fromStdString(totalTime));
    ui->totalPower_label->setText(QString::fromStdString(totalPowerConsumption));
    if (ui->comboBox->currentText() == QString::fromStdString("Movidius 1")) {
        setPredictionValue(mov1);
        return;
    }
     if (ui->comboBox->currentText() == QString::fromStdString("Movidius 2")) {
        setPredictionValue(mov2);
        return;
     }
     if (ui->comboBox->currentText() == QString::fromStdString("Movidius 3")) {
        setPredictionValue(mov3);
        return ;
     }
     if (ui->comboBox->currentText() == QString::fromStdString("Movidius 4")) {
        setPredictionValue(mov4);
        return;
     }
     if (ui->comboBox->currentText() == QString::fromStdString("CPU")) {
        setPredictionValue(cpu);
        return;
     }
     if (ui->comboBox->currentText() == QString::fromStdString("GPU")) {
        setPredictionValue(gpu);
        return;
    }
     if (ui->comboBox->currentText() == QString::fromStdString("FPGA")){
        setPredictionValue(fpga);
        return;
    }

        ui->flops_value->clear();
        ui->bandwidth_value->clear();
        ui->powerCons_value->clear();
        ui->time_value->clear();

}

void MainWindow::on_prediction_button_clicked()
{
    viewController->getPrediction(this->guiSettings);
}

void MainWindow::setComboboxContent(list<HardwareElement> availableHardware) {
    for (HardwareElement element : availableHardware) {
        addHardwareToCombobox(element);
    }
}

void MainWindow::addHardwareToCombobox(HardwareElement element) {
    ui->comboBox->addItem("element");
}

void MainWindow::checkSelectedHardware() {
    if (ui->Mov1_checkbox->checkState() == Qt::Checked) {
        guiSettings.selectHardwareElement("MYRIAD.1");
    }
    if (ui->Mov2_checkbox->checkState() == Qt::Checked) {
        guiSettings.selectHardwareElement("MYRIAD.2");
    }
    if (ui->Mov3_checkbox->checkState() == Qt::Checked) {
        guiSettings.selectHardwareElement("MYRIAD.3");
    }
    if (ui->Mov4_checkbox->checkState() == Qt::Checked) {
        guiSettings.selectHardwareElement("MYRIAD.4");
    }
    if (ui->CPU_checkbox->checkState() == Qt::Checked) {
        guiSettings.selectHardwareElement("CPU");
    }
    if (ui->GPU_checkbox->checkState() == Qt::Checked) {
        guiSettings.selectHardwareElement("GPU");
    }
    if (ui->FPGA_checkbox->checkState() == Qt::Checked) {
        guiSettings.selectHardwareElement("FPGA");
    }

}


void MainWindow::bindCheckbox(int arg, string hardwareElement, QString nameHardwareElement, int indexCombobox) {
    if (arg == 2) {
        guiSettings.selectHardwareElement(hardwareElement);
        ui->comboBox->insertItem(indexCombobox, nameHardwareElement);
        ui->prediction_button->setEnabled(true);
        ui->ClassifyButton->setEnabled(true);
    } else {
        ui->comboBox->setCurrentIndex(0);
        guiSettings.unselectHardwareElement(hardwareElement);
        int indexRemove = ui->comboBox->findText(nameHardwareElement);
        ui->comboBox->removeItem(indexRemove);
        if (guiSettings.getSelectedHardware().empty()) {
            ui->prediction_button->setEnabled(false);
            ui->ClassifyButton->setEnabled(false);
        }
    }
}

void MainWindow::on_Mov1_checkbox_stateChanged(int arg1)
{
    bindCheckbox(arg1, "MYRIAD.1", "Movidius 1", 1);
}

void MainWindow::on_Mov2_checkbox_stateChanged(int arg1)
{
    bindCheckbox(arg1, "MYRIAD.2", "Movidius 2", 2);
}

void MainWindow::on_Mov3_checkbox_stateChanged(int arg1)
{
    bindCheckbox(arg1, "MYRIAD.3", "Movidius 3", 3);
}

void MainWindow::on_Mov4_checkbox_stateChanged(int arg1)
{
    bindCheckbox(arg1, "MYRIAD.4", "Movidius 4", 4);
}

void MainWindow::on_CPU_checkbox_stateChanged(int arg1)
{
    bindCheckbox(arg1, "CPU", "CPU", 2);
}

void MainWindow::on_GPU_checkbox_stateChanged(int arg1)
{
    bindCheckbox(arg1, "GPU", "GPU", 6);
}

void MainWindow::on_FPGA_checkbox_stateChanged(int arg1)
{
    bindCheckbox(arg1, "FPGA", "FPGA", 7);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 1: ;// show for mov1;
        ui->prediction_button->setEnabled(true);
        break;
    case 2: ;
        ui->prediction_button->setEnabled(true);
        break;
    case 3: ;
        ui->prediction_button->setEnabled(true);
        break;
    case 4: ;
        ui->prediction_button->setEnabled(true);
        break;
    case 5: ;
        ui->prediction_button->setEnabled(true);
        break;
    case 6: ;
        ui->prediction_button->setEnabled(true);
        break;
    case 7: ;
        ui->prediction_button->setEnabled(true);
        break;
    default: ;
        ui->prediction_button->setEnabled(false);
        break;
    }
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Select hardware") {
        ui->flops_value->clear();
        ui->bandwidth_value->clear();
        ui->powerCons_value->clear();
        ui->time_value->clear();
    }
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (index == 0) {
        ui->tabWidget->hide();
        ui->HardwareOptions->hide();
        ui->NeuralNetOptions->hide();
        ui->ModeOptions->hide();

    } else {
    ui->tabWidget->removeTab(index);}
}

void MainWindow::on_classificationMenu_clicked()
{
    ui->tabWidget->show();
    ui->HardwareOptions->show();
    ui->NeuralNetOptions->show();
    ui->ModeOptions->show();
}
