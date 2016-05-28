#include "tests.h"
using namespace std;
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

long tlcheck(int tag, int length, bool isConstructed=0, bool isIndefinite=0)
{
    ASNInteger one(0);
    stringstream stream;
    long check;
    vector<char> temp = one.taglength(tag, length, isConstructed, isIndefinite);
    string str(temp.begin(), temp.end());
    stream << str;
    stream >> check;
    stream.str(string());
    stream.clear();
    return check;
}

TEST(ASNObjectTests, taglengthTest)
{

    EXPECT_EQ(tlcheck(2, 0, 1, 1),  10001010000000);
    EXPECT_EQ(tlcheck(3, 1),  1100000001);
    EXPECT_EQ(tlcheck(10, 30), 101000011110);
    EXPECT_EQ(tlcheck(12, 8), 110000001000);
    EXPECT_EQ(tlcheck(16, 89, 1, 1), 11000011011001);
}

TEST(ASNIntegerTests, serializeTest)
{
    ASNInteger wiek(16);
    vector<char> wiekVect = wiek.serialize();
    string wiekStr(wiekVect.begin(), wiekVect.end());
    EXPECT_EQ(wiekStr, "000000100000000100010000");
}
