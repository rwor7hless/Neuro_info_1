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

void neuron::fit(const std::vector<std::vector<int>>& training_data, int epochs, float step)
{
    int target;
    for (int epoch = 0; epoch < epochs; ++epoch) {
        this->v_error = 0;
        for (size_t i = 0; i < training_data.size(); ++i) {
            if (std::equal(training_data[i].begin(), training_data[i].end(), this->value_.begin())) {
               target = 1;
            }
            else {
                target = 0;
            }
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

int neuron::predict(const std::vector<int>& input)
{
    if (input.size() != weights.size()) {
        std::cerr << "Input size does not match weights size" << std::endl;
        return -1;
    }

    float sum = 0.0;
    for (size_t i = 0; i < input.size(); ++i) {
        sum += input[i] * this->weights[i];
    }
    int result = (sum >= this->threshold) ? 1 : 0;

    return result;
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

