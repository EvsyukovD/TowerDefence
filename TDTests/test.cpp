#include "pch.h"
USING_NS_CC;
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
TEST(Enemy, Constructor) {
        
        //TowerDefence::Enemy e(,"");
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
