#include "ConvolutionLayer.h"

CovolutionLayer::CovolutionLayer(
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

}

void CovolutionLayer::forwardPass(float [105][105][3])
{
        /*OpenCLLayerCreator* openCLLayerCreator = new OpenCLLayerCreator();
        OpenCLLayer* conv1 = openCLLayerCreator->createConvLayer(clEnv,10,3,105,105,50,34,34,6,6,3,3);
        srand(time(NULL));
        int length = 6*6*50;
            float* weights= (float*)malloc(sizeof(float)*(length));

            for (int i = 0; i < length; i++) {
                weights[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)/length*20;
            }
        conv1->setWeights(clEnv,weights,6*6*50);
        conv1->setLearningRate(0.2);
        conv1->setInputs(clEnv,weights,105*105*3);
        conv1->computeForward(clEnv,10,50);*/
}
