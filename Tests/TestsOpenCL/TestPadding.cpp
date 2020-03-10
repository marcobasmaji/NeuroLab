#include "Tests/TestsOpenCL/TestPadding.hpp"

#include "ie_builders.hpp"
#include "ie_network.hpp"
#include "ie_iexecutable_network.hpp"
#include <iostream>
#include "ie_core.hpp"

using namespace std;

#define TEST_CASES 10;

//Pooling Layer
#define PADDING_LAYER_MAX_BATCH_SIZE 10;
#define PADDING_LAYER_MAX_INPUT_HEIGHT 20;
#define PADDING_LAYER_MAX_INPUT_WIDTH 20;
#define PADDING_LAYER_MAX_INPUT_MAPS 10;
#define PADDING_LAYER_MAX_PADDING_HEIGHT 5;
#define PADDING_LAYER_MAX_PADDING_WIDTH 5;
#define PADDING_LAYER_MAX_ABSOLUTE_DIFFERENCE 0.0001;

void TestPadding::createRandomPaddingLayerCont(PaddingLayerCont* paddingLayerCont){
    //create parameters
    int maxBatchSize=PADDING_LAYER_MAX_BATCH_SIZE;
    int maxInputHeight=PADDING_LAYER_MAX_INPUT_HEIGHT;
    int maxInputWidth=PADDING_LAYER_MAX_INPUT_WIDTH;
    int maxInputMaps=PADDING_LAYER_MAX_INPUT_MAPS;
    int maxPaddingHeight=PADDING_LAYER_MAX_PADDING_HEIGHT;
    int maxPaddingWidth=PADDING_LAYER_MAX_PADDING_WIDTH;

    int batchSize=util->getRandomIntValue(1,maxBatchSize);
    int inputHeight=util->getRandomIntValue(1,maxInputHeight);
    int inputWidth=util->getRandomIntValue(1,maxInputWidth);
    int inputMaps=util->getRandomIntValue(1,maxInputMaps);
    int paddingWidth=util->getRandomIntValue(1,maxPaddingWidth);
    int paddingHeight=util->getRandomIntValue(1,maxPaddingHeight);
    int outputHeight=paddingHeight*2+inputHeight;
    int outputWidth=paddingWidth*2+inputWidth;

    int length;
    length=inputMaps*inputHeight*inputWidth*batchSize;
    float*inputValues=(float*)malloc(sizeof(float)*length);
    util->createRandomValues(inputValues, length);

    length=inputMaps*(inputHeight+2*paddingHeight)*(inputWidth+2*paddingWidth)*batchSize;
    float*outputErrors=(float*)malloc(sizeof(float)*length);
    util->createRandomValues(outputErrors, length);

    paddingLayerCont->batchSize=batchSize;
    paddingLayerCont->inputMaps=inputMaps;
    paddingLayerCont->inputHeight=inputHeight;
    paddingLayerCont->inputWidth=inputWidth;
    paddingLayerCont->paddingHeight=paddingHeight;
    paddingLayerCont->paddingWidth=paddingWidth;
    paddingLayerCont->inputValues=inputValues;
    paddingLayerCont->outputErrors=outputErrors;
    paddingLayerCont->outputHeight=outputHeight;
    paddingLayerCont->outputWidth=outputWidth;
}

int TestPadding::testFeedForward(){
    PaddingLayerCont*paddingLayerCont=new PaddingLayerCont();
    createRandomPaddingLayerCont(paddingLayerCont);

    OpenCLEnvironmentCreator* envCreator=new OpenCLEnvironmentCreator();
    OpenCLEnvironment* env=envCreator->createOpenCLEnvironment(HardwareType::CPU);
    OpenCLLayerCreator* openclLayerCreator=new OpenCLLayerCreator();
    OpenCLLayer* openclLayer=openclLayerCreator->createPadLayer(env, paddingLayerCont->batchSize, paddingLayerCont->inputMaps, paddingLayerCont->inputHeight,paddingLayerCont->inputWidth, paddingLayerCont->paddingHeight,paddingLayerCont->paddingWidth);
    openclLayer->setInputs(env, paddingLayerCont->inputValues, paddingLayerCont->batchSize*paddingLayerCont->inputMaps*paddingLayerCont->inputHeight*paddingLayerCont->inputWidth);

    //calculate outputs
    openclLayer->computeForward(env, paddingLayerCont->batchSize, paddingLayerCont->inputMaps);
    float*outputs2=openclLayer->getOutputs(env, paddingLayerCont->batchSize, paddingLayerCont->inputMaps, paddingLayerCont->outputHeight, paddingLayerCont->outputWidth, NULL);

    int maxAbsoluteDifference=PADDING_LAYER_MAX_ABSOLUTE_DIFFERENCE;

    //compare outputs
    int differences=0;

    for(int batch=0;batch<paddingLayerCont->batchSize;batch++){
        for(int map=0;map<paddingLayerCont->inputMaps;map++){
            for(int y=0;y<paddingLayerCont->outputHeight;y++){
                for(int x=0;x<paddingLayerCont->outputWidth;x++){
                    int indexOut=x+paddingLayerCont->outputWidth*(y+paddingLayerCont->outputHeight*(map+paddingLayerCont->inputMaps*(batch)));
                    float valueOut=outputs2[indexOut];

                    if(x<paddingLayerCont->paddingWidth || y<paddingLayerCont->paddingHeight || x>=paddingLayerCont->paddingWidth+paddingLayerCont->inputWidth || y>=paddingLayerCont->paddingHeight+paddingLayerCont->inputHeight){
                        if(valueOut!=0){
                            differences++;
                        }
                    }else{
                        int indexIn=x-paddingLayerCont->paddingWidth+paddingLayerCont->inputWidth*(y-paddingLayerCont->paddingHeight+paddingLayerCont->inputHeight*(map+paddingLayerCont->inputMaps*(batch)));
                        float valueIn=paddingLayerCont->inputValues[indexIn];
                        if(abs(valueIn!=valueOut)>maxAbsoluteDifference){
                            differences++;
                        }
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
    delete paddingLayerCont;

    return differences;
}

int TestPadding::testErrorComp(){
    PaddingLayerCont*paddingLayerCont=new PaddingLayerCont();
    createRandomPaddingLayerCont(paddingLayerCont);

    OpenCLEnvironmentCreator* envCreator=new OpenCLEnvironmentCreator();
    OpenCLEnvironment* env=envCreator->createOpenCLEnvironment(HardwareType::CPU);
    OpenCLLayerCreator* openclLayerCreator=new OpenCLLayerCreator();
    OpenCLLayer* openclLayer=openclLayerCreator->createPadLayer(env, paddingLayerCont->batchSize, paddingLayerCont->inputMaps, paddingLayerCont->inputHeight,paddingLayerCont->inputWidth, paddingLayerCont->paddingHeight,paddingLayerCont->paddingWidth);
    int length=paddingLayerCont->batchSize*paddingLayerCont->inputMaps*paddingLayerCont->inputHeight*paddingLayerCont->inputWidth;
    openclLayer->setInputs(env, paddingLayerCont->inputValues, length);
    length=paddingLayerCont->batchSize*paddingLayerCont->inputMaps*paddingLayerCont->outputHeight*paddingLayerCont->outputWidth;
    openclLayer->setOutputErrors(env, paddingLayerCont->outputErrors, length);

    //calculate input errors
    openclLayer->computeForward(env, paddingLayerCont->batchSize, paddingLayerCont->inputMaps);
    openclLayer->computeErrorComp(env, paddingLayerCont->batchSize);
    float*inputErrors=openclLayer->getErrorInputs(env, paddingLayerCont->batchSize, paddingLayerCont->inputMaps, paddingLayerCont->inputHeight, paddingLayerCont->inputWidth, NULL);

    int maxAbsoluteDifference=PADDING_LAYER_MAX_ABSOLUTE_DIFFERENCE;

    //compare outputs
    int differences=0;

    for(int batch=0;batch<paddingLayerCont->batchSize;batch++){
        for(int map=0;map<paddingLayerCont->inputMaps;map++){
            for(int y=0;y<paddingLayerCont->inputHeight;y++){
                for(int x=0;x<paddingLayerCont->inputWidth;x++){
                    int indexIn=x+paddingLayerCont->inputWidth*(y+paddingLayerCont->inputHeight*(map+paddingLayerCont->inputMaps*(batch)));
                    float valueIn=inputErrors[indexIn];
                    int indexOut=x+paddingLayerCont->paddingWidth+paddingLayerCont->outputWidth*(y+paddingLayerCont->paddingHeight+paddingLayerCont->outputHeight*(map+paddingLayerCont->inputMaps*(batch)));
                    float valueOut=paddingLayerCont->outputErrors[indexOut];

                    if(abs(valueIn-valueOut)>maxAbsoluteDifference){
                        differences++;
                    }
                }
            }
        }
    }

    delete[] inputErrors;
    delete openclLayer;
    delete openclLayerCreator;
    delete env;
    delete envCreator;
    delete paddingLayerCont;

    return differences;
}

TEST(Padding, FeedforwardProcess){
    TestPadding* p=new TestPadding();

    int testCases=TEST_CASES;
    for(int testCase=0;testCase<testCases;testCase++){
        EXPECT_EQ(0,p->testFeedForward());
    }

    delete p;
}

TEST(Padding, ErrorComp){
    TestPadding* p=new TestPadding();

    int testCases=TEST_CASES;
    for(int testCase=0;testCase<testCases;testCase++){
        EXPECT_EQ(0,p->testErrorComp());
    }

    delete p;
}
