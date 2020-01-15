#include "AlexNet.h"

AlexNet::AlexNet()
{
    this->ovEnv = new OpenVinoEnv();
}
void AlexNet::classify(QStringList paths)
{
    ovEnv->initMovidius();
    ovEnv->classify();
}
