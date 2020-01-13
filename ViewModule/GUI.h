#ifndef GUI_H
#define GUI_H
#include <ViewModule/MainWindow.h>

class ViewController;
class GUI
{
public:
    GUI(ViewController* partner);
    void drawGUI();
    void displayResults();
    void updatePredictions();
    void loadImages();
    void removeImages();
    void classifyImages();
private:
    ViewController *viewController;
};

#endif // GUI_H
