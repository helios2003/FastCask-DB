#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <mutex>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <filesystem>
#include <chrono>
#include "keydir.hpp"
#include "utils.hpp"

#define MAX_FILE_SIZE 1048576

using namespace std;

void KeyDir::set_command(const string &key, const string &value, float expiry)
{
    /* if there is no file or the current file can no longer
    be the active file then only run this subroutine */
    lock_guard<mutex> lock(mtx);
    if (current_file == nullptr || current_file->tellp() > MAX_FILE_SIZE)
    {
        if (current_file != nullptr)
        {
            current_file->close();
            delete current_file;
        }

        file_id = random_generator();
        string file_path = "user_files/" + file_id + ".txt";
        current_file = new fstream(file_path, ios::app);

        if (!current_file->is_open())
        {
            cerr << "Error opening the file" << endl;
            return;
        }
    }

    // find the metadata information
    int offset = current_file->tellp();
    int value_size = value.length();
    chrono::system_clock::time_point expiry_time = chrono::system_clock::now() + chrono::seconds(static_cast<int>(10000000));

    if (expiry != 10000000)
    {
        cout << "expiry is " << expiry;
        expiry_time = chrono::system_clock::now() + chrono::seconds(static_cast<int>(expiry));
    }

    MetaData metadata = {
        current_file,
        value_size,
        file_id,
        offset,
        expiry_time};

    // write the value into the hint file and current file
    logger.put_log(key, metadata);
    *current_file << value;
    current_file->flush();
    directory[key] = metadata;
}

string KeyDir::get_command(const string &key)
{
    if (directory.find(key) == directory.end())
    {
        cerr << "Key " << key << " is not found" << endl;
        return "";
    }

    chrono::system_clock::time_point curr_time = chrono::system_clock::now();

    auto it = directory.find(key);
    MetaData metadata = it->second;

    if (metadata.file_ptr->is_open())
    {
        metadata.file_ptr->close();
    }
    metadata.file_ptr->open("user_files/" + metadata.file_id + ".txt");

    if (metadata.file_ptr->good())
    {
        if (metadata.expiry_time < curr_time)
        {
            metadata.file_ptr->close();
            directory.erase(key);
            cerr << "Key " << key << " is not found" << endl; 
            return "";
        }
        metadata.file_ptr->seekg(metadata.offset, ios::beg);
        string value(metadata.value_size, '\0');
        metadata.file_ptr->read(&value[0], metadata.value_size);
        return value;
    }
    return "";
}

void KeyDir::delete_command(const string &key)
{
    lock_guard<mutex> lock(mtx);
    if (directory.find(key) == directory.end())
    {
        cerr << "Key " << key << " is not found" << endl;
        return;
    }
    directory.erase(key);
}

void KeyDir::list_command()
{
    for (auto it = directory.begin(); it!= directory.end();)
    {
        MetaData metadata = it->second;
        chrono::system_clock::time_point curr_time = chrono::system_clock::now();

        if (metadata.expiry_time < curr_time) 
        {
            if (metadata.file_ptr->is_open()) 
            {
                metadata.file_ptr->close();
            }
            it = directory.erase(it);
        }
        else 
        {
            cout << it->first << '\n';
            ++it;
        }
    }
}

MetaData &KeyDir::operator[](const string &key)
{
    return directory[key];
}
