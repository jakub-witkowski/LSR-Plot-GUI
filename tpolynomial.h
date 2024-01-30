#ifndef TPOLYNOMIAL_H
#define TPOLYNOMIAL_H

#include "TF1.h"
#include <string>
#include <vector>

class TPolynomial
{
    public:
    TPolynomial(int);
    ~TPolynomial();

    int deg{}; // stopień wyrażenia wielomianowego
    std::string phrase{}; // łańcuch znaków przekazywany do obiektu klasy TF1 w celu obliczenia regresji wielomianowej
    TF1* f{nullptr}; // klasa z biblioteki ROOT pozwalająca na tworzenie funkcji jednowymiarowych
    std::vector<double> parameters{}; // wektor przechowujący parametry wyrażenia wielomianowego
    double chi2{}; // parametr wyrażający stopień dopasowania regresji do zbioru danych
    int ndf{}; // liczba stopni swobody wyrażenia wielomianowego
};

#endif