#ifndef ALEXNET_H
#define ALEXNET_H

#include<HardwareModule/OpenVinoEnv.h>
#include<QApplication>

class AlexNet
{
public:
    AlexNet();
    void classify(QStringList paths);
private:
    OpenVinoEnv* ovEnv;
};

#endif // ALEXNET_H
