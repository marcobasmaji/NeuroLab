include(gtest_dependency.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ControllerModule/HardwareSurveillence.cpp \
    ControllerModule/MasterController.cpp \
    ControllerModule/NNController.cpp \
    ControllerModule/PredictionController.cpp \
    ControllerModule/ViewController.cpp \
    DataModule/WeightsAndBiasesCreator.cpp \
    HardwareModule/OpenCL/HardwareEnvironment.cpp \
    HardwareModule/OpenCL/HardwareType.cpp \
    HardwareModule/OpenCL/OpenCLLayerCreator.cpp \
    HardwareModule/OpenVinoEnv.cpp \
    HardwareModule/OpenCL/OpenCLEnvironment.cpp \
    HardwareModule/OpenCL/OpenCLEnvironmentCreator.cpp \
    HardwareModule/OpenCL/OpenCLLayer.cpp \
    HardwareModule/OpenCL/ReleaseCLObjectsManager.cpp \
    NNModule/Layers/ConvolutionLayer.cpp \
    NNModule/Layers/DenseLayer.cpp \
    NNModule/Layers/Loss.cpp \
    NNModule/Layers/MaxPoolingLayer.cpp \
    NNModule/Layers/ReLULayer.cpp \
    NNModule/Layers/SoftmaxLayer.cpp \
    NNModule/NeuroLabNet.cpp \
    NNModule/PretrainedNN.cpp \
    PredictionModule/DataResults.cpp \
    PredictionModule/Hardware.cpp \
    PredictionModule/Mode.cpp \
    PredictionModule/Prediction.cpp \
    PredictionModule/NeuroPrediction.cpp \
    PredictionModule/LowestPowerConsumption.cpp \
    PredictionModule/HighestPerformance.cpp \
    PredictionModule/HighestEfficiency.cpp \
    PredictionModule/AlexPrediction.cpp \
    Tests/TestsNN/Test_OpenVinoEnv.cpp \
    Tests/TestStarter.cpp \
    Tests/TestsExample/TestExample.cpp \
    Tests/TestsOpenCL/TestMaxPooling.cpp \
    Tests/TestsOpenCL/ManuelTestData.cpp \
    Tests/TestsOpenCL/TestConvolutional.cpp \
    Tests/TestsOpenCL/TestDense.cpp \
    Tests/TestsOpenCL/TestPadding.cpp \
    Tests/TestsOpenCL/TestRelu.cpp \
    Tests/TestsOpenCL/TestSoftmax.cpp \
    Tests/TestsOpenCL/Util.cpp \
    Tests/TestsView/GuiSettingsTest.cpp \
    ViewModule/GUISettings.cpp \
    ViewModule/MainWindow.cpp \
    ViewModule/TrainingPanel.cpp \
    main.cpp

HEADERS += \
    ControllerModule/HardwareElement.h \
    ControllerModule/HardwareSurveillence.h \
    ControllerModule/MasterController.h \
    ControllerModule/NNController.h \
    ControllerModule/PredictionController.h \
    ControllerModule/ViewController.h \
    DataModule/Result.h \
    DataModule/WeightsAndBiasesCreator.h \
    HardwareModule/OpenCL/HardwareEnvironment.hpp \
    HardwareModule/OpenCL/OpenCLLayerCreator.hpp \
    HardwareModule/OpenVinoEnv.h \
    HardwareModule/OpenCL/OpenCLEnvironment.hpp \
    HardwareModule/OpenCL/OpenCLEnvironmentCreator.hpp \
    HardwareModule/OpenCL/OpenCLLayer.hpp \
    HardwareModule/OpenCL/ReleaseCLObjectsManager.hpp \
    NNModule/Layers/ConvolutionLayer.h \
    NNModule/Layers/DenseLayer.h \
    NNModule/Layers/Layer.h \
    NNModule/Layers/Loss.h \
    NNModule/Layers/MaxPoolingLayer.h \
    NNModule/Layers/ReLULayer.h \
    NNModule/Layers/SoftmaxLayer.h \
    NNModule/NeuralNet.h \
    NNModule/NeuroLabNet.h \
    NNModule/PretrainedNN.h \
    PredictionModule/DataResults.h \
    PredictionModule/Hardware.h \
    PredictionModule/Mode.h \
    PredictionModule/Prediction.h \
    PredictionModule/NeuroPrediction.h \
    PredictionModule/LowestPowerConsumption.h \
    PredictionModule/HighestPerformance.h \
    PredictionModule/HighestEfficiency.h \
    PredictionModule/AlexPrediction.h \
    Tests/TestsNN/Test_OpenVinoEnv.h \
    Tests/TestStarter.hpp \
    Tests/TestsExample/TestExample.hpp \
    Tests/TestsOpenCL/TestMaxPooling.hpp \
    Tests/TestsOpenCL/ManuelTestData.hpp \
    Tests/TestsOpenCL/TestConvolutional.hpp \
    Tests/TestsOpenCL/TestDense.hpp \
    Tests/TestsOpenCL/TestPadding.hpp \
    Tests/TestsOpenCL/TestRelu.hpp \
    Tests/TestsOpenCL/TestSoftmax.hpp \
    Tests/TestsOpenCL/Util.hpp \
    Tests/TestsView/GuiSettingsTest.hpp \
    ViewModule/GUISettings.h \
    ViewModule/MainWindow.h \
    ViewModule/TrainingPanel.h

FORMS += \
    ViewModule/MainWindow.ui \
    ViewModule/TrainingPanel.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Libraries

LIBS += -L$$PWD/Tools/openvino/lib/ -linference_engine
LIBS += -L$$PWD/Tools/format_reader/lib/ -lformat_reader
LIBS += -L$$PWD/Tools/opencv2/lib/ -lopencv_core
LIBS += -L$$PWD/Tools/opencv2/lib/ -lopencv_imgcodecs
LIBS += -L$$PWD/Tools/opencv2/lib/ -lopencv_imgproc
LIBS += -L$$PWD/Tools/tbb/lib -ltbb
LIBS += -L$$PWD/Tools/tbb/lib -ltbbmalloc
LIBS += -L$$PWD/Tools/opencl/lib/ -lOpenCL
LIBS += -L$$PWD/Tools/opennn/lib/ -lopennn



# Headers

INCLUDEPATH += $$PWD/Tools/openvino/include
DEPENDPATH += $$PWD/Tools/openvino/include

INCLUDEPATH += $$PWD/Tools/opencv2/include
DEPENDPATH += $$PWD/Tools/opencv2/include

INCLUDEPATH += $$PWD/Tools/opennn
DEPENDPATH += $$PWD/Tools/opennn

INCLUDEPATH += Tools/opennn/eigen

RESOURCES += \
    HardwareModule/OpenCL/README.me \
    HardwareModule/OpenCL/kernels/Conv.cl \
    HardwareModule/OpenCL/kernels/Dense.cl \
    HardwareModule/OpenCL/kernels/MaxPool.cl \
    HardwareModule/OpenCL/kernels/Pad.cl \
    HardwareModule/OpenCL/kernels/Relu.cl \
    HardwareModule/OpenCL/kernels/Softmax.cl \
    ViewModule/welcome_panel.png

# OpenMP library

win32:!win32-g++{
QMAKE_CXXFLAGS += -openmp
QMAKE_LFLAGS  += -openmp
}

unix:!macx{
QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS += -fopenmp

QMAKE_CXXFLAGS+= -std=c++11
QMAKE_LFLAGS += -std=c++11
}
