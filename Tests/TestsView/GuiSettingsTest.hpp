#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "ControllerModule/MasterController.h"
#include "ControllerModule/ViewController.h"
#include "ViewModule/GUISettings.h"
#include "ViewModule/MainWindow.h"

using namespace testing;



class GUISettingsTest : public ::testing::Test {
public:
    static ViewController *testviewController;
    static MasterController *master;

//    GUISettingsTest(){
//        testviewController= new ViewController(master);
//    }

//    ~GUISettingsTest(){
//        delete testviewController;
//    }
    static void SetUpTestSuite() {
        testviewController = new ViewController(master);
    }

    static void TearDownTestSuite() {
        delete testviewController;
       delete master;
        //testviewController = NULL;
        //master = NULL;
    }
};

        ViewController * GUISettingsTest::testviewController = NULL;
        MasterController *GUISettingsTest::master;



