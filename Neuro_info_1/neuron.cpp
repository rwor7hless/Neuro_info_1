#include "neuron.h"


neuron::neuron(int size, int min_, int max_, float threshold)
{
    // Генерируем рандом девайс для псевдослучайных значений заполнения
    std::random_device rd;  
    std::mt19937 gen(rd()); 

    // диапазон случайных чисел
    std::uniform_int_distribution<> dis(min_, max_);

    // Подгоняем размер данных под тот, что указали в конструкторе
    weights.resize(size);
    for (float& weight : weights) {
        weight = dis(gen);  // Рандомно заполняем их
    }

    this->threshold = threshold;
}

void neuron::fit(const std::vector<std::vector<int>>& training_data, const std::vector<std::string>& targets, int epochs, float step) {
    for (int epoch = 0; epoch < epochs; ++epoch) {

        this->v_error = 0; // На каждой эпохе количество ошибок обнуляется

        /*
            Работа с уже размеченными данными, проходимся по каждому объекту в массиве тренировочных данных
            Умножаем каждую "1" входного массива на соответствующий вес в векторе весов
            Если сумма весов искомой цифры преодалевает порог, то все хорошо, ничего не делаем

            Если сумма ненужной цифры преодалевает порог или наоборот, сумма нужной цифры не дотягивает
            То изменяем веса на -step, если первый случай и +step для второго случая
            И если случай ошибки случился, то увеличиваем общее число ошибок после обучении
        */

        for (size_t i = 0; i < training_data.size(); ++i) {  
            std::string target = targets[i];
            float sum = 0.0;

            for (size_t j = 0; j < training_data[i].size(); ++j) {
                sum += training_data[i][j] * this->weights[j];
            }

            // Обновляем веса в зависимости от ошибки
            if (target == "три" && sum <= threshold) {
                // Если заданное число распознано неверно и сумма не доходит до порога
                for (size_t j = 0; j < training_data[i].size(); ++j) {
                    if (training_data[i][j] == 1) {
                        this->weights[j] += step;
                    }
                }
                this->v_error++;
            }
            else if (target != "три" && sum > threshold) {
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


/*
        Функция предикт просто считает сумму для входных векторов (векторов данных)
        И при при классфикации, в зависимости от того, прошла ли цифра порог, выдает 1, если данные прошли порог суммы
        И выдает 0, если порог не пройден
*/

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

