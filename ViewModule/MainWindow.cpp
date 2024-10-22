#include "MainWindow.h"
#include "ui_MainWindow.h"



MainWindow::MainWindow(QWidget *parent, ViewController *partner)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setBackgroundImage();
    this->viewController = partner;
    resultsCounter = 0;

    ui->tabWidget->hide();
    ui->HardwareOptions->hide();
    ui->NeuralNetOptions->hide();
    ui->ModeOptions->hide();
    ui->FPGA_checkbox->hide();
    ui->train_tab_widget->hide();
    ui->topologyMenu->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete viewController;
}

void MainWindow::uncheckAllHardware(){

    for (HardwareElement hw : viewController->availableHardware) {
        switch(hw){
        case MOV : if (ui->Mov1_checkbox->checkState() != Qt::CheckState::Unchecked) {
                ui->Mov1_checkbox->setCheckState(Qt::CheckState::Unchecked);}
            break;
        case MOV1 : if (ui->Mov1_checkbox->checkState() != Qt::CheckState::Unchecked) {
                ui->Mov1_checkbox->setCheckState(Qt::CheckState::Unchecked);}
            break;
        case MOV2 : if (ui->Mov2_checkbox->checkState() != Qt::CheckState::Unchecked) {
                ui->Mov2_checkbox->setCheckState(Qt::CheckState::Unchecked);}
            break;
        case MOV3 : if (ui->Mov3_checkbox->checkState() != Qt::CheckState::Unchecked) {
                ui->Mov3_checkbox->setCheckState(Qt::CheckState::Unchecked);}
            break;
        case MOV4 : if (ui->Mov4_checkbox->checkState() != Qt::CheckState::Unchecked) {
                ui->Mov4_checkbox->setCheckState(Qt::CheckState::Unchecked);}
            break;
        case CPU : if (ui->CPU_checkbox->checkState() != Qt::CheckState::Unchecked) {
                ui->CPU_checkbox->setCheckState(Qt::CheckState::Unchecked);}
            break;
        case GPU : if (ui->GPU_checkbox->checkState() != Qt::CheckState::Unchecked) {
                ui->GPU_checkbox->setCheckState(Qt::CheckState::Unchecked);}
            break;
        case FPGA : if (ui->FPGA_checkbox->checkState() != Qt::CheckState::Unchecked) {
                ui->FPGA_checkbox->setCheckState(Qt::CheckState::Unchecked);}
            break;
        }
    }
}

void MainWindow::setAllExistingHardwareUnchecked() {
    if (ui->Mov1_checkbox->checkState() != Qt::CheckState::Unchecked) {
        ui->Mov1_checkbox->setCheckState(Qt::CheckState::Unchecked);}
    if (ui->Mov1_checkbox->checkState() != Qt::CheckState::Unchecked) {
        ui->Mov1_checkbox->setCheckState(Qt::CheckState::Unchecked);}
    if (ui->Mov2_checkbox->checkState() != Qt::CheckState::Unchecked) {
        ui->Mov2_checkbox->setCheckState(Qt::CheckState::Unchecked);}
    if (ui->Mov3_checkbox->checkState() != Qt::CheckState::Unchecked) {
        ui->Mov3_checkbox->setCheckState(Qt::CheckState::Unchecked);}
    if (ui->Mov4_checkbox->checkState() != Qt::CheckState::Unchecked) {
        ui->Mov4_checkbox->setCheckState(Qt::CheckState::Unchecked);}
    if (ui->CPU_checkbox->checkState() != Qt::CheckState::Unchecked) {
        ui->CPU_checkbox->setCheckState(Qt::CheckState::Unchecked);}
    if (ui->GPU_checkbox->checkState() != Qt::CheckState::Unchecked) {
        ui->GPU_checkbox->setCheckState(Qt::CheckState::Unchecked);}
    if (ui->FPGA_checkbox->checkState() != Qt::CheckState::Unchecked) {
        ui->FPGA_checkbox->setCheckState(Qt::CheckState::Unchecked);}

}


void MainWindow::selectAllHardware() {
    if (guiSettings.getMode() == "LOWEST_POWER_CONSUMPTION") {
        return;
    }
    for (HardwareElement hw : viewController->availableHardware) {
        switch(hw){
        case MOV : if (ui->Mov1_checkbox->checkState() != Qt::CheckState::Checked) {
                ui->Mov1_checkbox->setCheckState(Qt::CheckState::Checked);
            }
            break;
        case MOV1 : if (ui->Mov1_checkbox->checkState() != Qt::CheckState::Checked) {
                ui->Mov1_checkbox->setCheckState(Qt::CheckState::Checked);}
            break;
        case MOV2 : if (ui->Mov2_checkbox->checkState() != Qt::CheckState::Checked) {
                ui->Mov2_checkbox->setCheckState(Qt::CheckState::Checked);}
            break;
        case MOV3 : if (ui->Mov3_checkbox->checkState() != Qt::CheckState::Checked) {
                ui->Mov3_checkbox->setCheckState(Qt::CheckState::Checked);}
            break;
        case MOV4 : if (ui->Mov4_checkbox->checkState() != Qt::CheckState::Checked) {
                ui->Mov4_checkbox->setCheckState(Qt::CheckState::Checked);}
            break;
        case CPU : if (ui->CPU_checkbox->checkState() != Qt::CheckState::Checked) {
                ui->CPU_checkbox->setCheckState(Qt::CheckState::Checked);}
            break;
        case GPU : if (ui->GPU_checkbox->checkState() != Qt::CheckState::Checked) {
                ui->GPU_checkbox->setCheckState(Qt::CheckState::Checked);}
            break;
        case FPGA : if (ui->FPGA_checkbox->checkState() != Qt::CheckState::Checked) {
                ui->FPGA_checkbox->setCheckState(Qt::CheckState::Checked);}
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
    guiSettings.setMode("LOWEST_POWER_CONSUMPTION");
    bool hasMovidius = false;
    uncheckAllHardware();
    for (HardwareElement hw : viewController->availableHardware) {
        switch(hw){
        case MOV1 : hasMovidius = true;
            this->disableHWCheckboxes();
            this->uncheckAllHardware();
            ui->Mov1_checkbox->setCheckState(Qt::Checked);
            break;
        case MOV2 : hasMovidius = true;
            this->disableHWCheckboxes();
            this->uncheckAllHardware();
            ui->Mov2_checkbox->setCheckState(Qt::Checked);
            break;
        case MOV3: hasMovidius = true;
            this->disableHWCheckboxes();
            this->uncheckAllHardware();
            ui->Mov3_checkbox->setCheckState(Qt::Checked);
            break;
        case MOV4 : hasMovidius = true;
            this->disableHWCheckboxes();
            this->uncheckAllHardware();
            ui->Mov4_checkbox->setCheckState(Qt::Checked);
            break;
        default:    this->disableHWCheckboxes();
            this->uncheckAllHardware();
            ui->CPU_checkbox->setCheckState(Qt::Checked);
            break;

        }
        if(hasMovidius){
            return;
        }
    }
}


void MainWindow::on_HP_radio_button_clicked()
{
    //    if(guiSettings.getNn().compare("NEUROLABNET")==0){
    //        return;
    //    }
    guiSettings.setMode("HIGHEST_PERFOMANCE");
    viewController->displayAvailableHardware();
    uncheckAllHardware();
    enableClassifyIfPossible();

}

void MainWindow::on_HEE_radio_button_clicked()
{
    guiSettings.setMode("HIGHEST_EFFICIENCY");
    viewController->displayAvailableHardware();
    uncheckAllHardware();
    enableClassifyIfPossible();
}

void MainWindow::on_AlexNet_radio_button_clicked()
{
    guiSettings.setNn("ALEXNET");
    setEnabledModes(true);
    viewController->displayAvailableHardware();
    uncheckAllHardware();
    enableClassifyIfPossible();
    if(guiSettings.getMode() == "LOWEST_POWER_CONSUMPTION"){
        on_LPC_radio_button_clicked();
    }
}

void MainWindow::on_NeuroLabNet_radio_button_clicked()
{
    guiSettings.setNn("NEUROLABNET");
    on_HP_radio_button_clicked();
    ui->HP_radio_button->toggle();
    uncheckAllHardware();
    disableHWCheckboxes();
    setEnabledModes(false);
    ui->CPU_checkbox->setCheckState(Qt::Checked);
    qDebug()<<QString::fromStdString(guiSettings.getNn())<<endl;
    for (string hw : guiSettings.getSelectedHardware()) {

        qDebug()<<QString::fromStdString(hw)<<endl;
    }
}

void MainWindow::on_GoogleNet_radio_button_clicked()
{
    guiSettings.setNn("GOOGLENET");
    setEnabledModes(true);
    viewController->displayAvailableHardware();
    uncheckAllHardware();
    if(guiSettings.getMode() == "LOWEST_POWER_CONSUMPTION"){
        on_LPC_radio_button_clicked();
    }
}

bool MainWindow::displayPreview(const QIcon imageIcon, const QString imagePath) {

    if(ui->previewArea->count() > 150){
        //ui->LoadButton->setEnabled(false);
        showErrorMessage("The maximum number of images was reached!");
        //return false;
    }
    QListWidgetItem *newItem;
    newItem  = new QListWidgetItem(imageIcon, imagePath);
    ui->previewArea->addItem(newItem);
    return true;
}


void MainWindow::on_LoadButton_clicked()
{
    // when load is clicked. tab names should be changed
    QStringList filesList = QFileDialog::getOpenFileNames(this,
                                                          tr("Load Image"), "/home", tr("Image Files (*.png *.jpg *.bmp *.jpeg *.JPG)"));
    if(filesList.isEmpty()){
        return;
    }

    qDebug()<<"Images Loaded"<<endl;

    int lenght = filesList.length();
    for(int i = 0; i < lenght && !filesList.isEmpty(); i++){
        qDebug()<<"1 Image added to list: "<<filesList.at(i)<<endl;
        QIcon newIcon = QIcon(filesList.at(i));
        bool res = displayPreview(newIcon, filesList.at(i));
        if(!res){
            lenght = i;
         }
    }
    // turning Qstrings into std strings
    vector<string> vec;
    for(int i = 0; i < lenght; i++) {
        vec.push_back(filesList.at(i).toStdString());
    }
    //load in mainwindow
    this->guiSettings.setPaths(vec);
    enableClassifyIfPossible();

}

void MainWindow::on_DeleteButton_clicked()
{
    QList<QListWidgetItem *> selectedItems = ui->previewArea->selectedItems();
    if(selectedItems.empty()){
        //nothing to delete
        return;
    }
    for (QListWidgetItem *imageToBeRemoved: selectedItems){
        string imagePath = imageToBeRemoved->text().toStdString();

        //remove image from main window
        int row = ui->previewArea->row(imageToBeRemoved);
        ui->previewArea->takeItem(row);

        //decrease total nr of images stored in guiSettings
        guiSettings.removePath(imagePath);
    }

    selectedItems.clear();

    //if there are no more images left, gray out classify button
    if(guiSettings.getPaths().empty()){
        ui->ClassifyButton->setEnabled(false);
    }

    if(ui->previewArea->count() <= 150){
        ui->LoadButton->setEnabled(true);
    }
}

void MainWindow::on_ClassifyButton_clicked()
{
    // calling classify in GUI
    qDebug()<<"MainWindow gui setting in classify"<<endl;
    for(string hw : guiSettings.getSelectedHardware()){
        qDebug()<<QString::fromStdString(hw)<<endl;
    }
    this->viewController->handleClassifyRequest(guiSettings);

}

void MainWindow::displayResults(vector<Result> results)
{
    qDebug()<<"Results size: "<<results.size()<<endl; // debug:

    QVBoxLayout *layout = new QVBoxLayout();
    QScrollArea *scrollArea = new QScrollArea(this);

    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    int newIndex = ui->tabWidget->count();
    ui->tabWidget->insertTab(newIndex, scrollArea, "Results");
    ui->tabWidget->setCurrentIndex(newIndex);


    for(Result result : results){

        QString path = QString::fromStdString(result.getPath());
        QHBoxLayout *resultLayout = new QHBoxLayout;
        QVBoxLayout *labelsLayout = new QVBoxLayout;


        QLabel *imageLabel = new QLabel();
        imageLabel->setFixedSize(400,200);
        QPixmap image(path);
        QPixmap scaledImage = image.scaledToHeight(200);

        vector<pair<string, float>> labelsAndprob = result.getLabelsAndProb();
        for(int i = 0; i < 5; i++){
            int probPercent = (int) (labelsAndprob[i].second * 100);
            string prob = to_string(probPercent);
            QString label = QString::fromStdString(labelsAndprob[i].first + ' ' + prob + '%');
            labelsLayout->addWidget(new QLabel(label));
        }

        imageLabel->setPixmap(scaledImage);
        resultLayout->addWidget(imageLabel);
        resultLayout->addLayout(labelsLayout);
        layout->addLayout(resultLayout);

        QWidget * horizontalLineWidget = new QWidget;
        horizontalLineWidget->setFixedHeight(2);
        horizontalLineWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        horizontalLineWidget->setStyleSheet(QString("background-color: #c0c0c0;"));
        layout->addWidget(horizontalLineWidget);

        QWidget *controlsRestrictorWidget = new QWidget();
        controlsRestrictorWidget->setLayout(layout);
        controlsRestrictorWidget->setMinimumHeight(results.size() * 210);
        controlsRestrictorWidget->setMaximumWidth(1000);
        scrollArea->setWidget(controlsRestrictorWidget);

    }
}

void MainWindow::on_SelectAllHardware_clicked()
{
    if(guiSettings.getNn() != "NEUROLABNET"){
        selectAllHardware();
        enableClassifyIfPossible();
    }
}

void MainWindow::on_Refresh_hardware_clicked()
{
    setAllExistingHardwareUnchecked();
    viewController->displayAvailableHardware();
    uncheckAllHardware();
    guiSettings.clearHardware();
    ui->hardwareNotUsed_label->clear();

    if(guiSettings.getMode() == "LOWEST_POWER_CONSUMPTION"){
        on_LPC_radio_button_clicked();
    }
    if(guiSettings.getNn() == "NEUROLABNET"){
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
        showHwNotUsedMessage(mov1);
        setPredictionValue(mov1);
        return;
    }
    if (ui->comboBox->currentText() == QString::fromStdString("Movidius 2")) {
        showHwNotUsedMessage(mov2);
        setPredictionValue(mov2);
        return;
    }
    if (ui->comboBox->currentText() == QString::fromStdString("Movidius 3")) {
        showHwNotUsedMessage(mov3);
        setPredictionValue(mov3);
        return ;
    }
    if (ui->comboBox->currentText() == QString::fromStdString("Movidius 4")) {
        showHwNotUsedMessage(mov4);
        setPredictionValue(mov4);
        return;
    }
    if (ui->comboBox->currentText() == QString::fromStdString("CPU")) {
        showHwNotUsedMessage(cpu);
        setPredictionValue(cpu);
        return;
    }
    if (ui->comboBox->currentText() == QString::fromStdString("GPU")) {
        showHwNotUsedMessage(gpu);
        setPredictionValue(gpu);
        return;
    }
    if (ui->comboBox->currentText() == QString::fromStdString("FPGA")){
        showHwNotUsedMessage(fpga);
        setPredictionValue(fpga);
        return;
    }

    ui->flops_value->clear();
    ui->bandwidth_value->clear();
    ui->powerCons_value->clear();
    ui->time_value->clear();

}

void MainWindow::showHwNotUsedMessage(PredictionValues* predictionValues) {
    if (! predictionValues->usedInDistribution()) {
        ui->hardwareNotUsed_label->setText("This hardware is not used for the classification");

        QFont font = ui->hardwareNotUsed_label->font();
        font.setPointSize(6);
        font.setBold(true);
        ui->hardwareNotUsed_label->setFont(font);
        ui->hardwareNotUsed_label->setStyleSheet("QLabel {color : red; }");
    } else {
        ui->hardwareNotUsed_label->clear();
    }
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
        enableClassifyIfPossible();
        qDebug()<<"checked" + nameHardwareElement<<endl;
    } else {
        qDebug()<<"UNchecked" + nameHardwareElement<<endl;
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
        on_Refresh_hardware_clicked();
        ui->NeuralNetOptions->hide();
        on_AlexNet_radio_button_clicked();
        ui->AlexNet_radio_button->toggle();
        ui->ModeOptions->hide();
        on_HP_radio_button_clicked();
        ui->HP_radio_button->toggle();
        ui->previewArea->clear();
        guiSettings.clearPaths();
        ui->totalTime_label->clear();
        ui->totalPower_label->clear();
        setBackgroundImage();
        ui->verticalWidget->show();
        index++;
        int count = ui->tabWidget->count();
        while(index < count){
            on_tabWidget_tabCloseRequested(1);
            index++;
        }
    } else {
        ui->tabWidget->removeTab(index);
    }
}

void MainWindow::on_classificationMenu_clicked()
{
    ui->tabWidget->show();
    ui->HardwareOptions->show();
    ui->NeuralNetOptions->show();
    ui->ModeOptions->show();
    ui->verticalWidget->hide();
    resetPalette();

}

void MainWindow::enableClassifyIfPossible() {
    if(!guiSettings.getPaths().empty() && !guiSettings.getSelectedHardware().empty()){
        ui->ClassifyButton->setEnabled(true);
    } else {
        ui->ClassifyButton->setEnabled(false);
    }
}

void MainWindow::on_trainMenu_clicked()
{

    ui->progress_bar->hide();
    ui->training_label->hide();
    ui->train_tab_widget->show();
    resetPalette();
}

void MainWindow::on_load_dataset_button_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Load Dataset"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    ui->dataset_path_label->setText(dir);
    guiSettings.setDataSetDirectory(dir.toStdString());
    enableTrainIfPossible();
}

void MainWindow::on_select_weights_button_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select weights folder"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    ui->weights_path_label->setText(dir);
    guiSettings.setWeightsDirectory(dir.toStdString());
    enableTrainIfPossible();

}
void MainWindow::on_train_button_clicked()
{
    ui->train_button->setEnabled(false);
    ui->train_tab_widget->setTabsClosable(false);
    ui->progress_bar->show();
    ui->training_label->show();

    QProgressBar *progress_bar;
    progress_bar = ui->progress_bar;
    progress_bar->setTextVisible(false);


    QLabel *progressLabel;
    progressLabel= ui->training_label;
    progressLabel->setText("Training is in progress. Please do not close the window!");


    //prepare for parallel computation
    QThread *thread = new QThread;
    QTimer *timer = new QTimer;
    Worker *worker = new Worker(guiSettings.getWeightsDirectory(), guiSettings.getDataSetDirectory(), guiSettings.getNewWeightsDirectory(), viewController);

    worker->moveToThread(thread);
    connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));

    connect(thread, SIGNAL(started()), timer, SLOT(start()));
    connect(thread, SIGNAL(finished()), timer, SLOT(stop()));
    connect(timer, SIGNAL(timeout()), this, SLOT(training_running()));
    connect(thread, SIGNAL(finished()), this, SLOT(stop_training()));

    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));


    thread->start();
    timer->start(1000);

}

void MainWindow::training_running()
{
    //cerr<<"update progressbar"<<endl;

    ui->progress_bar->setValue((ui->progress_bar->value() + 1) % 101);
}

void MainWindow::stop_training(){
    ui->progress_bar->setValue(100);
    ui->training_label->setText("Training successfull. Updated weights file saved in " +
                                QString::fromStdString(guiSettings.getNewWeightsDirectory()));
    ui->train_tab_widget->setTabsClosable(true);
}

void MainWindow::errorString(QString message){
    ui->progress_bar->setValue(0);
    ui->training_label->setText("Error");
    showErrorMessage(message.toStdString());
}


void MainWindow::enableTrainIfPossible() {

    if (!guiSettings.getWeightsDirectory().empty() && !guiSettings.getDataSetDirectory().empty()
            && !guiSettings.getNewWeightsDirectory().empty()){
        ui->train_button->setEnabled(true);
    };

}

void MainWindow::on_train_tab_widget_tabCloseRequested(int index)
{
    ui->train_tab_widget->hide();
    ui->dataset_path_label->clear();
    ui->new_weights_dir_label->clear();
    ui->weights_path_label->clear();
    setBackgroundImage();
}

void MainWindow::resetPalette(){
    QWidget t;
    this->setPalette(t.palette());
}

void MainWindow::setBackgroundImage(string imagePath){
    QPixmap bkgnd(QString::fromStdString(imagePath));
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}

void MainWindow::setBackgroundImage(){
    QPixmap bkgnd(":/ViewModule/welcome_panel.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
}


void MainWindow::showErrorMessage(string mes){
    TrainingPanel *popUp = new TrainingPanel(this);
    popUp->setErrorMessage(mes);
    popUp->show();
}

void MainWindow::on_new_weights_dir_button_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select folder for new train"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    ui->new_weights_dir_label->setText(dir);
    guiSettings.setNewWeightsDirectory(dir.toStdString());
    enableTrainIfPossible();
}
