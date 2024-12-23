#pragma once

#include <unordered_map>
#include <string>
#include <fstream>
#include <mutex>
#include "logger.hpp"

using namespace std;

class KeyDir
{
private:
    fstream *current_file = nullptr;
    string file_id;
    Logger logger;
    mutable mutex mtx;
public:
    unordered_map<string, MetaData> directory;
    void set_command(const string &key, const string &value, float expiry = 10000000);
    void list_command();
    string get_command(const string &key);
    void delete_command(const string& key);
    MetaData& operator[](const string& key);
};