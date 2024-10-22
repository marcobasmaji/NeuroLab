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
#include <QProgressDialog>
#include <QTimer>
#include "TrainingPanel.h"
#include <ControllerModule/ViewController.h>
#include <ControllerModule/HardwareElement.h>
#include "Worker.h"
#include <QFileDialog>
#include <QDebug>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QThread>

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
    void displayTrainingResults();
    void showErrorMessage(string mes);


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
    void on_prediction_button_clicked();
    void on_Mov1_checkbox_stateChanged(int arg1);
    void on_Mov2_checkbox_stateChanged(int arg1);
    void on_Mov3_checkbox_stateChanged(int arg1);
    void on_Mov4_checkbox_stateChanged(int arg1);
    void on_CPU_checkbox_stateChanged(int arg1);
    void on_GPU_checkbox_stateChanged(int arg1);
    void on_FPGA_checkbox_stateChanged(int arg1);
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_tabWidget_tabCloseRequested(int index);
    void on_classificationMenu_clicked();
    void on_GoogleNet_radio_button_clicked();
    void on_trainMenu_clicked();
    void on_load_dataset_button_clicked();
    void on_select_weights_button_clicked();
    void on_train_button_clicked();
    void on_train_tab_widget_tabCloseRequested(int index);
    void on_new_weights_dir_button_clicked();

public slots:
    void training_running();
    void stop_training();
    void errorString(QString message);

private:

    Ui::MainWindow *ui;
    ViewController* viewController;
    QList<QImage> imageList;
    bool displayPreview(const QIcon imageIcon, const QString imagePath);
    QList<QLabel> imagesPreviews;
    GUISettings guiSettings;
    int resultsCounter;
    void setPredictionValue(PredictionValues *values);
    void addHardwareToCombobox(HardwareElement element);
    void bindCheckbox(int arg, string hardwareElement, QString nameHardwareElement, int indexCombobox);
    void enableClassifyIfPossible();
    void showHwNotUsedMessage(PredictionValues* predictionValues);
    void setComboboxContent(list<HardwareElement> availableHardware);
    void checkSelectedHardware();
    void uncheckAllHardware();
    void selectAllHardware();
    void enableTrainIfPossible();
    void resetPalette();
    void setBackgroundImage(string imagePath);
    void setBackgroundImage();
    void setAllExistingHardwareUnchecked();
};
#endif // MAINWINDOW_H(imageToBeRemoved)
