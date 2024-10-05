#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "../headers/utils.hpp"

using namespace std;

string random_generator()
{
    const char alphabets[] = "abcdefghijklmnopqrstuvwxyz";
    string random_string;
    srand(time(0));

    for (size_t i = 0; i < 6; i++)
    {
        random_string += alphabets[rand() % 26];
    }

    return random_string;
}

void welcome_message()
{
    vector<string> fastcask =
        {
            " ______           _    _____           _    ",
            "|  ____|         | |  / ____|         | |   ",
            "| |__ __ _ ___  _| |_| |     __ _ ___| | __ ",
            "|  __/ _` / __|/  ` || |    / _` / __| |/ / ",
            "| | | (_| \\__  _| || |___| (_| \\__ \\   <  ",
            "|_|  \\__,_|___/\\__,_|\\_____\\__,_|___/_|\\_\\ ",
            "                                            ",
            "          Welcome to FastCask!              "};

    for (const auto &line : fastcask)
    {
        cout << line << '\n';
    }
}