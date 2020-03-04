#include "Tests/TestsOpenCL/TestDense.hpp"

#include "ie_builders.hpp"
#include "ie_network.hpp"
#include "ie_iexecutable_network.hpp"
#include <iostream>
#include "ie_core.hpp"

using namespace std;

#define TEST_CASES 1;

//Dense Layer
#define DENSE_LAYER_MAX_BATCH_SIZE 10;
#define DENSE_LAYER_MAX_INPUT_MAPS 10;
#define DENSE_LAYER_MAX_INPUT_HEIGHT 20;
#define DENSE_LAYER_MAX_INPUT_WIDTH 20;
#define DENSE_LAYER_MAX_OUTPUT_NEURONS 10;
#define POOLING_LAYER_MAX_ABSOLUTE_DIFFERENCE 0.0001;

void TestDense::createRandomDenseLayerCont(DenseLayerCont* denseLayerCont){
    int maxBatchSize=DENSE_LAYER_MAX_BATCH_SIZE;
    int maxInputMaps=DENSE_LAYER_MAX_INPUT_MAPS;
    int maxInputHeight=DENSE_LAYER_MAX_INPUT_HEIGHT;
    int maxInputWidth=DENSE_LAYER_MAX_INPUT_WIDTH;
    int maxOutputNeurons=DENSE_LAYER_MAX_OUTPUT_NEURONS;

    int batchSize=util->getRandomIntValue(1,maxBatchSize);
    int inputMaps=util->getRandomIntValue(1,maxInputMaps);
    int inputHeight=util->getRandomIntValue(1,maxInputHeight);
    int inputWidth=util->getRandomIntValue(1,maxInputWidth);
    int outputNeurons=util->getRandomIntValue(1,maxOutputNeurons);
    float learningRate=(float)(util->getRandomIntValue(1,100))/100.0;

    int length=inputMaps*inputHeight*inputWidth*outputNeurons;
    float*weights=(float*)malloc(sizeof(float)*length);
    for(int i=0;i<length;i++)   weights[i]*=sqrt(1.0/(float)(inputMaps*inputHeight*inputWidth));
    util->createRandomValues(weights, length);

    length=outputNeurons;
    float*biases=(float*)malloc(sizeof(float)*length);
    util->createRandomValues(biases, length);

    length=batchSize*inputMaps*inputHeight*inputWidth;
    float*inputValues=(float*)malloc(sizeof(float)*length);
    util->createRandomValues(inputValues, length);

    length=batchSize*outputNeurons;
    float*outputErrors=(float*)malloc(sizeof(float)*length);
    util->createRandomValues(outputErrors, length);

    denseLayerCont->inputMaps=inputMaps;
    denseLayerCont->inputHeight=inputHeight;
    denseLayerCont->inputWidth=inputWidth;
    denseLayerCont->outputNeurons=outputNeurons;
    denseLayerCont->batchSize=batchSize;
    denseLayerCont->biases=biases;
    denseLayerCont->weights=weights;
    denseLayerCont->inputValues=inputValues;
    denseLayerCont->outputErrors=outputErrors;
    denseLayerCont->learningRate=learningRate;
}
void TestDense::createPerzeptronLayerOpennn(DenseLayerCont* denseLayerCont, PerceptronLayer* perceptronLayerOpennn){
    Tensor<double>biases(denseLayerCont->outputNeurons);
    perceptronLayerOpennn->set_activation_function(PerceptronLayer::ActivationFunction::Linear);
    for(int i=0;i<denseLayerCont->outputNeurons;i++)    biases[i]=denseLayerCont->biases[i];
    perceptronLayerOpennn->set_biases(biases);
    Matrix<double>weights(denseLayerCont->inputMaps*denseLayerCont->inputHeight*denseLayerCont->inputWidth,denseLayerCont->outputNeurons);
    int a=0;
    for(int out=0;out<denseLayerCont->outputNeurons;out++){
        for(int x=0;x<denseLayerCont->inputWidth;x++){
            for(int y=0;y<denseLayerCont->inputHeight;y++){
                for(int map=0;map<denseLayerCont->inputMaps;map++){
                    int index=x+denseLayerCont->inputWidth*(y+denseLayerCont->inputHeight*(map+denseLayerCont->inputMaps*(out)));
                    weights[a]=denseLayerCont->weights[index];
                    a++;
                }
            }
        }
    }
    perceptronLayerOpennn->set_synaptic_weights(weights);
}

int TestDense::testFeedForward(){
    DenseLayerCont* denseLayerCont=new DenseLayerCont();
    createRandomDenseLayerCont(denseLayerCont);

    OpenCLEnvironmentCreator* envCreator=new OpenCLEnvironmentCreator();
    OpenCLEnvironment* env=envCreator->createOpenCLEnvironment(HardwareType::CPU);

    OpenCLLayerCreator* openclLayerCreator=new OpenCLLayerCreator();
    OpenCLLayer* openclLayer=openclLayerCreator->createDenseLayer(env, denseLayerCont->batchSize, denseLayerCont->inputMaps, denseLayerCont->inputHeight, denseLayerCont->inputWidth, denseLayerCont->outputNeurons);
    openclLayer->setInputs(env, denseLayerCont->inputValues, denseLayerCont->batchSize*denseLayerCont->inputMaps*denseLayerCont->inputHeight*denseLayerCont->inputWidth);
    openclLayer->setBiases(env, denseLayerCont->biases, denseLayerCont->outputNeurons);
    openclLayer->setLearningRate(denseLayerCont->learningRate);
    openclLayer->setWeights(env, denseLayerCont->weights, denseLayerCont->inputMaps*denseLayerCont->inputHeight*denseLayerCont->inputWidth*denseLayerCont->outputNeurons);

    PerceptronLayer* perceptronLayerOpennn=new PerceptronLayer(denseLayerCont->inputMaps*denseLayerCont->inputHeight*denseLayerCont->inputWidth,denseLayerCont->outputNeurons);
    createPerzeptronLayerOpennn(denseLayerCont, perceptronLayerOpennn);

    //set inputs
    Tensor<double>inputs(denseLayerCont->batchSize, denseLayerCont->inputMaps, denseLayerCont->inputHeight, denseLayerCont->inputWidth);
    int i=0;
    for(int batch=0;batch<denseLayerCont->batchSize;batch++){
        for(int map=0;map<denseLayerCont->inputMaps;map++){
            for(int y=0;y<denseLayerCont->inputHeight;y++){
                for(int x=0;x<denseLayerCont->inputWidth;x++){
                    inputs(batch, map, y, x)=denseLayerCont->inputValues[i];
                    i++;
                }
            }
        }
    }

    //calculate outputs
    Tensor<double>outputs1=perceptronLayerOpennn->calculate_outputs(inputs);
    openclLayer->computeForward(env, denseLayerCont->batchSize, denseLayerCont->outputNeurons);
    float*outputs2=openclLayer->getOutputs(env, denseLayerCont->batchSize, denseLayerCont->outputNeurons, 1, 1, NULL);

    //compare outputs
    int differences=0;

    for(int batch=0;batch<denseLayerCont->batchSize;batch++){
        for(int out=0;out<denseLayerCont->outputNeurons;out++){
            int index=out+denseLayerCont->outputNeurons*(batch);

            float value1=outputs1(batch, out);
            float value2=outputs2[index];

            float diff=abs(value1-value2);
            float maxAbsoluteDiff=POOLING_LAYER_MAX_ABSOLUTE_DIFFERENCE;
            if(diff>maxAbsoluteDiff){
                differences++;
            }
        }
    }

    delete perceptronLayerOpennn;
    delete openclLayerCreator;
    delete openclLayer;
    delete[]outputs2;
    delete env;
    delete envCreator;
    delete denseLayerCont;

    return differences;
}
//TODO
int TestDense::testErrorComp(){
    //TODO
    return 0;
}


TEST(Dense, FeedforwardProcess){
    TestDense* p=new TestDense();

    int testCases=TEST_CASES;
    for(int testCase=0;testCase<testCases;testCase++){
        EXPECT_EQ(0,p->testFeedForward());
    }

    delete p;
}

TEST(Dense, ErrorComp){
    TestDense* p=new TestDense();

    int testCases=TEST_CASES;
    for(int testCase=0;testCase<testCases;testCase++){
        EXPECT_EQ(0,p->testErrorComp());
    }

    delete p;
}

