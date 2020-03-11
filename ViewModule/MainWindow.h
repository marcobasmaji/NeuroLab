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
#include "TrainingPanel.h"

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
    void displayPrediction(string totalTime, string totalPowerConsumption, PredictionValues *cpu, PredictionValues *gpu, PredictionValues *mov1,
                           PredictionValues *mov2, PredictionValues *mov3, PredictionValues *mov4,
                           PredictionValues *fpga);
    void enableCheckbox(HardwareElement checkboxName);
    void disableHWCheckboxes();

private slots:
    void on_LoadButton_clicked();

    void on_DeleteButton_clicked();

    void on_ClassifyButton_clicked();

    void on_LPC_radio_button_clicked();

    void on_HP_radio_button_clicked();

    void on_HEE_radio_button_clicked();

    void on_AlexNet_radio_button_clicked();

    void on_NeuroLabNet_radio_button_clicked();


    void setEnabledModes(bool value);

    void on_SelectAllHardware_clicked();

    void on_Refresh_hardware_clicked();

    void on_previewArea_itemClicked(QListWidgetItem *item);

    void on_prediction_button_clicked();

    int createTab();

    //void on_comboBox_currentTextChanged(const QString &arg1);

    void on_Mov1_checkbox_stateChanged(int arg1);


    void on_Mov2_checkbox_stateChanged(int arg1);

    void on_Mov3_checkbox_stateChanged(int arg1);

    void on_Mov4_checkbox_stateChanged(int arg1);

    void on_CPU_checkbox_stateChanged(int arg1);

    void on_GPU_checkbox_stateChanged(int arg1);

    void on_FPGA_checkbox_stateChanged(int arg1);

    //void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_tabWidget_tabCloseRequested(int index);

    void on_classificationMenu_clicked();

    //void on_radioButton_clicked(bool checked);

    void on_GoogleNet_radio_button_clicked();

    void on_trainMenu_clicked();

    void on_load_dataset_button_clicked();

    void on_select_weights_button_clicked();

    void on_train_button_clicked();

    void on_train_tab_widget_tabCloseRequested(int index);

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
    void setPredictionValue(PredictionValues *values);
    void addHardwareToCombobox(HardwareElement element);
    void bindCheckbox(int arg, string hardwareElement, QString nameHardwareElement, int indexCombobox);
    void enableClassifyIfPossible();
    void showHwNotUsedMessage(PredictionValues* predictionValues);

    void setComboboxContent(list<HardwareElement> availableHardware);
    void checkSelectedHardware();
    void uncheckAllHardware();
    void selectAllHardware();
};
#endif // MAINWINDOW_H(imageToBeRemoved)
