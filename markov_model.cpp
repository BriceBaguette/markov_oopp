#include "markov_model.hpp"

// part 1

void markov_model(Markov_model &model, unsigned int order, const std::string &data)
{
    if (data.length() <= order)
    {
        throw std::length_error("order and data are incompatible to build the model");
    }
    model.order = order;
    model.alphabet = makeAlphabet(data);
    model.model = makeModel(data, order);
}

Alphabet makeAlphabet(std::string data)
{
    Alphabet *alphabet = new Alphabet();
    for (string::iterator it = data.begin(); it != data.end(); it++)
    {
        if (alphabet->find(*it) == alphabet->end())
            alphabet->insert(*it);
    }
    return *alphabet;
}

Model makeModel(std::string data, unsigned int order)
{
    Model *model = new Model();
    for (unsigned int i = 0; i < data.length(); i++)
    {
        std::string value;
        if (i < data.length() - order)
        {
            value = data.substr(i, order + 1);
        }
        else
        {
            value = data.substr(i, (data.length() - i)) + data.substr(0, (order - (data.length() - i) + 1));
        }
        Model::iterator it = model->find(value);
        if (it == model->end())
        {
            model->insert({value, 1});
        }
        else
        {

            it->second = it->second + 1;
        }
    }

    for (unsigned int i = 0; i < data.length(); i++)
    {
        std::string value;
        if (i < data.length() - order + 1)
        {
            value = data.substr(i, order);
        }
        else
        {
            value = data.substr(i, (data.length()) - i) + data.substr(0, (order - (data.length() - i)));
        }
        Model::iterator it = model->find(value);
        if (it == model->end())
        {
            model->insert({value, 1});
        }
        else
        {
            it->second = it->second + 1;
        }
    }

    return *model;
}

double laplace(const Markov_model &markov_model, const std::string &string)
{
    double numerator = 1;
    double denominator = static_cast<double>(markov_model.alphabet.size());
    if(markov_model.model.find(string) != markov_model.model.end()){
        numerator = static_cast<double>(markov_model.model.find(string)->second + 1);
    }
    if(markov_model.model.find(string.substr(0, string.length() - 1)) != markov_model.model.end()){
        denominator += static_cast<double>(markov_model.model.find(string.substr(0, string.length() - 1))->second);
    }
    double value = numerator / denominator;
    return value;
}

double likelihood(Markov_model &markov_model, const std::string &string)
{
    unsigned int order = markov_model.order;
    for (unsigned int i = 0; i < string.length(); i++)
    {
        if (markov_model.alphabet.find(string[i]) == markov_model.alphabet.end())
        {
            throw std::domain_error("input data contains symbols not in the model");
        }
    }
    if (string.length() < order + 1)
    {
        throw std::length_error("model and input data are incompatible");
    }
    double likelihood = 0;
    for (unsigned int i = 0; i < string.length(); i++)
    {
        std::string value;
        if (i < string.length() - order)
        {
            value = string.substr(i, order + 1);
        }
        else
        {
            value = string.substr(i, (string.length() - i)) + string.substr(0, (order - (string.length() - i) + 1));
        }
        likelihood += log(laplace(markov_model, value));
    }
    return likelihood;
}