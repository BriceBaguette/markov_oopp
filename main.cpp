#include "markov_model.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>
#include <sstream>

int main(int argc, char const *argv[])
{
    int count = 0;
    for (int i = 0; !(strcmp(argv[i], "---") == 0); i++)
    {
        count++;
    }

    for (int j = count + 1; j < argc; j++)
    {
        std::ifstream t(argv[j]);
        std::stringstream buffer;
        buffer << t.rdbuf();
        string testingData = buffer.str();
        cout << "Testing file: " << argv[j] << "\n";
        string bestModel;
        double bestLikelihood = std::numeric_limits<double>::max();
        for (int i = 2; i < count; i++)
        {
            std::ifstream inputFile(argv[i]);
            if (!inputFile.is_open())
            {
                std::cerr << "Error opening file: " << argv[i] << std::endl;
                return 1;
            }
            std::string trainingData;
            std::string modelName;
            std::getline(inputFile, modelName);
            std::string line;
            while (std::getline(inputFile, line))
            {
                trainingData += line;
            }
            Markov_model *model = new Markov_model();
            markov_model(*model, std::stoi(argv[1]), trainingData);
            try
            {
                double modelLikelihood = likelihood(*model, testingData);
                cout << modelName << ": " << modelLikelihood << "\n";
                if (modelLikelihood < bestLikelihood)
                {
                    bestModel = modelName;
                    bestLikelihood = modelLikelihood;
                }
            }
            catch (const std::exception &e)
            {
                cout << modelName << ": -\n";
            }
        }
        if (bestModel.empty())
        {
            cout << argv[j] << " attributed to - \n";
        }
        else
        {
            cout << argv[j] << " attributed to " << bestModel << "\n";
        }
    }
    return 0;
}