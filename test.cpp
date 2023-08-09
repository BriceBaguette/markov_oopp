#include "markov_model.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

int main(int argc, char const *argv[])
{
    string data = "abcd";
    unsigned int order = 2;
     for (unsigned int i = 0; i < data.length(); i++)
    {
        std::string value;
        if (i < data.length() - order)
        {
            value = data.substr(i, order + 1);
        }
        else
        {
            value = data.substr(i, (data.length() - i)) + data.substr(0, (i - order + 1));
        }
    cout << value << "\n";
    }
    return 0;
}