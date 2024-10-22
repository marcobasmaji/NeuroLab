#include "Tests/TestsOpenCL/TestMaxPooling.hpp"

#include "ie_builders.hpp"
#include "ie_network.hpp"
#include "ie_iexecutable_network.hpp"
#include <iostream>
#include "ie_core.hpp"
#include "Tests/TestsOpenCL/ManuelTestData.hpp"
#include <sstream>

using namespace std;

#define TEST_CASES 10;

//Pooling Layer
#define POOLING_LAYER_MAX_BATCH_SIZE 10;
#define POOLING_LAYER_MAX_INPUT_HEIGHT 30;
#define POOLING_LAYER_MAX_INPUT_WIDTH 30;
#define POOLING_LAYER_MAX_INPUT_MAPS 10;
#define POOLING_LAYER_MAX_POOLING_HEIGHT 8;
#define POOLING_LAYER_MAX_POOLING_WIDTH 8;
#define POOLING_LAYER_MAX_STRIDE_HEIGHT 8;
#define POOLING_LAYER_MAX_STRIDE_WIDTH 8;
#define POOLING_LAYER_MAX_ABSOLUTE_DIFFERENCE 0.0001;

void TestMaxPooling::parseStructure(PoolingLayerCont* poolingLayerCont, string content){
    stringstream in(content);
    while(!in.eof()){
        string key;
        in>>key;
        string value;
        in>>value;
        if(key=="BatchSize"){
            poolingLayerCont->batchSize=stof(value);
        }else if(key=="Maps"){
            poolingLayerCont->inputMaps=stof(value);
        }else if(key=="InputWidth"){
            poolingLayerCont->inputWidth=stof(value);
        }else if(key=="InputHeight"){
            poolingLayerCont->inputHeight=stof(value);
        }else if(key=="PoolingHeight"){
            poolingLayerCont->poolingHeight=stof(value);
        }else if(key=="PoolingWidth"){
            poolingLayerCont->poolingWidth=stof(value);
        }else if(key=="StrideHeight"){
            poolingLayerCont->strideHeight=stof(value);
        }else if(key=="StrideWidth"){
            poolingLayerCont->strideWidth=stof(value);
        }else if(key=="OutputHeight"){
            poolingLayerCont->outputHeight=stof(value);
        }else if(key=="OutputWidth"){
            poolingLayerCont->outputWidth=stof(value);
        }else{
            cerr<<"This key is not implemented (key,value)!"<<endl;
        }
    }
}

void TestMaxPooling::createRandomPoolingLayerCont(PoolingLayerCont* poolingLayerCont){
    //create parameters
    int maxBatchSize=POOLING_LAYER_MAX_BATCH_SIZE;
    int maxInputHeight=POOLING_LAYER_MAX_INPUT_HEIGHT;
    int maxInputWidth=POOLING_LAYER_MAX_INPUT_WIDTH;
    int maxInputMaps=POOLING_LAYER_MAX_INPUT_MAPS;
    int maxPoolingHeight=POOLING_LAYER_MAX_POOLING_HEIGHT;
    int maxPoolingWidth=POOLING_LAYER_MAX_POOLING_WIDTH;
    int maxStrideHeight=POOLING_LAYER_MAX_STRIDE_HEIGHT;
    int maxStrideWidth=POOLING_LAYER_MAX_STRIDE_WIDTH;

    int batchSize=util->getRandomIntValue(1, maxBatchSize);
    int inputMaps=util->getRandomIntValue(1, maxInputMaps);
    int inputHeight;
    int outputHeight;
    int poolingHeight;
    int strideHeight;
    do{
        outputHeight=util->getRandomIntValue(1, maxInputHeight);
        poolingHeight=util->getRandomIntValue(1, maxPoolingHeight);
        strideHeight=util->getRandomIntValue(1, maxStrideHeight);

        inputHeight=(outputHeight-1)*strideHeight+poolingHeight;
    }while(inputHeight>maxInputHeight);

    int inputWidth;
    int outputWidth;
    int poolingWidth;
    int strideWidth;
    do{
        outputWidth=util->getRandomIntValue(1, maxInputWidth);
        poolingWidth=util->getRandomIntValue(1, maxPoolingWidth);
        strideWidth=util->getRandomIntValue(1, maxStrideWidth);

        inputWidth=(outputWidth-1)*strideWidth+poolingWidth;
    }while(inputWidth>maxInputWidth);

    float* inputValues=(float*)malloc(sizeof(float)*batchSize*inputMaps*inputHeight*inputWidth);
    util->createRandomValues(inputValues, batchSize*inputMaps*inputHeight*inputWidth);

    float* outputErrors=(float*)malloc(sizeof(float)*batchSize*inputMaps*outputHeight*outputWidth);
    util->createRandomValues(outputErrors, batchSize*inputMaps*outputHeight*outputWidth);

    poolingLayerCont->batchSize=batchSize;
    poolingLayerCont->inputMaps=inputMaps;
    poolingLayerCont->inputHeight=inputHeight;
    poolingLayerCont->inputWidth=inputWidth;
    poolingLayerCont->outputHeight=outputHeight;
    poolingLayerCont->outputWidth=outputWidth;
    poolingLayerCont->poolingHeight=poolingHeight;
    poolingLayerCont->poolingWidth=poolingWidth;
    poolingLayerCont->strideHeight=strideHeight;
    poolingLayerCont->strideWidth=strideWidth;
    poolingLayerCont->inputValues=inputValues;
    poolingLayerCont->outputErrors=outputErrors;
}

void TestMaxPooling::createPoolingLayerOpennn(PoolingLayerCont* poolingLayerCont, PoolingLayer* poolingLayerOpennn){
    vector<size_t>inputDim={(size_t)poolingLayerCont->inputMaps, (size_t)poolingLayerCont->inputHeight, (size_t)poolingLayerCont->inputWidth};

    poolingLayerOpennn->set_pool_size(poolingLayerCont->poolingHeight, poolingLayerCont->poolingWidth);
    poolingLayerOpennn->set_row_stride(poolingLayerCont->strideHeight);
    poolingLayerOpennn->set_column_stride(poolingLayerCont->strideWidth);
    poolingLayerOpennn->set_padding_width(0);
    poolingLayerOpennn->set_inputs_dimensions(inputDim);
    poolingLayerOpennn->set_pooling_method(PoolingLayer::PoolingMethod::MaxPooling);
}

int TestMaxPooling::testFeedForward(){
    //create Pooling layers
    PoolingLayerCont* poolingLayerCont=new PoolingLayerCont();
    createRandomPoolingLayerCont(poolingLayerCont);

    PoolingLayer* poolingLayerOpennn=new PoolingLayer();
    createPoolingLayerOpennn(poolingLayerCont, poolingLayerOpennn);

    OpenCLEnvironmentCreator* envCreator=new OpenCLEnvironmentCreator();
    OpenCLEnvironment* env=envCreator->createOpenCLEnvironment(HardwareType::CPU);
    OpenCLLayerCreator* openclLayerCreator=new OpenCLLayerCreator();
    OpenCLLayer* openclLayer=openclLayerCreator->createMaxPoolLayer(env, poolingLayerCont->batchSize, poolingLayerCont->inputMaps, poolingLayerCont->inputHeight, poolingLayerCont->inputWidth, poolingLayerCont->outputHeight, poolingLayerCont->outputWidth, poolingLayerCont->poolingHeight, poolingLayerCont->poolingWidth, poolingLayerCont->strideHeight, poolingLayerCont->strideWidth);
    openclLayer->setInputs(env, poolingLayerCont->inputValues, poolingLayerCont->batchSize*poolingLayerCont->inputMaps*poolingLayerCont->inputHeight*poolingLayerCont->inputWidth);

    //set inputs
    Tensor<double>inputs(poolingLayerCont->batchSize, poolingLayerCont->inputMaps, poolingLayerCont->inputHeight, poolingLayerCont->inputWidth);
    int i=0;
    for(int batch=0;batch<poolingLayerCont->batchSize;batch++){
        for(int map=0;map<poolingLayerCont->inputMaps;map++){
            for(int y=0;y<poolingLayerCont->inputHeight;y++){
                for(int x=0;x<poolingLayerCont->inputWidth;x++){
                    inputs(batch, map, y, x)=poolingLayerCont->inputValues[i];
                    i++;
                }
            }
        }
    }

    //calculate outputs
    Tensor<double>outputs1=poolingLayerOpennn->calculate_outputs(inputs);
    openclLayer->computeForward(env, poolingLayerCont->batchSize, poolingLayerCont->inputMaps);
    float*outputs2=openclLayer->getOutputs(env, poolingLayerCont->batchSize, poolingLayerCont->inputMaps, poolingLayerCont->outputHeight, poolingLayerCont->outputWidth, NULL);

    //compare outputs
    int differences=0;

    for(int batch=0;batch<poolingLayerCont->batchSize;batch++){
        for(int map=0;map<poolingLayerCont->inputMaps;map++){
            for(int y=0;y<poolingLayerCont->outputHeight;y++){
                for(int x=0;x<poolingLayerCont->outputWidth;x++){
                    int index=x+poolingLayerCont->outputWidth*(y+poolingLayerCont->outputHeight*(map+poolingLayerCont->inputMaps*(batch)));

                    float value1=outputs1(batch, map, y, x);
                    float value2=outputs2[index];

                    float diff=abs(value1-value2);
                    float maxAbsoluteDiff=POOLING_LAYER_MAX_ABSOLUTE_DIFFERENCE;
                    if(diff>maxAbsoluteDiff){
                        differences++;
                    }
                }
            }
        }
    }

    delete[] outputs2;
    delete openclLayer;
    delete openclLayerCreator;
    delete env;
    delete envCreator;
    delete poolingLayerCont;
    delete poolingLayerOpennn;

    return differences;
}

int TestMaxPooling::testErrorComp(){
    ManuelTestData* manuelTestData=new ManuelTestData();

    //load errors input
    vector<float>vectorErrorsInput;
    util->loadStringToArray(manuelTestData->getMaxPoolingErrorsInputTest1(),&vectorErrorsInput);
    float*errorsInput=(float*)malloc(sizeof(float)*vectorErrorsInput.size());
    util->convertVectorToFloatArray(&vectorErrorsInput, errorsInput);

    //load errors output
    vector<float>vectorErrorsOutput;
    util->loadStringToArray(manuelTestData->getMaxPoolingErrorsOutputTest1(),&vectorErrorsOutput);
    float*errorsOutput=(float*)malloc(sizeof(float)*vectorErrorsOutput.size());
    util->convertVectorToFloatArray(&vectorErrorsOutput, errorsOutput);

    //load input values
    vector<float>vectorInputValues;
    util->loadStringToArray(manuelTestData->getMaxPoolingInputValuesTest1(),&vectorInputValues);
    float*inputValues=(float*)malloc(sizeof(float)*vectorInputValues.size());
    util->convertVectorToFloatArray(&vectorInputValues, inputValues);

    //load output values
    vector<float>vectorOutputValues;
    util->loadStringToArray(manuelTestData->getMaxPoolingOutputValuesTest1(),&vectorOutputValues);
    float*outputValues=(float*)malloc(sizeof(float)*vectorOutputValues.size());
    util->convertVectorToFloatArray(&vectorOutputValues, outputValues);

    string content=manuelTestData->getMaxPoolingStructureTest1();
    PoolingLayerCont* poolingLayerCont=new PoolingLayerCont();
    parseStructure(poolingLayerCont, content);
    poolingLayerCont->outputErrors=errorsOutput;
    poolingLayerCont->inputValues=inputValues;

    OpenCLEnvironmentCreator* envCreator=new OpenCLEnvironmentCreator();
    OpenCLEnvironment* env=envCreator->createOpenCLEnvironment(HardwareType::CPU);
    OpenCLLayerCreator* openclLayerCreator=new OpenCLLayerCreator();
    OpenCLLayer* openclLayer=openclLayerCreator->createMaxPoolLayer(env, poolingLayerCont->batchSize, poolingLayerCont->inputMaps, poolingLayerCont->inputHeight, poolingLayerCont->inputWidth, poolingLayerCont->outputHeight, poolingLayerCont->outputWidth, poolingLayerCont->poolingHeight, poolingLayerCont->poolingWidth, poolingLayerCont->strideHeight, poolingLayerCont->strideWidth);
    openclLayer->setInputs(env, poolingLayerCont->inputValues, poolingLayerCont->batchSize*poolingLayerCont->inputMaps*poolingLayerCont->inputHeight*poolingLayerCont->inputWidth);
    openclLayer->setOutputErrors(env, poolingLayerCont->outputErrors, poolingLayerCont->batchSize*poolingLayerCont->inputMaps*poolingLayerCont->outputHeight*poolingLayerCont->outputWidth);

    openclLayer->computeForward(env, poolingLayerCont->batchSize, poolingLayerCont->inputMaps);
    openclLayer->computeErrorComp(env, poolingLayerCont->batchSize);
    float*computedInputErrors=openclLayer->getErrorInputs(env, poolingLayerCont->batchSize, poolingLayerCont->inputMaps, poolingLayerCont->inputHeight, poolingLayerCont->inputWidth, NULL);

    int differences=0;
    for(int batch=0;batch<poolingLayerCont->batchSize;batch++){
        for(int map=0;map<poolingLayerCont->inputMaps;map++){
            for(int y=0;y<poolingLayerCont->inputHeight;y++){
                for(int x=0;x<poolingLayerCont->inputWidth;x++){
                    int index=x+poolingLayerCont->inputWidth*(y+poolingLayerCont->inputHeight*(map+poolingLayerCont->inputMaps*(batch)));
                    float diff=errorsInput[index]-computedInputErrors[index];
                    float maxAbsolutDifference=POOLING_LAYER_MAX_ABSOLUTE_DIFFERENCE;
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
    delete poolingLayerCont;
    delete[]errorsInput;
    delete[]outputValues;
    delete manuelTestData;

    return differences;
}

TEST(MaxPooling, FeedforwardProcess){
    TestMaxPooling* p=new TestMaxPooling();

    int testCases=TEST_CASES;
    for(int testCase=0;testCase<testCases;testCase++){
        EXPECT_EQ(0,p->testFeedForward());
    }

    delete p;
}

TEST(MaxPooling, ErrorComp){
    TestMaxPooling* p=new TestMaxPooling();

    p->testErrorComp();

    delete p;
}
