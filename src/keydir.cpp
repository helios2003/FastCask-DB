#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <mutex>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <filesystem>
#include "../headers/keydir.hpp"
#include "../headers/utils.hpp"

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
        filesystem::create_directories("user_files");
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

    MetaData metadata = {
        current_file,
        value_size,
        file_id,
        offset};

    // write the value into the hint file and current file
    logger.put_log(key, metadata);
    *current_file << value;
    current_file->flush();
    directory[key] = metadata;
}

string KeyDir::get_command(const string &key) const
{
    if (directory.find(key) == directory.end())
    {
        cerr << "Key " << key << " is not found" << endl;
        return "";
    }

    auto it = directory.find(key);
    MetaData metadata = it->second;

    if (metadata.file_ptr->is_open())
    {
        metadata.file_ptr->close();
    }
    metadata.file_ptr->open("user_files/" + metadata.file_id + ".txt");

    if (metadata.file_ptr->good())
    {
        metadata.file_ptr->seekg(metadata.offset, ios::beg);
        string value(metadata.value_size, '\0');
        metadata.file_ptr->read(&value[0], metadata.value_size);
        return value;
    }
    return "";
}

void KeyDir::delete_command(const string& key) 
{
    lock_guard<mutex> lock(mtx);
    if (directory.find(key) == directory.end())
    {
        cerr << "Key " << key << " is not found" << endl;
        return;
    }
    directory.erase(key);
}

void KeyDir::list_command() const
{
    for (auto &it : directory)
    {
        cout << it.first << '\n';
    }
}

MetaData &KeyDir::operator[](const string &key)
{
    return directory[key];
}
