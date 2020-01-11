#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QGroupBox>
#include<QLabel>
#include<QGridLayout>
#include<QCheckBox>
#include<ViewModule/GUIRequestHandler.h>
#include<ViewModule/GUISettings.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_AlexNet_clicked();
    void on_LoadButton_clicked();

    void on_DeleteButton_clicked();

    void on_ClassifyButton_clicked();

    void on_StopButton_clicked();

private:
    Ui::MainWindow *ui;
    QList<QImage> imageList;

    QImage hasRightSize(QImage image);
    void displayPreviews();
    QGroupBox *gridGroupBox;
    QGridLayout *gridLayout;

    QList<QLabel> imagesPreviews;
    GUIRequestHandler *guiRequestHandler;
    GUISettings *guiSettings;
};
#endif // MAINWINDOW_H
