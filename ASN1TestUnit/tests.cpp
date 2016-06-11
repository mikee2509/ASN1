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
    EXPECT_EQ(a.getTag(), 2);
    EXPECT_EQ(a.getLength(), 1);
    EXPECT_EQ(a.getData(), aVect);
    EXPECT_EQ(a.getConstructed(), false);
    EXPECT_EQ(a.getIndefinite(), false);

    a = 13565;
    aVect = a.getData();
    aStr.assign(aVect.begin(), aVect.end());
    EXPECT_EQ(aStr, "00000010000000100011010011111101");
    EXPECT_EQ(a.getTag(), 2);
    EXPECT_EQ(a.getLength(), 2);
    EXPECT_EQ(a.getData(), aVect);
    EXPECT_EQ(a.getConstructed(), false);
    EXPECT_EQ(a.getIndefinite(), false);

    a = 8123456;
    aVect = a.getData();
    aStr.assign(aVect.begin(), aVect.end());
    EXPECT_EQ(aStr, "0000001000000011011110111111010001000000");
    EXPECT_EQ(a.getLength(), 3);

    a = 1234567890;
    ASNInteger newA(a);
    aVect = newA.getData();
    aStr.assign(aVect.begin(), aVect.end());
    EXPECT_EQ(aStr, "000000100000010001001001100101100000001011010010");
    EXPECT_EQ(a.getLength(), 4);
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
                        '1','1','0','1','0','0','1','0', '1'};
    a.deserialize(cVect);
    cVect.pop_back();
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

    vector<char> test  {'0','0','0','0','1','1','0','0',
                        '0','0','0','0','0','0','0','0'};

    EXPECT_EQ(str.getData(), test);
    EXPECT_EQ(str.getStr(), string(""));
    EXPECT_EQ(str.getTag(), 12);
    EXPECT_EQ(str.getLength(), 0);
    EXPECT_EQ(str.getConstructed(), false);
    EXPECT_EQ(str.getIndefinite(), false);


    str = string("John");
    vector<char> test2  {'0','0','0','0','1','1','0','0',
                        '0','0','0','0','0','1','0','0',
                        '0','1','0','0','1','0','1','0',
                        '0','1','1','0','1','1','1','1',
                        '0','1','1','0','1','0','0','0',
                        '0','1','1','0','1','1','1','0'};
    EXPECT_EQ(str.getData(), test2);
    EXPECT_EQ(str.getStr(), string("John"));
    EXPECT_EQ(str.getTag(), 12);
    EXPECT_EQ(str.getLength(), 4);
    EXPECT_EQ(str.getConstructed(), false);
    EXPECT_EQ(str.getIndefinite(), false);
}

TEST(ASNUTF8StringTests, deserializeTest)
{
    string temp;
    ASNUTF8String str(temp);
    vector<char> test  {'0','0','0','0','1','1','0','0',
                        '0','0','0','0','0','0','0','0'};
    str.deserialize(test);
    EXPECT_EQ(str.getStr(), string(""));
    EXPECT_EQ(str.getData(), test);
    EXPECT_EQ(str.getTag(), 12);
    EXPECT_EQ(str.getLength(), 0);
    EXPECT_EQ(str.getConstructed(), false);
    EXPECT_EQ(str.getIndefinite(), false);

    vector<char> test2 {'0','0','0','0','1','1','0','0',
                        '0','0','0','0','0','1','0','0',
                        '0','1','0','0','1','1','0','1',
                        '0','1','1','0','1','0','0','1',
                        '0','1','1','0','1','0','1','1',
                        '0','1','1','0','0','1','0','1', '1'};
    str.deserialize(test2);
    test2.pop_back();
    EXPECT_EQ(str.getStr(), string("Mike"));
    EXPECT_EQ(str.getData(), test2);
    EXPECT_EQ(str.getTag(), 12);
    EXPECT_EQ(str.getLength(), 4);
    EXPECT_EQ(str.getConstructed(), false);
    EXPECT_EQ(str.getIndefinite(), false);
}

TEST(ASNBitstringTests, serializeTest)
{
    string str = "10101010111100001";
    ASNBitstring one(str);
    vector <char> test {'0','0','0','0','0','0','1','1',
                        '0','0','0','0','0','1','0','0',
                        '0','0','0','0','0','1','1','1',
                        '1','0','1','0','1','0','1','0',
                        '1','1','1','1','0','0','0','0',
                        '1','0','0','0','0','0','0','0'};
    EXPECT_EQ(one.getData(), test);
    EXPECT_EQ(one.getStr(), str);
    EXPECT_EQ(one.getTag(), 3);
    EXPECT_EQ(one.getLength(), 4);
    EXPECT_EQ(one.getConstructed(), false);
    EXPECT_EQ(one.getIndefinite(), false);


    str = "101";
    one = str;
    test = {'0','0','0','0','0','0','1','1',
            '0','0','0','0','0','0','1','0',
            '0','0','0','0','0','1','0','1',
            '1','0','1','0','0','0','0','0'};
    EXPECT_EQ(one.getData(), test);
    EXPECT_EQ(one.getStr(), str);
    EXPECT_EQ(one.getTag(), 3);
    EXPECT_EQ(one.getLength(), 2);
    EXPECT_EQ(one.getConstructed(), false);
    EXPECT_EQ(one.getIndefinite(), false);
}

TEST(ASNBitstringTests, deserializeTest)
{
    string temp;
    ASNBitstring str(temp);
    vector<char> test  {'0','0','0','0','0','0','1','1',
                        '0','0','0','0','0','1','0','0',
                        '0','0','0','0','0','1','0','1',
                        '1','1','1','0','1','0','0','1',
                        '0','1','1','0','1','0','1','1',
                        '0','1','1','1','0','0','0','0', '1'};
    str.deserialize(test);
    test.pop_back();
    EXPECT_EQ(str.getStr(), string("1110100101101011011"));
    EXPECT_EQ(str.getData(), test);
    EXPECT_EQ(str.getTag(), 3);
    EXPECT_EQ(str.getLength(), 4);
    EXPECT_EQ(str.getConstructed(), false);
    EXPECT_EQ(str.getIndefinite(), false);
}

TEST(ASNEnumeratedTests, serializeTest)
{
    ASNEnumerated a(16);
    vector<char> aVect = a.getData();
    string aStr(aVect.begin(), aVect.end());
    EXPECT_EQ(aStr, "000010100000000100010000");
    EXPECT_EQ(a.getTag(), 10);
    EXPECT_EQ(a.getLength(), 1);
    EXPECT_EQ(a.getData(), aVect);
    EXPECT_EQ(a.getConstructed(), false);
    EXPECT_EQ(a.getIndefinite(), false);

    a = 13565;
    aVect = a.getData();
    aStr.assign(aVect.begin(), aVect.end());
    EXPECT_EQ(aStr, "00001010000000100011010011111101");
    EXPECT_EQ(a.getTag(), 10);
    EXPECT_EQ(a.getLength(), 2);
    EXPECT_EQ(a.getData(), aVect);
    EXPECT_EQ(a.getConstructed(), false);
    EXPECT_EQ(a.getIndefinite(), false);

    a = 8123456;
    aVect = a.getData();
    aStr.assign(aVect.begin(), aVect.end());
    EXPECT_EQ(aStr, "0000101000000011011110111111010001000000");
    EXPECT_EQ(a.getLength(), 3);

    a = 1234567890;
    ASNEnumerated newA(a);
    aVect = newA.getData();
    aStr.assign(aVect.begin(), aVect.end());
    EXPECT_EQ(aStr, "000010100000010001001001100101100000001011010010");
    EXPECT_EQ(a.getLength(), 4);
}

TEST(ASNEnumeratedTests, deserializeTest)
{
    ASNEnumerated a;
    vector<char> aVect {'0','0','0','0','1','0','1','0',
                        '0','0','0','0','0','0','0','1',
                        '0','0','0','1','0','0','0','0'};
    vector<char> bVect = aVect;
    bVect.push_back('1');
    a.deserialize(bVect);
    EXPECT_EQ(a.getNumber(), 16);
    EXPECT_EQ(a.getTag(), 10);
    EXPECT_EQ(a.getLength(), 1);
    EXPECT_EQ(a.getData(), aVect);
    EXPECT_EQ(a.getConstructed(), false);
    EXPECT_EQ(a.getIndefinite(), false);


    vector<char> cVect {'0','0','0','0','1','0','1','0',
                        '0','0','0','0','0','1','0','0',
                        '0','1','0','0','1','0','0','1',
                        '1','0','0','1','0','1','1','0',
                        '0','0','0','0','0','0','1','0',
                        '1','1','0','1','0','0','1','0', '1'};
    a.deserialize(cVect);
    cVect.pop_back();
    EXPECT_EQ(a.getNumber(), 1234567890);
    EXPECT_EQ(a.getTag(), 10);
    EXPECT_EQ(a.getLength(), 4);
    EXPECT_EQ(a.getData(), cVect);
    EXPECT_EQ(a.getConstructed(), false);
    EXPECT_EQ(a.getIndefinite(), false);
}

TEST(ASNSequenceTests, serializeTest)
{
    string str = "John";
    string bitstr = "10101010111100001";
    shared_ptr<ASNObject> i1(new IASNInteger(1));
    shared_ptr<ASNObject> e2(new IASNEnumerated(256));
    shared_ptr<ASNObject> s3(new IASNUTF8String(str));
    shared_ptr<ASNObject> b4(new IASNBitstring(bitstr));

    vector<shared_ptr<ASNObject>> container;

    container.push_back(i1);
    container.push_back(e2);
    container.push_back(s3);
    container.push_back(b4);

    ASNSequence one(container);

    vector<char> test  {'0','0','1','1','0','0','0','0',
                        '0','0','0','1','0','0','1','1',

                        '0','0','0','0','0','0','1','0',
                        '0','0','0','0','0','0','0','1',
                        '0','0','0','0','0','0','0','1',

                        '0','0','0','0','1','0','1','0',
                        '0','0','0','0','0','0','1','0',
                        '0','0','0','0','0','0','0','1',
                        '0','0','0','0','0','0','0','0',

                        '0','0','0','0','1','1','0','0',
                        '0','0','0','0','0','1','0','0',
                        '0','1','0','0','1','0','1','0',
                        '0','1','1','0','1','1','1','1',
                        '0','1','1','0','1','0','0','0',
                        '0','1','1','0','1','1','1','0',

                        '0','0','0','0','0','0','1','1',
                        '0','0','0','0','0','1','0','0',
                        '0','0','0','0','0','1','1','1',
                        '1','0','1','0','1','0','1','0',
                        '1','1','1','1','0','0','0','0',
                        '1','0','0','0','0','0','0','0'};

    EXPECT_EQ(one.getData(), test);
    EXPECT_EQ(one.getLength(), 19);
    EXPECT_EQ(one.getTag(), 16);
    EXPECT_EQ(one.getConstructed(), true);
    EXPECT_EQ(one.getIndefinite(), false);
}

TEST(ASNSequenceTests, deserializeTest)
{
    vector<char> test  {'0','0','1','1','0','0','0','0',
                        '0','0','0','1','0','0','1','1',

                        '0','0','0','0','0','0','1','0',
                        '0','0','0','0','0','0','0','1',
                        '0','0','0','0','0','0','0','1',

                        '0','0','0','0','1','0','1','0',
                        '0','0','0','0','0','0','1','0',
                        '0','0','0','0','0','0','0','1',
                        '0','0','0','0','0','0','0','0',

                        '0','0','0','0','1','1','0','0',
                        '0','0','0','0','0','1','0','0',
                        '0','1','0','0','1','0','1','0',
                        '0','1','1','0','1','1','1','1',
                        '0','1','1','0','1','0','0','0',
                        '0','1','1','0','1','1','1','0',

                        '0','0','0','0','0','0','1','1',
                        '0','0','0','0','0','1','0','0',
                        '0','0','0','0','0','1','1','1',
                        '1','0','1','0','1','0','1','0',
                        '1','1','1','1','0','0','0','0',
                        '1','0','0','0','0','0','0','0'};
    ASNSequence one;
    one.deserialize(test);
    EXPECT_EQ(one.getData(), test);
    EXPECT_EQ(one.getLength(), 19);
    EXPECT_EQ(one.getTag(), 16);
    EXPECT_EQ(one.getConstructed(), true);
    EXPECT_EQ(one.getIndefinite(), false);


    vector<char> i1 {'0','0','0','0','0','0','1','0',
                     '0','0','0','0','0','0','0','1',
                     '0','0','0','0','0','0','0','1'};

    EXPECT_EQ(one.getObjects()[0]->getData(), i1);
    EXPECT_EQ(one.getObjects()[0]->getTag(), 2);
    EXPECT_EQ(one.getObjects()[0]->getLength(), 1);
    EXPECT_EQ(dynamic_pointer_cast<ASNInteger>(one.getObjects()[0])->getNumber(), 1);


    vector<char> e2 {'0','0','0','0','1','0','1','0',
                     '0','0','0','0','0','0','1','0',
                     '0','0','0','0','0','0','0','1',
                     '0','0','0','0','0','0','0','0'};

    EXPECT_EQ(one.getObjects()[1]->getData(), e2);
    EXPECT_EQ(one.getObjects()[1]->getTag(), 10);
    EXPECT_EQ(one.getObjects()[1]->getLength(), 2);
    EXPECT_EQ(dynamic_pointer_cast<ASNEnumerated>(one.getObjects()[1])->getNumber(), 256);


    vector<char> s3 {'0','0','0','0','1','1','0','0',
                     '0','0','0','0','0','1','0','0',
                     '0','1','0','0','1','0','1','0',
                     '0','1','1','0','1','1','1','1',
                     '0','1','1','0','1','0','0','0',
                     '0','1','1','0','1','1','1','0'};

    EXPECT_EQ(one.getObjects()[2]->getData(), s3);
    EXPECT_EQ(one.getObjects()[2]->getTag(), 12);
    EXPECT_EQ(one.getObjects()[2]->getLength(), 4);
    EXPECT_EQ(dynamic_pointer_cast<ASNUTF8String>(one.getObjects()[2])->getStr(), string("John"));


    vector<char> b4 {'0','0','0','0','0','0','1','1',
                     '0','0','0','0','0','1','0','0',
                     '0','0','0','0','0','1','1','1',
                     '1','0','1','0','1','0','1','0',
                     '1','1','1','1','0','0','0','0',
                     '1','0','0','0','0','0','0','0'};

    EXPECT_EQ(one.getObjects()[3]->getData(), b4);
    EXPECT_EQ(one.getObjects()[3]->getTag(), 3);
    EXPECT_EQ(one.getObjects()[3]->getLength(), 4);
    EXPECT_EQ(dynamic_pointer_cast<ASNBitstring>(one.getObjects()[3])->getStr(), string("10101010111100001"));
}





