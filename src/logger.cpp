#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include "../headers/json.hpp"
#include "../headers/logger.hpp"

using namespace std;
using json = nlohmann::json;

Logger::Logger()
{
    filesystem::create_directories("sync");
    string file_path = "sync/" + string("wal") + ".json";
    log_file.open(file_path, ios::app);
    fstream log_file(file_path, ios::app);

    if (!log_file.is_open())
    {
        cerr << "Error opening log file" << endl;
    }
}

Logger::~Logger()
{
    if (log_file.is_open())
    {
        log_file.close();
    }
}

void Logger::put_log(const string &key, const MetaData &metadata)
{
    json log_entry;

    log_entry["key"] = key;
    log_entry["file_id"] = metadata.file_id;
    log_entry["value_size"] = metadata.value_size;
    log_entry["offset"] = metadata.offset;

    log_file << log_entry.dump() << endl;
    log_file.flush();
}

vector<pair<string, MetaData>> Logger::retrieve_logs() const
{
    vector<pair<string, MetaData>> logs;
    ifstream log_file("user_files/wal.json");

    if (!log_file.is_open())
    {
        cerr << "Error opening log file for reading" << endl;
        return logs;
    }

    string line;

    while (getline(log_file, line))
    {
        json log_entry = json::parse(line);
        string key = log_entry["key"];
        MetaData metadata = {
            nullptr,
            log_entry["value_size"],
            log_entry["file_id"],
            log_entry["offset"]};

        logs.emplace_back(key, metadata);
    }

    return logs;
}