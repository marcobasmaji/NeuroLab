#include "MainWindow.h"
#include "ui_MainWindow.h"
#include<ControllerModule/ViewController.h>
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
void MainWindow::on_AlexNet_clicked() {
    guiSettings.setNerualNet("ALEXNET");

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
    list<string> sl;
    for(int i = 0;i<filesList.length();i++) {
        sl.push_back(filesList.front().toStdString());
    }
    // loading paths in GUI
    qDebug()<<"load in MainWindow"<<endl;
    this->viewController->updatePathList(sl);
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
    // moving into a new results tab
    QWidget* newTab = new QWidget();
    newTab->setAccessibleName("result");
    ui->tabWidget->addTab(newTab,tr("Result"));
    ui->tabWidget->setCurrentWidget(newTab);
    //resultsCounter++;

}

void MainWindow::on_StopButton_clicked()
{
    // maybe find a way to stop the classify() method  in here
}

void MainWindow::displayPreviews() {
    // TODO !!

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



