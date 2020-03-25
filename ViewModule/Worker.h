#ifndef WORKER_H
#define WORKER_H

#include <QObject>

#include <ControllerModule/ViewController.h>



class Worker : public QObject
{
    Q_OBJECT

public:
    Worker(string dataSetDir, string weightsDir, string newWeightsDir, ViewController *viewController);
    ~Worker();

public slots:
    void process();
signals:
    void finished();
    void error(QString err);
private:
    string dataSetDir;
    string weightsDir;
    string newWeightsDir;
    ViewController *viewController = nullptr;
};

#endif // WORKER_H
