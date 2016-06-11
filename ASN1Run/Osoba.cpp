#include "Osoba.h"

using namespace std;

Osoba::Osoba(string name, string surname, int age, bool gender, string interests)
{
    if(interests.size()!=4 || any_of(interests.begin(), interests.end(), [](char c) { return c!='1' && c!='0'; } ))
        throw interests_error("Niepoprawny wybor zainteresowan");

    shared_ptr<ASNObject> n1(new IASNUTF8String(name));
    shared_ptr<ASNObject> s2(new IASNUTF8String(surname));
    shared_ptr<ASNObject> a3(new IASNInteger(age));
    shared_ptr<ASNObject> g4(new IASNEnumerated((int)gender));
    shared_ptr<ASNObject> i5(new IASNBitstring(interests));

    this->push_back(n1);
    this->push_back(s2);
    this->push_back(a3);
    this->push_back(g4);
    this->push_back(i5);
}


void Osoba::wyswietl()
{
    cout << "Imie:     " << dynamic_pointer_cast<IASNUTF8String>(this->getObjects()[0])->getStr() << endl;
    cout << "Nazwisko: " << dynamic_pointer_cast<IASNUTF8String>(this->getObjects()[1])->getStr() << endl;
    cout << "Plec:     ";
    if(dynamic_pointer_cast<IASNEnumerated>(this->getObjects()[3])->getNumber()) cout << "mezczyzna" << endl;
    else cout << "kobieta" << endl;

    string wiek = to_string(dynamic_pointer_cast<IASNInteger>(this->getObjects()[2])->getNumber());
    cout << "Wiek:     " << wiek;
    if(wiek=="1") cout << " rok" << endl;
    else if (wiek[wiek.length()-1]=='2' || wiek[wiek.length()-1]=='3' || wiek[wiek.length()-1]=='4') cout << " lata" << endl;
    else cout << " lat" << endl;
    cout << "Hobby:    ";
    bool coma = false;
    string temp = dynamic_pointer_cast<IASNBitstring>(this->getObjects()[4])->getStr();
    if(temp[0]-'0') {
        cout << "narty";
        coma = true;
    }
    if(temp[1]-'0') {
        if(coma) cout << ", ";
        cout << "lyzwy";
        coma = true;
    }
    if(temp[2]-'0') {
        if(coma) cout << ", ";
        cout << "ksiazki";
        coma = true;
    }
    if(temp[3]-'0') {
        if(coma) cout << ", ";
        cout << "plywanie";
        coma = true;
    }
    cout << endl << endl;
}



