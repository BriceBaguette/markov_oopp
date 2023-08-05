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
    model.model = makeModel(data, model.alphabet, order);
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

Model makeModel(std::string data, Alphabet alphabet, int order)
{
    Model *model = new Model();
    for (int i = 0; i < data.length(); i++)
    {
        std::string value;
        if (i >= data.length() - order - 1)
        {
            value = data.substr(i, order + 1);
        }
        else
        {
            value = data.substr(i, (data.length()) - i - order) + data.substr(0, data.length() - i + 1);
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

    for (int i = 0; i < data.length() - (order); i++)
    {
        std::string value;
        if (i >= data.length() - order)
        {
            value = data.substr(i, order);
        }
        else
        {
            value = data.substr(i, (data.length()) - i - 1) + data.substr(0, data.length() - i);
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
    if (string.length() > markov_model.order + 1)
    {
        throw std::length_error("model and input data are incompatible");
    }
    for (int i = 0; i < string.length(); i++)
    {
        if (markov_model.alphabet.find(string[i]) == markov_model.alphabet.end())
        {
            throw std::domain_error("input data contains symbols not in the model");
        }
    }
    Model::const_iterator it = markov_model.model.find(string);
    if (it == markov_model.model.end())
    {
        return 0;
    }
    return ((markov_model.model.find(string)->second + 1) /
                markov_model.model.find(string.substr(0, string.length() - 1))->second +
            markov_model.alphabet.size());
}

double likelihood(Markov_model &markov_model, const std::string &string)
{
    int order = markov_model.order;
    double likelihood = 0;
    for (int i = 0; i < string.length(); i++)
    {
        std::string value;
        if (i >= string.length() - order - 1)
        {
            value = string.substr(i, order + 1);
        }
        else
        {
            value = string.substr(i, (string.length()) - i - 1) + string.substr(0, string.length() - i + 1);
        }
        likelihood += log(laplace(markov_model, value));
    }
    return likelihood;
}