#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "metadata.hpp"

using namespace std;


class Logger
{
private:
    fstream log_file;

public:
    Logger();
    ~Logger();
    void put_log(const string &key, const MetaData &metadata);
    vector<pair<string, MetaData>> retrieve_logs() const;
};