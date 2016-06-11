#include "IStorable.h"

using namespace std;

void IStorable::saveData(const string &filename)
{
    ofstream file;
    file.open(filename, ofstream::binary);
    for_each(data.begin(), data.end(), [&](char c) { file << c; });
    file.close();
}
