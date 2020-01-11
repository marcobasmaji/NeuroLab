#include <ControllerModule/MasterController.h>
#include <QApplication>

int main(int argc, char *argv[]) {
    // schon gelöst ! XD
    // musste ich hier QApp machen und nicht un GUI builder
    // dort kriege ich eine Fehlermeldung, dass die QApp erstellt werden muss
    // before ein QWidget erstellt werden kann. Kann jemand versuchen QApp in GUIBuiler zu erstellen?
    // man muss so app immer übergeben.
    // mögliche Lösung https://stackoverflow.com/questions/23804238/must-construct-a-qapplication-before-a-qwidget-invalid-parameter-passed-to-c-r

    MasterController* masterController = new MasterController();

}
