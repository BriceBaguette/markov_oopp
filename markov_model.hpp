#include <set>
#include <map>
#include <string>
#include <stdexcept>
#include <cmath>
#include <iostream>
using namespace std;

typedef set<char> Alphabet;
typedef map<std::string, unsigned int> Model;

struct Markov_model
{
    unsigned int order;
    Alphabet alphabet;
    Model model;
};

/*
Function that builds a Markov model from an inputstring where the first parameter represents the
model the function is building, the second parameter represents the model’s order, and the third
parameter is the training data on which the model is built.
*/
void markov_model(Markov_model &model, unsigned int order, const std::string &data);

/*
Function that takes as input the data we build markov model on
and return the alphabet
*/
Alphabet makeAlphabet(std::string data);

/*
Function that takes as input the alphabet from markov model and the data we build markov model on
and return the model
*/
Model makeModel(std::string data, unsigned int order);

/*
Function that computes laplace probabilities given a model and an input data.
*/
double laplace(const Markov_model &markov_model, const std::string &string);

/*
Functon that computes the likelihood of a input data given a model.
*/
double likelihood(Markov_model &markov_model, const std::string &string);
