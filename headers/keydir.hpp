# pragma once

#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;

struct MetaData
{
    fstream* file_ptr;
    int value_size;
    string file_id;
    int offset;
};

class KeyDir {
private:
    unordered_map<string, MetaData> directory;
    fstream* current_file = nullptr;
    string file_id;
    // mutable std::mutex mtx;
public:
    void set_command(const string &key, const string &value, float expiry = 1e9);
    void list_command() const;
    string get_command(const string &key) const;
};