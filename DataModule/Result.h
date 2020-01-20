#ifndef RESULT_H
#define RESULT_H



#include <iostream>
#include <vector>
using namespace std;

class Result {

public:
    string getPath() const{
        return path;
    }
    void setPath(const string &value){
        path = value;
    }



    vector<pair<string, float> > getLabelsAndProb() const{
        return labelsAndProb;
    }
    void pushLabelsAndProb(const pair<string, float>  &value){
        labelsAndProb.push_back(value);
    }

private:
    string path;
    vector<pair<string,float>> labelsAndProb;
};

#endif // RESULT_H
