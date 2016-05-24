#include "tests.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(first, one)
{
    Student nowy(3);
    EXPECT_EQ(nowy.getNo(), 3);
}
