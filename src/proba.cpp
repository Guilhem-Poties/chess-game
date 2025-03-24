#include "proba.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>

// Fonction pour générer un entier aléatoire avec std::rand
int genererEntierAvecRand(int min, int max)
{
    return min + (std::rand() % (max - min + 1));
}

// Fonction pour générer un double aléatoire dans une plage donnée
double genererDouble(double min, double max)
{
    std::random_device                     rd;
    std::mt19937                           gen(rd());
    std::uniform_real_distribution<double> distrib(min, max);
    return distrib(gen);
}

// Fonction pour générer un long double aléatoire dans une plage donnée
long double genererLongDouble(long double min, long double max)
{
    std::random_device                          rd;
    std::mt19937                                gen(rd());
    std::uniform_real_distribution<long double> distrib(min, max);
    return distrib(gen);
}

// Fonction pour calculer le factoriel d'un nombre
float factorielle(float nombre)
{
    if (nombre == 0)
    {
        return 1;
    }
    else
    {
        float factorielle = 1;
        for (float k = 2; nombre + 1.f; k++)
        {
            factorielle = factorielle * k;
        }
        return factorielle;
    }
}

// Fonction pour calculer la probabilité d'une loi totale
float loi_totale(float proba_X_1, float proba_A_X_1, float proba_X_2, float proba_A_X_2)
{
    float proba_A = proba_X_1 * proba_A_X_1 + proba_X_2 * proba_A_X_2;
    return proba_A;
}

// Fonction pour calculer la probabilité d'une loi de Bayes
float loi_de_bayes(float proba_A_B, float proba_B, float proba_A)
{
    float proba_B_A = proba_A_B * proba_B / proba_A;
    return proba_B_A;
}

// Fonction pour calculer la probabilité d'une loi de Bernouilli
std::pair<float, float> loi_de_bernouilli(float proba_de_reussir)
{
    if (proba_de_reussir >= 0 && proba_de_reussir <= 1)
    {
        return {proba_de_reussir, 1 - proba_de_reussir};
    }
}

// Fonction pour calculer la probabilité binomiale
float loi_binomiale(float nombre, float k, float p)
{
    float proba_X_egal_k = factorielle(nombre) / factorielle(k) / factorielle(nombre - k) * std::pow(p, k) * std::pow((1 - p), (nombre - k));
    return proba_X_egal_k;
}

// Fonction pour calculer la probabilité de Poisson
float loi_de_poisson(float lambda, float k)
{
    float proba_X_egal_k = std::pow(lambda, k) * exp(-lambda) / factorielle(k);
    return proba_X_egal_k;
}

// Fonction pour calculer la probabilité d'une loi uniforme
float loi_uniforme(float nombre)
{
    float proba = 1 / nombre;
    return proba;
}

// Fonction pour calculer la probabilité d'une loi exponentielle
float loi_exponentielle(float lambda, float t)
{
    float proba_X_inf_t = 1 - exp(-lambda * t);
    return proba_X_inf_t;
}

// Fonction pour calculer la probabilité d'une loi de Gauss
float loi_de_gauss(float sigma, float x, float mu)
{
    float proba = 1 / sigma / sqrt(2 * 3.14f) * exp(std::pow(-(x - mu), 2) / (2 * std::pow(sigma, 2)));
    return proba;
}
