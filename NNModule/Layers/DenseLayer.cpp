#include "DenseLayer.h"




DenseLayer::DenseLayer(OpenCLEnvironment *clEnv,
                       size_t inputHeight,
                       size_t inputWidth,
                       size_t inputDepth,
                       size_t numOutputs)
{
    this->clEnv = clEnv;
    OpenCLLayerCreator* openCLLayerCreator = new OpenCLLayerCreator();
    OpenCLLayer* cLDense = openCLLayerCreator->createDenseLayer(clEnv,10,inputDepth,
                                                                inputHeight,inputWidth,
                                                                numOutputs);
    this->clLayer = cLDense;

    clLayer->setWeights(clEnv,getWeights(inputHeight*inputWidth*inputDepth),inputHeight*inputWidth*inputDepth);
    clLayer->setBiases(clEnv,getWeights(inputDepth),inputDepth);
    clLayer->setLearningRate(0.2);
}

void DenseLayer::forwardPass(float input[], float output[])
{

    //clLayer->setInputs(clEnv,input,105*105*3);
    clLayer->computeForward(clEnv,10,inputDepth);
}

void DenseLayer::backPropagate(float upstreamGrad[])
{

}

OpenCLLayer *DenseLayer::getCLLayer()
{
    return clLayer;
}

float* DenseLayer::getWeights(int length) {
    srand(time(NULL));

    float* weights= (float*)malloc(sizeof(float)*length);

    for (int i = 0; i < length; i++) {
        weights[i] = getRandom();
    }

    return weights;
}

float DenseLayer::getRandom() {
    return rand() / float(RAND_MAX);
}

