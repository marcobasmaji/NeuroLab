#include "NNModule/trainingItem.hpp"

TrainingItem::TrainingItem(string path, int label){
    this->path=path;
    this->label=label;
}

string TrainingItem::getPath(){
    return path;
}
int TrainingItem::getLabel(){
    return label;
}
