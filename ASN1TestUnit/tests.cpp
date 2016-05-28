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
    ASNInteger a(16);
    vector<char> aVect = a.serialize();
    string aStr(aVect.begin(), aVect.end());
    EXPECT_EQ(aStr, "000000100000000100010000");

    a = 13565;
    aVect = a.serialize();
    aStr.assign(aVect.begin(), aVect.end());
    EXPECT_EQ(aStr, "00000010000000100011010011111101");

    a = 8123456;
    aVect = a.serialize();
    aStr.assign(aVect.begin(), aVect.end());
    EXPECT_EQ(aStr, "0000001000000011011110111111010001000000");

    a = 1234567890;
    ASNInteger newA(a);
    aVect = newA.serialize();
    aStr.assign(aVect.begin(), aVect.end());
    EXPECT_EQ(aStr, "000000100000010001001001100101100000001011010010");
}



