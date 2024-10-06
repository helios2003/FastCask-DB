#pragma once

#include <unordered_map>
#include <string>
#include <fstream>
#include "logger.hpp"

using namespace std;

class KeyDir
{
private:
    unordered_map<string, MetaData> directory;
    fstream *current_file = nullptr;
    string file_id;
    Logger logger;
    // mutable std::mutex mtx;
public:
    void set_command(const string &key, const string &value, float expiry = 1e9);
    void list_command() const;
    string get_command(const string &key) const;
    MetaData& operator[](const string& key);
};