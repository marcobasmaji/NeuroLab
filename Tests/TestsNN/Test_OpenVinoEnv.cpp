#include "Test_OpenVinoEnv.h"
#include "HardwareModule/OpenVinoEnv.h"


TEST(OpenVino, CombinationOfHardware)
{
    OpenVinoEnv env;
    env.setDistribution({{"CPU",15},{"MYRIAD",12}});
    vector<pair<string,int>> distribtuion = env.getDistribution();

    EXPECT_EQ(2,distribtuion.size());
    EXPECT_EQ("MULTI:CPU,MYRIAD",distribtuion.front().first);
    EXPECT_EQ(24,distribtuion.front().second);
    EXPECT_EQ(3,distribtuion.back().second);
    EXPECT_EQ("CPU",distribtuion.back().first);

    env.setDistribution({{"CPU",22}});
    distribtuion = env.getDistribution();

    EXPECT_EQ(1,distribtuion.size());
    EXPECT_EQ(distribtuion.front().first,distribtuion.back().first);
    EXPECT_EQ("CPU",distribtuion.back().first);
    EXPECT_EQ(22,distribtuion.back().second);
}
