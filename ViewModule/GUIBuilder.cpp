#include "GUIBuilder.h"
#include <QApplication>

GUIBuilder::GUIBuilder()
{
    // dummy arguments for QApplication
    char amessage[] = "this is it";
    char *pmessage = amessage;
    int argc = 0;
    char **argv = &pmessage;

    QApplication app(argc,argv);

    MainWindow w;
    w.setWindowTitle("NeuroLab");
    w.resize(750,450);
    w.show();


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
    app.exec();


}
