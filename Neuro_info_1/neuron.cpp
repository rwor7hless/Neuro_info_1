#include "neuron.h"


neuron::neuron(int size, int min_, int max_, float threshold, std::vector<int>& value_)
{
    std::random_device rd;  
    std::mt19937 gen(rd()); 

    // диапазон случайных чисел
    std::uniform_int_distribution<> dis(min_, max_);

    weights.resize(size);
    for (float& weight : weights) {
        weight = dis(gen);  
    }

    this->threshold = threshold;
    this->value_ = value_;
}

void neuron::fit(const std::vector<std::vector<int>>& training_data, const std::vector<int>& targets, int epochs, float step) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        this->v_error = 0;
        for (size_t i = 0; i < training_data.size(); ++i) {
            int target = targets[i];
            float sum = 0.0;

            for (size_t j = 0; j < training_data[i].size(); ++j) {
                sum += training_data[i][j] * this->weights[j];
            }

            // Обновляем веса в зависимости от ошибки
            if (target == 1 && sum <= threshold) {
                // Если заданное число распознано неверно и сумма не доходит до порога
                for (size_t j = 0; j < training_data[i].size(); ++j) {
                    if (training_data[i][j] == 1) {
                        this->weights[j] += step;
                    }
                }
                this->v_error++;
            }
            else if (target == 0 && sum > threshold) {
                // Если распознанно незаданное число и его вес больше порога
                for (size_t j = 0; j < training_data[i].size(); ++j) {
                    if (training_data[i][j] == 1) {
                        this->weights[j] -= step;
                    }
                }
                this->v_error++;
            }
        }
    }
}

std::vector<int> neuron::predict(const std::vector<std::vector<int>>& test_data) {
    std::vector<int> predictions;
    for (const auto& input : test_data) {
        float sum = 0.0;
        for (size_t j = 0; j < input.size(); ++j) {
            sum += input[j] * this->weights[j];
        }
        // Предсказываем 1, если сумма больше или равна порогу, иначе 0
        predictions.push_back(sum >= threshold ? 1 : 0);
    }
    return predictions;
}

void neuron::printW()
{
    for (auto n : this->weights)
    {
        std::cout << std::setw(3) << n << " ";
    }
    std::cout << std::endl;
}

int neuron::getErrors()
{
    return this->v_error;
}

