#pragma once
#include <fstream>
#include <string>

using namespace std;

struct MetaData
{
    fstream *file_ptr;
    int value_size;
    string file_id;
    int offset;
};