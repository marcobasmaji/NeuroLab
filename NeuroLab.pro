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
    ControllerModule/ImagePareser.cpp \
    ControllerModule/MasterController.cpp \
    ControllerModule/NNController.cpp \
    ControllerModule/PredictionController.cpp \
    ControllerModule/ViewController.cpp \
    DataModule/Shape.cpp \
    HardwareModule/OpenCL/HardwareEnvironment.cpp \
    HardwareModule/OpenCL/HardwareType.cpp \
    HardwareModule/OpenCL/OpenCLEnvironment.cpp \
    HardwareModule/OpenCL/OpenCLEnvironmentCreator.cpp \
    HardwareModule/OpenCL/OpenCLLayer.cpp \
    HardwareModule/OpenCL/OpenCLLayerCreator.cpp \
    HardwareModule/OpenCL/ReleaseCLObjectsManager.cpp \
    HardwareModule/OpenVinoEnv.cpp \
    NNModule/Layers/ConvolutionLayer.cpp \
    NNModule/Layers/DenseLayer.cpp \
    NNModule/Layers/Loss.cpp \
    NNModule/Layers/MaxPoolingLayer.cpp \
    NNModule/Layers/ReLULayer.cpp \
    NNModule/Layers/SoftmaxLayer.cpp \
    NNModule/NeuroLabNet.cpp \
    NNModule/PretrainedNN.cpp \
    PredictionModule/Prediction.cpp \
    PredictionModule/NeuroPrediction.cpp \
    PredictionModule/LowestPowerConsumption.cpp \
    PredictionModule/HighestPerformance.cpp \
    PredictionModule/HighestEfficiency.cpp \
    PredictionModule/AlexPrediction.cpp \
    ViewModule/GUISettings.cpp \
    ViewModule/MainWindow.cpp \
    ViewModule/WellcomePanel.cpp \
    main.cpp

HEADERS += \
    ControllerModule/HardwareElement.h \
    ControllerModule/ImagePareser.h \
    ControllerModule/MasterController.h \
    ControllerModule/NNController.h \
    ControllerModule/PredictionController.h \
    ControllerModule/ViewController.h \
    DataModule/Result.h \
    DataModule/Shape.h \
    HardwareModule/OpenCL/HardwareEnvironment.hpp \
    HardwareModule/OpenCL/OpenCLEnvironment.hpp \
    HardwareModule/OpenCL/OpenCLEnvironmentCreator.hpp \
    HardwareModule/OpenCL/OpenCLLayer.hpp \
    HardwareModule/OpenCL/OpenCLLayerCreator.hpp \
    HardwareModule/OpenCL/ReleaseCLObjectsManager.hpp \
    HardwareModule/OpenVinoEnv.h \
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
    PredictionModule/Prediction.h \
    PredictionModule/NeuroPrediction.h \
    PredictionModule/LowestPowerConsumption.h \
    PredictionModule/HighestPerformance.h \
    PredictionModule/HighestEfficiency.h \
    PredictionModule/AlexPrediction.h \
    ViewModule/GUISettings.h \
    ViewModule/MainWindow.h \
    ViewModule/WellcomePanel.h

FORMS += \
    ViewModule/MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Libraries


LIBS += -L$$PWD/Tools/openvino/lib/ -linference_engine
LIBS += -L$$PWD/Tools/format_reader/ -lformat_reader




# Headers

INCLUDEPATH += $$PWD/Tools/openvino/include
DEPENDPATH += $$PWD/Tools/openvino/include

INCLUDEPATH += $$PWD/Tools/opencv2/include
DEPENDPATH += $$PWD/Tools/opencv2/include


unix:!macx: LIBS += -L$$PWD/../../intel/openvino/opencv/lib/ -lopencv_imgcodecs



unix:!macx: LIBS += -L$$PWD/../../intel/openvino/opencv/lib/ -lopencv_core

INCLUDEPATH += $$PWD/../../intel/openvino/opencv/include
DEPENDPATH += $$PWD/../../intel/openvino/opencv/include



INCLUDEPATH += $$PWD/../../intel/openvino/opencv/include
DEPENDPATH += $$PWD/../../intel/openvino/opencv/include

unix:!macx: LIBS += -L$$PWD/../../intel/openvino/opencv/lib/ -lopencv_imgproc

INCLUDEPATH += $$PWD/../../intel/openvino/opencv/include
DEPENDPATH += $$PWD/../../intel/openvino/opencv/include

unix:!macx: LIBS +=  -lOpenCL

INCLUDEPATH += $$PWD/Tools/opencl/include
DEPENDPATH += $$PWD/Tools/opencl/include

DISTFILES += \
    HardwareModule/OpenCL/README.me



unix:!macx: LIBS += -L$$PWD/../../intel/openvino/opencv/lib/ -lopencv_highgui

INCLUDEPATH += $$PWD/../../intel/openvino/opencv/include
DEPENDPATH += $$PWD/../../intel/openvino/opencv/include
