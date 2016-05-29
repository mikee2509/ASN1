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

TEST(ASNObjectTests, taglengthTest1)
{

    EXPECT_EQ(tlcheck(2, 0, 1, 1),  10001010000000);
    EXPECT_EQ(tlcheck(3, 1),  1100000001);
    EXPECT_EQ(tlcheck(10, 30), 101000011110);
    EXPECT_EQ(tlcheck(12, 8), 110000001000);
    EXPECT_EQ(tlcheck(16, 89, 1, 1), 11000011011001);
}

TEST(ASNObjectTests, taglengthTest2)
{
    vector<char> vect {'0','0','0',/**/'0','0','0','1','0',/**/'0',/**/'0','0','0','0','1','0','1'};
    ASNInteger one(0);
    one.taglength(vect);
    EXPECT_EQ(one.getTag(), 2);
    EXPECT_EQ(one.getLength(), 5);
}

TEST(ASNIntegerTests, serializeTest)
{
    ASNInteger a(16);
    vector<char> aVect = a.getData();
    string aStr(aVect.begin(), aVect.end());
    EXPECT_EQ(aStr, "000000100000000100010000");

    a = 13565;
    aVect = a.getData();
    aStr.assign(aVect.begin(), aVect.end());
    EXPECT_EQ(aStr, "00000010000000100011010011111101");

    a = 8123456;
    aVect = a.getData();
    aStr.assign(aVect.begin(), aVect.end());
    EXPECT_EQ(aStr, "0000001000000011011110111111010001000000");

    a = 1234567890;
    ASNInteger newA(a);
    aVect = newA.getData();
    aStr.assign(aVect.begin(), aVect.end());
    EXPECT_EQ(aStr, "000000100000010001001001100101100000001011010010");
}

TEST(ASNIntegerTests, deserializeTest)
{
    ASNInteger a;
    vector<char> aVect {'0','0','0','0','0','0','1','0',
                        '0','0','0','0','0','0','0','1',
                        '0','0','0','1','0','0','0','0'};
    vector<char> bVect = aVect;
    bVect.push_back('1');
    a.deserialize(bVect);
    EXPECT_EQ(a.getNumber(), 16);
    EXPECT_EQ(a.getTag(), 2);
    EXPECT_EQ(a.getLength(), 1);
    EXPECT_EQ(a.getData(), aVect);
    EXPECT_EQ(a.getConstructed(), false);
    EXPECT_EQ(a.getIndefinite(), false);


    vector<char> cVect {'0','0','0','0','0','0','1','0',
                        '0','0','0','0','0','1','0','0',
                        '0','1','0','0','1','0','0','1',
                        '1','0','0','1','0','1','1','0',
                        '0','0','0','0','0','0','1','0',
                        '1','1','0','1','0','0','1','0'};
    a.deserialize(cVect);
    EXPECT_EQ(a.getNumber(), 1234567890);
    EXPECT_EQ(a.getTag(), 2);
    EXPECT_EQ(a.getLength(), 4);
    EXPECT_EQ(a.getData(), cVect);
    EXPECT_EQ(a.getConstructed(), false);
    EXPECT_EQ(a.getIndefinite(), false);
}

TEST(ASNUTF8StringTests, serializeTest)
{
    string emptyStr = "";
    ASNUTF8String str(emptyStr);
    str = string("John");
    vector<char> test  {'0','0','0','0','1','1','0','0',
                        '0','0','0','0','0','1','0','0',
                        '0','1','0','0','1','0','1','0',
                        '0','1','1','0','1','1','1','1',
                        '0','1','1','0','1','0','0','0',
                        '0','1','1','0','1','1','1','0'};
    EXPECT_EQ(str.getData(), test);
}

TEST(ASNUTF8StringTests, deserializeTest)
{
    string temp;
    ASNUTF8String str(temp);
    vector<char> test  {'0','0','0','0','1','1','0','0',
                        '0','0','0','0','0','1','0','0',
                        '0','1','0','0','1','1','0','1',
                        '0','1','1','0','1','0','0','1',
                        '0','1','1','0','1','0','1','1',
                        '0','1','1','0','0','1','0','1'};
    str.deserialize(test);
    EXPECT_EQ(str.getStr(), string("Mike"));
}








