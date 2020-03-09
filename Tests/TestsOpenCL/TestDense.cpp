#include "Tests/TestsOpenCL/TestDense.hpp"

#include "ie_builders.hpp"
#include "ie_network.hpp"
#include "ie_iexecutable_network.hpp"
#include <iostream>
#include "ie_core.hpp"
#include "Tests/TestsOpenCL/ManuelTestData.hpp"

using namespace std;

#define TEST_CASES 30;

//Dense Layer
#define DENSE_LAYER_MAX_BATCH_SIZE 10;
#define DENSE_LAYER_MAX_INPUT_MAPS 10;
#define DENSE_LAYER_MAX_INPUT_HEIGHT 20;
#define DENSE_LAYER_MAX_INPUT_WIDTH 20;
#define DENSE_LAYER_MAX_OUTPUT_NEURONS 10;
#define DENSE_LAYER_MAX_ABSOLUTE_DIFFERENCE 0.0001;

void TestDense::parseStructure(DenseLayerCont* denseLayerCont,string content){
    stringstream in(content);
    while(!in.eof()){
        string key;
        in>>key;
        string value;
        in>>value;
        if(key=="BatchSize"){
            denseLayerCont->batchSize=stof(value);
        }else if(key=="InputMaps"){
            denseLayerCont->inputMaps=stof(value);
        }else if(key=="InputWidth"){
            denseLayerCont->inputWidth=stof(value);
        }else if(key=="InputHeight"){
            denseLayerCont->inputHeight=stof(value);
        }else if(key=="OutputNeurons"){
            denseLayerCont->outputNeurons=stof(value);
        }else{
            cerr<<"This key is not implemented ("<<key<<","<<value<<")!"<<endl;
        }
    }
}

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
            float maxAbsoluteDiff=DENSE_LAYER_MAX_ABSOLUTE_DIFFERENCE;
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
int TestDense::testErrorComp(){
    ManuelTestData* manuelTestData=new ManuelTestData();

    //load errors input
    vector<float>vectorErrorsInput;
    util->loadStringToArray(manuelTestData->getDenseErrorsInputTest1(),&vectorErrorsInput);
    float*errorsInput=(float*)malloc(sizeof(float)*vectorErrorsInput.size());
    util->convertVectorToFloatArray(&vectorErrorsInput, errorsInput);

    //load errors output
    vector<float>vectorErrorsOutput;
    util->loadStringToArray(manuelTestData->getDenseErrorsOutputTest1(),&vectorErrorsOutput);
    float*errorsOutput=(float*)malloc(sizeof(float)*vectorErrorsOutput.size());
    util->convertVectorToFloatArray(&vectorErrorsOutput, errorsOutput);

    //load input values
    vector<float>vectorInputValues;
    util->loadStringToArray(manuelTestData->getDenseInputValuesTest1(),&vectorInputValues);
    float*inputValues=(float*)malloc(sizeof(float)*vectorInputValues.size());
    util->convertVectorToFloatArray(&vectorInputValues, inputValues);

    //load output values
    vector<float>vectorOutputValues;
    util->loadStringToArray(manuelTestData->getDenseOutputValuesTest1(),&vectorOutputValues);
    float*outputValues=(float*)malloc(sizeof(float)*vectorOutputValues.size());
    util->convertVectorToFloatArray(&vectorOutputValues, outputValues);

    //load weight values
    vector<float>vectorWeightValues;
    util->loadStringToArray(manuelTestData->getDenseWeightsTest1(),&vectorWeightValues);
    float*weightValues=(float*)malloc(sizeof(float)*vectorWeightValues.size());
    util->convertVectorToFloatArray(&vectorWeightValues, weightValues);

    //load bias values
    vector<float>vectorBiasValues;
    util->loadStringToArray(manuelTestData->getDenseWeightsTest1(),&vectorBiasValues);
    float*biasValues=(float*)malloc(sizeof(float)*vectorBiasValues.size());
    util->convertVectorToFloatArray(&vectorBiasValues, biasValues);

    string content=manuelTestData->getDenseStructureTest1();
    DenseLayerCont* denseLayerCont=new DenseLayerCont();
    parseStructure(denseLayerCont, content);
    denseLayerCont->outputErrors=errorsOutput;
    denseLayerCont->inputValues=inputValues;
    denseLayerCont->weights=weightValues;
    denseLayerCont->biases=biasValues;

    OpenCLEnvironmentCreator* envCreator=new OpenCLEnvironmentCreator();
    OpenCLEnvironment* env=envCreator->createOpenCLEnvironment(HardwareType::CPU);
    OpenCLLayerCreator* openclLayerCreator=new OpenCLLayerCreator();
    OpenCLLayer* openclLayer=openclLayerCreator->createDenseLayer(env, denseLayerCont->batchSize, denseLayerCont->inputMaps, denseLayerCont->inputHeight, denseLayerCont->inputWidth, denseLayerCont->outputNeurons);
    openclLayer->setBiases(env, denseLayerCont->biases, denseLayerCont->outputNeurons);
    openclLayer->setWeights(env, denseLayerCont->weights, denseLayerCont->inputMaps*denseLayerCont->inputHeight*denseLayerCont->inputWidth*denseLayerCont->outputNeurons);
    openclLayer->setInputs(env, denseLayerCont->inputValues, denseLayerCont->batchSize*denseLayerCont->inputMaps*denseLayerCont->inputHeight*denseLayerCont->inputWidth);
    openclLayer->setOutputErrors(env, denseLayerCont->outputErrors, denseLayerCont->batchSize*denseLayerCont->outputNeurons);

    openclLayer->computeForward(env, denseLayerCont->batchSize, denseLayerCont->outputNeurons);
    openclLayer->computeErrorComp(env, denseLayerCont->batchSize);
    float*computedInputErrors=openclLayer->getErrorInputs(env, denseLayerCont->batchSize, denseLayerCont->inputMaps, denseLayerCont->inputHeight, denseLayerCont->inputWidth, NULL);

    int differences=0;
    for(int batch=0;batch<denseLayerCont->batchSize;batch++){
        for(int map=0;map<denseLayerCont->inputMaps;map++){
            for(int y=0;y<denseLayerCont->inputHeight;y++){
                for(int x=0;x<denseLayerCont->inputWidth;x++){
                    int index=x+denseLayerCont->inputWidth*(y+denseLayerCont->inputHeight*(map+denseLayerCont->inputMaps*(batch)));
                    float diff=errorsInput[index]-computedInputErrors[index];
                    float maxAbsolutDifference=DENSE_LAYER_MAX_ABSOLUTE_DIFFERENCE;
                    if(abs(diff)>maxAbsolutDifference){
                        differences++;
                    }
                }
            }
        }
    }

    delete[]computedInputErrors;
    delete envCreator;
    delete env;
    delete openclLayerCreator;
    delete openclLayer;
    delete denseLayerCont;
    delete[]errorsInput;
    delete[]outputValues;
    delete manuelTestData;

    return differences;
}
int TestDense::testWeightsUpdate(){
    ManuelTestData* manuelTestData=new ManuelTestData();

    //load errors input
    vector<float>vectorErrorsInput;
    util->loadStringToArray(manuelTestData->getDenseErrorsInputTest1(),&vectorErrorsInput);
    float*errorsInput=(float*)malloc(sizeof(float)*vectorErrorsInput.size());
    util->convertVectorToFloatArray(&vectorErrorsInput, errorsInput);

    //load errors output
    vector<float>vectorErrorsOutput;
    util->loadStringToArray(manuelTestData->getDenseErrorsOutputTest1(),&vectorErrorsOutput);
    float*errorsOutput=(float*)malloc(sizeof(float)*vectorErrorsOutput.size());
    util->convertVectorToFloatArray(&vectorErrorsOutput, errorsOutput);

    //load input values
    vector<float>vectorInputValues;
    util->loadStringToArray(manuelTestData->getDenseInputValuesTest1(),&vectorInputValues);
    float*inputValues=(float*)malloc(sizeof(float)*vectorInputValues.size());
    util->convertVectorToFloatArray(&vectorInputValues, inputValues);

    //load output values
    vector<float>vectorOutputValues;
    util->loadStringToArray(manuelTestData->getDenseOutputValuesTest1(),&vectorOutputValues);
    float*outputValues=(float*)malloc(sizeof(float)*vectorOutputValues.size());
    util->convertVectorToFloatArray(&vectorOutputValues, outputValues);

    //load weight values
    vector<float>vectorWeightValues;
    util->loadStringToArray(manuelTestData->getDenseWeightsTest1(),&vectorWeightValues);
    float*weightValues=(float*)malloc(sizeof(float)*vectorWeightValues.size());
    util->convertVectorToFloatArray(&vectorWeightValues, weightValues);

    //load bias values
    vector<float>vectorBiasValues;
    util->loadStringToArray(manuelTestData->getDenseBiasesTest1(),&vectorBiasValues);
    float*biasValues=(float*)malloc(sizeof(float)*vectorBiasValues.size());
    util->convertVectorToFloatArray(&vectorBiasValues, biasValues);

    //load new bias values
    vector<float>vectorNewBiasValues;
    util->loadStringToArray(manuelTestData->getDenseNewBiasesTest1(),&vectorNewBiasValues);
    float*newBiasValues=(float*)malloc(sizeof(float)*vectorNewBiasValues.size());
    util->convertVectorToFloatArray(&vectorNewBiasValues, newBiasValues);

    //load new weight values
    vector<float>vectorNewWeightsValues;
    util->loadStringToArray(manuelTestData->getDenseNewWeightsTest1(),&vectorNewWeightsValues);
    float*newWeightsValues=(float*)malloc(sizeof(float)*vectorNewWeightsValues.size());
    util->convertVectorToFloatArray(&vectorNewWeightsValues, newWeightsValues);

    //load learning rate
    float learningRate=stof(manuelTestData->getDenseLearningRateTest1());

    string content=manuelTestData->getDenseStructureTest1();
    DenseLayerCont* denseLayerCont=new DenseLayerCont();
    parseStructure(denseLayerCont, content);
    denseLayerCont->outputErrors=errorsOutput;
    denseLayerCont->inputValues=inputValues;
    denseLayerCont->weights=weightValues;
    denseLayerCont->biases=biasValues;
    denseLayerCont->learningRate=learningRate;

    OpenCLEnvironmentCreator* envCreator=new OpenCLEnvironmentCreator();
    OpenCLEnvironment* env=envCreator->createOpenCLEnvironment(HardwareType::CPU);
    OpenCLLayerCreator* openclLayerCreator=new OpenCLLayerCreator();
    OpenCLLayer* openclLayer=openclLayerCreator->createDenseLayer(env, denseLayerCont->batchSize, denseLayerCont->inputMaps, denseLayerCont->inputHeight, denseLayerCont->inputWidth, denseLayerCont->outputNeurons);
    openclLayer->setBiases(env, denseLayerCont->biases, denseLayerCont->outputNeurons);
    openclLayer->setWeights(env, denseLayerCont->weights, denseLayerCont->inputMaps*denseLayerCont->inputHeight*denseLayerCont->inputWidth*denseLayerCont->outputNeurons);
    openclLayer->setInputs(env, denseLayerCont->inputValues, denseLayerCont->batchSize*denseLayerCont->inputMaps*denseLayerCont->inputHeight*denseLayerCont->inputWidth);
    openclLayer->setOutputErrors(env, denseLayerCont->outputErrors, denseLayerCont->batchSize*denseLayerCont->outputNeurons);
    openclLayer->setLearningRate(learningRate);

    openclLayer->computeForward(env, denseLayerCont->batchSize, denseLayerCont->outputNeurons);
    openclLayer->computeErrorComp(env, denseLayerCont->batchSize);
    openclLayer->computeWeightsUpdate(env, denseLayerCont->outputNeurons);
    float*computedNewWeights=openclLayer->getWeights(env, denseLayerCont->inputMaps*denseLayerCont->inputHeight*denseLayerCont->inputWidth*denseLayerCont->outputNeurons);
    float*computedNewBiases=openclLayer->getBiases(env, denseLayerCont->outputNeurons);

    int differences=0;
    float maxAbsolutDifference=DENSE_LAYER_MAX_ABSOLUTE_DIFFERENCE;
    for(int out=0;out<denseLayerCont->outputNeurons;out++){
        for(int map=0;map<denseLayerCont->inputMaps;map++){
            for(int y=0;y<denseLayerCont->inputHeight;y++){
                for(int x=0;x<denseLayerCont->inputWidth;x++){
                    int index=x+denseLayerCont->inputWidth*(y+denseLayerCont->inputHeight*(map+denseLayerCont->inputMaps*(out)));
                    float diff=newWeightsValues[index]-computedNewWeights[index];
                    if(abs(diff)>maxAbsolutDifference){
                        differences++;
                    }
                }
            }
        }
        float diff=newBiasValues[out]-computedNewBiases[out];
        if(abs(diff)>maxAbsolutDifference){
            differences++;
        }
    }

    delete[]computedNewBiases;
    delete[]computedNewWeights;
    delete envCreator;
    delete env;
    delete openclLayerCreator;
    delete openclLayer;
    delete denseLayerCont;
    delete[]errorsInput;
    delete[]outputValues;
    delete[]newWeightsValues;
    delete[]newBiasValues;
    delete manuelTestData;

    return differences;
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

    EXPECT_EQ(0,p->testErrorComp());

    delete p;
}

TEST(Dense, WeightsUpdate){
    TestDense* p=new TestDense();

    EXPECT_EQ(0,p->testWeightsUpdate());

    delete p;
}
