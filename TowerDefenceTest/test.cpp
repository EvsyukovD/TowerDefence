#include "pch.h"
#include "../Classes/TDGame/include/TowerDefence.h"
#include "../Classes/TDGame/include/TDObject.h"
TEST(TDObject, Constructor){
	TowerDefence::TDObject object;

}
TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
