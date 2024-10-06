#include <iostream>
#include <string>
#include <filesystem>
#include "headers/keydir.hpp"
#include "headers/parser.hpp"
#include "headers/utils.hpp"
#include "headers/logger.hpp"
#include "headers/metadata.hpp"

#define BLU "\e[0;34m"
#define RESET "\e[0m"

using namespace std;

int main(void)
{
    welcome_message();
    KeyDir keydir;
    string user_input;
    Logger logger;
    while (true)
    {
        cout << BLU ">> fastcask: " RESET;
        getline(cin, user_input);
        if (user_input == "EXIT")
        {
            try
            {
                if (filesystem::exists("user_files"))
                {
                    filesystem::remove_all("user_files");
                }
            }
            catch (const filesystem::filesystem_error &err)
            {
                cerr << "Error: " << err.what() << endl;
            }
            cout << "Exiting from Fastcask..." << endl;
            exit(0);
        }

        tuple<string, string, string, float> arguments_list = parse_user_info(user_input);
        string command, key, value;
        float expiry;
        tie(command, key, value, expiry) = arguments_list;

        if (command == "SET")
        {
            keydir.set_command(key, value, expiry);
        }
        else if (command == "GET")
        {
            string value = keydir.get_command(key);
            if (value != "")
            {
                cout << value << '\n';
            }
        }
        else if (command == "LIST")
        {
            keydir.list_command();
        }
        else if (command == "SYNC")
        {
            vector<pair<string, MetaData>> logs = logger.retrieve_logs();
            for (const auto &entry : logs)
            {
                string key = entry.first;
                MetaData metadata = entry.second;
                string file_path = "user_files/" + metadata.file_id + ".txt";
                fstream *file_ptr = new fstream(file_path, ios::in | ios::out);

                if (!file_ptr->is_open())
                {
                    cerr << "Error opening file for key: " << key << '\n';
                    delete file_ptr;
                    continue;
                }

                metadata.file_ptr = file_ptr;
                keydir[key] = metadata;
            }
        }
    }
    return 0;
}