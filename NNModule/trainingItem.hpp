#pragma once

#include <stdlib.h>
#include <string>

using namespace std;

class TrainingItem{
private:
    int label;
    string path;

public:
    TrainingItem(string path, int label);

    string getPath();
    int getLabel();
};
