#include <algorithm>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#pragma once

float factorielle(float nombre);

float loi_totale(float P_X_1, float P_A_X_1, float P_X_2, float P_A_X_2);

float loi_de_bayes(float P_A_B, float P_B, float P_A);

std::pair<float, float> loi_de_bernouilli(float proba_de_reussir);

float loi_binomiale(float nombre, float k, float p);

float loi_de_poisson(float lambda_, float k);

float loi_uniforme(float nombre);

float loi_exponentielle(float lambda, float t);

float loi_de_gauss(float sigma, float x, float mu);