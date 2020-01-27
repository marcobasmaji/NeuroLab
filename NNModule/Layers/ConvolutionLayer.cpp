#include "ConvolutionLayer.h"

ConvolutionLayer::ConvolutionLayer(
        OpenCLEnvironment* clEnv,
        size_t inputHeight,
        size_t inputWidth,
        size_t inputDepth,
        size_t filterHeight,
        size_t filterWidth,
        size_t horizontalStride,
        size_t verticalStride,
        size_t numFilters) :
      inputHeight(inputHeight),
      inputWidth(inputWidth),
      inputDepth(inputDepth),
      filterHeight(filterHeight),
      filterWidth(filterWidth),
      horizontalStride(horizontalStride),
      verticalStride(verticalStride),
      numFilters(numFilters)
{
    this->clEnv = clEnv;
    OpenCLLayerCreator* openCLLayerCreator = new OpenCLLayerCreator();
    OpenCLLayer* cLconv = openCLLayerCreator->createConvLayer(clEnv,10,inputDepth,inputHeight,
                                                              inputWidth,20,28,28,filterHeight,
                                                              filterWidth,horizontalStride,verticalStride);
    this->clLayer = cLconv;
    clLayer->setWeights(clEnv,getWeights(filterWidth*filterHeight*numFilters),filterWidth*filterHeight*numFilters);
    clLayer->setBiases(clEnv,getWeights(numFilters),numFilters);
    clLayer->setLearningRate(0.2);

}

void ConvolutionLayer::forwardPass(float input[],float output[])
{

        clLayer->setInputs(clEnv,input,inputHeight*inputWidth*inputDepth);
        clLayer->computeForward(clEnv,10,numFilters);

}
void ConvolutionLayer::backPropagate(float *upstreamGrad)
{
}
OpenCLLayer* ConvolutionLayer::getCLLayer()
{
    return clLayer;
}

float* ConvolutionLayer::getWeights(int length) {

    float* weights= (float*)malloc(sizeof(float)*length);

    for (int i = 0; i < length; i++) {
        weights[i] = getRandom();
    }

    return weights;
}

float ConvolutionLayer::getRandom() {
    return rand() / float(RAND_MAX);
}
