#include "DataModule/WeightsAndBiasesCreator.h"
#include <QDebug>

WeightsAndBiasesCreator::WeightsAndBiasesCreator(int outputMaps, int inputMaps, int kernelHeight, int kernelWidth, int seed) {
        this->outputMaps = outputMaps;
        this->inputMaps = inputMaps;
        this->kernelHeight = kernelHeight;
        this->kernelWidth = kernelWidth;
        std::default_random_engine generator(seed);
}

WeightsAndBiasesCreator::WeightsAndBiasesCreator(){}

vector<float> WeightsAndBiasesCreator::createWeights(){
    int inputNeurons = inputMaps * kernelHeight * kernelWidth;
    vector<float> weights;
    weights.resize(outputMaps * inputNeurons);

    for(int outputMap=0; outputMap < outputMaps; outputMap++){
        for(int inputMap=0; inputMap < inputMaps; inputMap++){
            for(int kernelY=0; kernelY < kernelHeight; kernelY++){
                for(int kernelX=0; kernelX < kernelWidth; kernelX++){
                    //https://hackernoon.com/how-to-initialize-weights-in-a-neural-net-so-it-performs-well-3e9302d4490f for formula for relu
                    weights[calculateId(outputMap, inputMap, kernelY, kernelX)]=(float)(sqrt(2) * distribution(generator)/sqrt((float)inputNeurons));
                }
            }
        }
    }

    return weights;
}

vector<float> WeightsAndBiasesCreator::createBias(){
    vector<float> biases;
    biases.resize(outputMaps);
    for(int i=0;i<outputMaps;i++){
        biases[i]=(float) distribution(generator);
    }
    return biases;
}


void WeightsAndBiasesCreator::save(vector<float> values, string dir){
        ofstream fout;

        fout.open(dir);

        for(int i=0; i < (int) values.size() && (fout.is_open()); i++){
            fout << values[i] << " ";
            if(i + 1 % kernelWidth == 0){
                fout << "\n";
            }
        }
        qDebug()<<"save weights"<<endl;

        fout.close();
}


int WeightsAndBiasesCreator::calculateWeightId(int inputMaps, int inputHeight, int inputWidth, int outputNeuron, int inputMap, int y, int x){
    return (((outputNeuron) * inputMaps + inputMap) * inputHeight + y) * inputWidth + x;
}

int WeightsAndBiasesCreator::calculateId(int outputMap, int inputMap, int kernelY, int kernelX){
    return calculateWeightId(inputMaps, kernelHeight, kernelWidth, outputMap, inputMap, kernelY, kernelX);
}

string WeightsAndBiasesCreator::createWeightsFile(string fileName, string dir) {
    qDebug()<<"weights file"<<endl;
    vector<float> weights = createWeights();
    fileName = dir + fileName;
    save(weights, fileName);
    return fileName;
}

void WeightsAndBiasesCreator::updateWeightsFile(string filePath, vector<vector<float>> weights, int size) {
    for(int i = 0; i < size; i++){
        save(weights[i], filePath);
    }
}

void WeightsAndBiasesCreator::updateWeightsFile(string filePath, vector<float> weights) {
    save(weights, filePath);
}

void WeightsAndBiasesCreator::createBiasFile(string fileName, string dir) {
    vector<float> biases = createBias();
    fileName = dir + fileName;
    save(biases, fileName);
}


/*
 * example of how to use the methods to create the files; please give the directory path in your computer;
 * the values for each layer should be correct
 **/
 void WeightsAndBiasesCreator::createWeightsAndBiases() {

     //conv1
    WeightsAndBiasesCreator  *creator;
    creator = new WeightsAndBiasesCreator(15, 3, 7, 7, 12345);
    creator->createWeightsFile("conv1_weights.txt", "/home/jens/Schreibtisch/Weights/");
    creator->createBiasFile("biases_conv1.txt", "/home/jens/Schreibtisch/Weights/");

    //conv2
    creator = new WeightsAndBiasesCreator(40, 15, 4, 4, 12347);
    creator->createWeightsFile("weights_conv2.txt", "/home/jens/Schreibtisch/Weights/");
    creator->createBiasFile("biases_conv2.txt", "/home/jens/Schreibtisch/Weights/");


    //dense
    creator = new WeightsAndBiasesCreator(6, 40, 5, 5, 12346);
    creator->createWeightsFile("weights_dense.txt", "/home/jens/Schreibtisch/Weights/");
    creator->createBiasFile("biases_dense.txt", "/home/jens/Schreibtisch/Weights/");
}
