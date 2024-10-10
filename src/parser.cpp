#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
#include <stdexcept>
#include "parser.hpp"

using namespace std;

tuple<string, string, string, float> parse_user_info(const string &user_input)
{
    const unordered_set<string> commands_list = {"GET", "SET", "DELETE", "LIST", "SYNC"};
    string command, key, value, given_expiry;
    float expiry = 10000000;
    istringstream ss(user_input);
    tuple<string, string, string, float> parsed_facts;

    if (!(ss >> command) || command.empty() || commands_list.find(command) == commands_list.end())
    {
        cerr << "Error: Command '" << command << "' does not exist or is invalid" << endl;
        return make_tuple("", "", "", expiry);
    }

    key.clear();
    value.clear();

    if (command == "GET")
    {
        if (ss >> key && !(ss >> value))
        {
            return make_tuple(command, key, "", expiry);
        }
        cerr << "GET command only requires a key" << endl;
    }
    else if (command == "SET")
    {
        if (ss >> key >> value)
        {
            if (ss >> given_expiry)
            {
                try
                {
                    expiry = stof(given_expiry);
                }
                catch (const exception &e)
                {
                    cerr << "Expiry must be a number" << endl;
                }
            }
            return make_tuple(command, key, value, expiry);
        }
        cerr << "SET command requires a key and value" << endl;
    }
    else if (command == "DELETE")
    {
        if (ss >> key && !(ss >> value))
        {
            return make_tuple(command, key, "", expiry);
        }
        cerr << "DELETE command requires a key" << endl;
    }
    else if (command == "LIST")
    {
        if (!(ss >> key) && !(ss >> value))
        {
            return make_tuple(command, "", "", expiry);
        }
        cerr << "LIST command does not need any arguments" << endl;
    }
    else if (command == "SYNC")
    {
        if (!(ss >> key) && !(ss >> value))
        {
            return make_tuple(command, "", "", expiry);
        }
        cerr << "SYNC command does not need any arguments" << endl;
    }
    return make_tuple("", "", "", expiry); 
}