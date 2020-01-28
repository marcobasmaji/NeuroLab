#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QLabel>
#include <QGridLayout>
#include <QCheckBox>
#include <ControllerModule/ViewController.h>
#include <ViewModule/GUISettings.h>
#include <DataModule/Result.h>
#include <ControllerModule/HardwareElement.h>
#include <string>
#include <QListWidgetItem>

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
    void displayPrediction(vector<double> timeConsumption, vector<double> powerConsumption, double bandwidth, double flops);
    void enableCheckbox(HardwareElement checkboxName);
    void disableHWCheckboxes();

private slots:
    void on_LoadButton_clicked();

    void on_DeleteButton_clicked();

    void on_ClassifyButton_clicked();

    void on_StopButton_clicked();

    void on_LPC_radio_button_clicked();

    void on_HP_radio_button_clicked();

    void on_HEE_radio_button_clicked();

    void on_AlexNet_radio_button_clicked();

    void on_NeuroLabNet_radio_button_clicked();

    void checkAll();
    void uncheckAll();
    void setEnabledModes(bool value);

    void on_SelectAllHardware_clicked();

    void on_Refresh_hardware_clicked();

    void on_previewArea_itemClicked(QListWidgetItem *item);

    void on_prediction_button_clicked();

    int createTab();

    //void displayPredictionValues(double value, string valueType);



    private:

    Ui::MainWindow *ui;
    QList<QImage> imageList;
    void displayPreview(const QIcon imageIcon, const QString imagePath);
    QGroupBox *gridGroupBox;
    QGridLayout *gridLayout;
    QList<QLabel> imagesPreviews;
    ViewController* viewController;
    GUISettings guiSettings;
    int resultsCounter;
    QListWidgetItem *imageToBeRemoved;
};
#endif // MAINWINDOW_H(imageToBeRemoved)
