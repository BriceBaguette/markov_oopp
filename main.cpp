#include "markov_model.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char const *argv[])
{
    int count = 0;
    for (int i = 0; argv[i] != "---"; i++)
    {
        count++;
    }
    for (int i = 1; i <= count; i++)
    {
        std::ifstream t(argv[i]);
        std::stringstream buffer;
        buffer << t.rdbuf();
        string trainingData = buffer.str();
        Markov_model *model = new Markov_model();
        markov_model(*model, int(argv[0]), trainingData);
        for (int j = count + 2; j < argc; j++)
        {
            std::ifstream t(argv[j]);
            std::stringstream buffer;
            buffer << t.rdbuf();
            string testingData = buffer.str();
            cout << "Testing file: " << argv[j] << ", model file: " << argv[i] << likelihood(*model, testingData);
        }
    }
}