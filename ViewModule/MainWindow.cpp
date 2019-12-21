#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // die connect functions werden in ui_mainwindow.h gebaut, wenn man das design tool nutzt.
    // aber ich habe hier bespiele geschrieben, damit jeder weiß wie das geht.

    connect(ui->LoadButton,SIGNAL(clicked(bool)), this,SLOT(on_LoadButton_clicked()));
    connect(ui->AlexNet,SIGNAL(clicked(bool)), this, SLOT(on_AlexNet_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_AlexNet_clicked() {
    // bespiel, um labels zu ändern
    ui->label_17->setText("safdsada");
}
void MainWindow::on_LoadButton_clicked()
{
    // when load is clicked. tab names should be changed
    QStringList filesList = QFileDialog::getOpenFileNames(ui->tab_7,
                                                            tr("Load Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug()<<"Images Loaded"<<endl;
    if (!filesList.isEmpty()){
           for(int i=0; i<filesList.length(); i++){
               QString file = filesList.at(i) ;
               QImage image(file);
               image = MainWindow::hasRightSize(image); // make sure its 224 * 224
               imageList.push_front(image);
               qDebug()<<"1 Image added to list"<<endl;

           }
           // should be somewhere else. this is just a test
           displayPreviews();
       }
    ui->ClassifyButton->setEnabled(true);

}

void MainWindow::on_DeleteButton_clicked()
{

}

void MainWindow::on_ClassifyButton_clicked()
{
    ui->tabWidget->setCurrentWidget(ui->tab_8);
    QWidget* newTab = new QWidget();
    newTab->setAccessibleName("hola");
    ui->tabWidget->addTab(newTab,tr("dasd"));

    ui->tabWidget->setCurrentWidget(newTab);

}

void MainWindow::on_StopButton_clicked()
{

}

// just a test. should be in image parser
QImage MainWindow::hasRightSize(QImage image ){
    if ( image.height() > 224 || image.width()> 224) {
        image = image.scaled(224, 224, Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    }
    return image;
}
// in another class. just a test
void MainWindow::displayPreviews() {
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



