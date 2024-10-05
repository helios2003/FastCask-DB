#include <iostream>
#include <string>
#include <filesystem>
#include "headers/keydir.hpp"
#include "headers/parser.hpp"
#include "headers/utils.hpp"

#define BLU "\e[0;34m"
#define RESET "\e[0m"

using namespace std;

int main(void)
{
    welcome_message();
    KeyDir directory;
    string user_input;

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
            directory.set_command(key, value, expiry);
        }
        else if (command == "GET")
        {
            string value = directory.get_command(key);
            if (value != "")
            {
                cout << value << '\n';
            }
        }
        else if (command == "LIST")
        {
            directory.list_command();
        }
    }
    return 0;
}