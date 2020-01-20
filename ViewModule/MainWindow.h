#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QGroupBox>
#include<QLabel>
#include<QGridLayout>
#include<QCheckBox>
#include<ControllerModule/ViewController.h>
#include<ViewModule/GUISettings.h>
#include <DataModule/Result.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ViewController;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, ViewController* partner);
    ~MainWindow();

    void displayResults(vector<Result> results);
    void displayPrediction();

private slots:
    void on_AlexNet_clicked();
    void on_LoadButton_clicked();

    void on_DeleteButton_clicked();

    void on_ClassifyButton_clicked();

    void on_StopButton_clicked();



private:
    Ui::MainWindow *ui;
    QList<QImage> imageList;
    void displayPreviews();
    QGroupBox *gridGroupBox;
    QGridLayout *gridLayout;
    QList<QLabel> imagesPreviews;
    ViewController* viewController;
    GUISettings guiSettings;
    int resultsCounter;
};
#endif // MAINWINDOW_H
