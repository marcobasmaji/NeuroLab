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
    HardwareModule/OpenVinoEnv.cpp \
    NNModule/Layers/ConvolutionLayer.cpp \
    NNModule/Layers/DenseLayer.cpp \
    NNModule/Layers/MaxPoolingLayer.cpp \
    NNModule/Layers/ReLULayer.cpp \
    NNModule/Layers/SoftmaxLayer.cpp \
    NNModule/NeuroLabNet.cpp \
    NNModule/PretrainedNN.cpp \
    ViewModule/GUISettings.cpp \
    ViewModule/MainWindow.cpp \
    main.cpp

HEADERS += \
    ControllerModule/ImagePareser.h \
    ControllerModule/MasterController.h \
    ControllerModule/NNController.h \
    ControllerModule/PredictionController.h \
    ControllerModule/ViewController.h \
    DataModule/Result.h \
    DataModule/Shape.h \
    HardwareModule/OpenVinoEnv.h \
    NNModule/Layers/ConvolutionLayer.h \
    NNModule/Layers/DenseLayer.h \
    NNModule/Layers/Layer.h \
    NNModule/Layers/MaxPoolingLayer.h \
    NNModule/Layers/ReLULayer.h \
    NNModule/Layers/SoftmaxLayer.h \
    NNModule/NeuralNet.h \
    NNModule/NeuroLabNet.h \
    NNModule/PretrainedNN.h \
    ViewModule/GUISettings.h \
    ViewModule/MainWindow.h

FORMS += \
    ViewModule/MainWindow.ui
LIBS += /usr/lib/libinference_engine.so \
        /usr/lib/libformat_reader.so

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../intel/openvino/deployment_tools/inference_engine/external/mkltiny_lnx/lib/release/ -lmkl_tiny_tbb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../intel/openvino/deployment_tools/inference_engine/external/mkltiny_lnx/lib/debug/ -lmkl_tiny_tbb
else:unix: LIBS += -L$$PWD/../../intel/openvino/deployment_tools/inference_engine/external/mkltiny_lnx/lib/ -lmkl_tiny_tbb

INCLUDEPATH += $$PWD/../../intel/openvino/deployment_tools/inference_engine/external/mkltiny_lnx/include
DEPENDPATH += $$PWD/../../intel/openvino/deployment_tools/inference_engine/external/mkltiny_lnx/include
