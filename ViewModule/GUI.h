#ifndef GUI_H
#define GUI_H
#include <QApplication>
#include <string>
#include <iostream>
using namespace std;
class ViewController;
class GUI
{
public:
    GUI(ViewController* partner);
    void loadPaths(list<string> paths);
    void drawGUI();
    void displayResults();
    void updatePredictions();
    void removeImages();
    void classifyImages();
private:
    ViewController *viewController;
};

#endif // GUI_H
