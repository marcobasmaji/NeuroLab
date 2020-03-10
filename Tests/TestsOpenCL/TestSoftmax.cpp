#include "Tests/TestsOpenCL/TestSoftmax.hpp"

#include "ie_builders.hpp"
#include "ie_network.hpp"
#include "ie_iexecutable_network.hpp"
#include <iostream>
#include "ie_core.hpp"

using namespace std;

#define TEST_CASES 10;

//Pooling Layer
#define SOFTMAX_LAYER_MAX_BATCH_SIZE 10;
#define SOFTMAX_LAYER_MAX_NEURONS 10;
#define SOFTMAX_LAYER_MAX_ABSOLUTE_DIFFERENCE 0.0001;

void TestSoftmax::createRandomSoftmaxLayerCont(SoftmaxLayerCont* softmaxLayerCont){
    int maxNeurons=SOFTMAX_LAYER_MAX_NEURONS;
    int maxBatchSize=SOFTMAX_LAYER_MAX_BATCH_SIZE;

    int neurons=util->getRandomIntValue(2,maxNeurons);  //2, due to opennn restrictions
    int batchSize=util->getRandomIntValue(1,maxBatchSize);

    int length=batchSize*neurons;
    float*inputValues=(float*)malloc(sizeof(float)*length);
    util->createRandomValues(inputValues,length);

    length=batchSize*neurons;
    float*outputErrors=(float*)malloc(sizeof(float)*length);
    util->createRandomValues(outputErrors,length);

    softmaxLayerCont->neurons=neurons;
    softmaxLayerCont->batchSize=batchSize;
    softmaxLayerCont->inputValues=inputValues;
    softmaxLayerCont->outputErrors=outputErrors;
}

void TestSoftmax::createProbabilisticLayerOpennn(SoftmaxLayerCont* softmaxLayerCont, ProbabilisticLayer* probabilisticLayerOpennn){
    probabilisticLayerOpennn->set_activation_function(ProbabilisticLayer::ActivationFunction::Softmax);

    Tensor<double>biases(softmaxLayerCont->neurons);
    for(int i=0;i<softmaxLayerCont->neurons;i++)  biases[i]=0;
    probabilisticLayerOpennn->set_biases(biases);

    int neurons=softmaxLayerCont->neurons;
    Matrix<double>weights(neurons, neurons);
    for(int neuron=0;neuron<neurons;neuron++){
        weights(neuron,neuron)=1;
    }
    probabilisticLayerOpennn->set_synaptic_weights(weights);
}

int TestSoftmax::testFeedForward(){
    SoftmaxLayerCont* softmaxLayerCont=new SoftmaxLayerCont();
    createRandomSoftmaxLayerCont(softmaxLayerCont);

    ProbabilisticLayer* probabilisticLayerOpennn=new ProbabilisticLayer(softmaxLayerCont->neurons,softmaxLayerCont->neurons);
    createProbabilisticLayerOpennn(softmaxLayerCont,probabilisticLayerOpennn);

    //set inputs
    Tensor<double>inputs(softmaxLayerCont->batchSize, softmaxLayerCont->neurons);
    for(int batch=0;batch<softmaxLayerCont->batchSize;batch++){
        int in=0;
        for(int neuron=0;neuron<softmaxLayerCont->neurons;neuron++){
            inputs(batch, neuron)=softmaxLayerCont->inputValues[neuron+softmaxLayerCont->neurons*(batch)];
        }
    }

    OpenCLEnvironmentCreator* envCreator=new OpenCLEnvironmentCreator();
    OpenCLEnvironment* env=envCreator->createOpenCLEnvironment(HardwareType::CPU);
    OpenCLLayerCreator* openclLayerCreator=new OpenCLLayerCreator();
    OpenCLLayer* openclLayer=openclLayerCreator->createSoftmaxLayer(env, softmaxLayerCont->batchSize, softmaxLayerCont->neurons, 1, 1);
    openclLayer->setInputs(env, softmaxLayerCont->inputValues, softmaxLayerCont->batchSize*softmaxLayerCont->neurons);

    //calculate outputs
    Tensor<double>outputs1=probabilisticLayerOpennn->calculate_outputs(inputs);
    openclLayer->computeForward(env, softmaxLayerCont->batchSize, softmaxLayerCont->neurons);
    float*outputs2=openclLayer->getOutputs(env, softmaxLayerCont->batchSize, softmaxLayerCont->neurons, 1, 1, NULL);

    //compare outputs
    int differences=0;

    for(int batch=0;batch<softmaxLayerCont->batchSize;batch++){
        for(int out=0;out<softmaxLayerCont->neurons;out++){
            int index=out+softmaxLayerCont->neurons*(batch);

            float value1=outputs1(batch,out);
            float value2=outputs2[index];

            float diff=abs(value1-value2);
            float maxAbsoluteDiff=SOFTMAX_LAYER_MAX_ABSOLUTE_DIFFERENCE;
            if(diff>maxAbsoluteDiff){
                differences++;
            }
        }
    }

    delete probabilisticLayerOpennn;
    delete softmaxLayerCont;

    return differences;
}

int TestSoftmax::testErrorComp(){
    SoftmaxLayerCont* softmaxLayerCont=new SoftmaxLayerCont();
    createRandomSoftmaxLayerCont(softmaxLayerCont);

    OpenCLEnvironmentCreator* envCreator=new OpenCLEnvironmentCreator();
    OpenCLEnvironment* env=envCreator->createOpenCLEnvironment(HardwareType::CPU);
    OpenCLLayerCreator* openclLayerCreator=new OpenCLLayerCreator();
    OpenCLLayer* openclLayer=openclLayerCreator->createSoftmaxLayer(env, softmaxLayerCont->batchSize, softmaxLayerCont->neurons, 1, 1);
    int length=softmaxLayerCont->batchSize*softmaxLayerCont->neurons;
    openclLayer->setInputs(env, softmaxLayerCont->inputValues, length);
    openclLayer->setOutputErrors(env, softmaxLayerCont->outputErrors, length);

    //calculate input errors
    openclLayer->computeForward(env, softmaxLayerCont->batchSize, softmaxLayerCont->neurons);
    openclLayer->computeErrorComp(env, softmaxLayerCont->batchSize);
    float*errorInputs=openclLayer->getErrorInputs(env, softmaxLayerCont->batchSize, softmaxLayerCont->neurons, 1, 1, NULL);

    //compare outputs
    int differences=0;

    for(int batch=0;batch<softmaxLayerCont->batchSize;batch++){
        for(int out=0;out<softmaxLayerCont->neurons;out++){
            int index=out+softmaxLayerCont->neurons*(batch);

            float errorInput=errorInputs[index];
            float errorOutput=softmaxLayerCont->outputErrors[index];

            float diff=abs(errorInput-errorOutput);
            float maxAbsoluteDiff=SOFTMAX_LAYER_MAX_ABSOLUTE_DIFFERENCE;
            if(diff>maxAbsoluteDiff){
                differences++;
            }
        }
    }

    delete softmaxLayerCont;
    delete errorInputs;

    return differences;
}

TEST(Softmax, FeedforwardProcess){
    TestSoftmax* p=new TestSoftmax();

    int testCases=TEST_CASES;
    for(int testCase=0;testCase<testCases;testCase++){
        EXPECT_EQ(0,p->testFeedForward());
    }

    delete p;
}

TEST(Softmax, ErrorComp){
    TestSoftmax* p=new TestSoftmax();

    int testCases=TEST_CASES;
    for(int testCase=0;testCase<testCases;testCase++){
        EXPECT_EQ(0,p->testErrorComp());
    }

    delete p;
}
