#pragma once
#include <fstream>
#include <chrono>
#include <string>

using namespace std;

struct MetaData
{
    fstream *file_ptr;
    int value_size;
    string file_id;
    int offset;
    chrono::system_clock::time_point expiry_time; 
};