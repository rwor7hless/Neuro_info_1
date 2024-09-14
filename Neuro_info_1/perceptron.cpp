#include "perceptron.h"

perceptron::perceptron(int min_, int max_)
{
    this->m_errors = 0;
    // Генерируем рандом девайс для псевдослучайных значений заполнения
    std::random_device rd;
    std::mt19937 gen(rd());

    // диапазон случайных чисел
    std::uniform_int_distribution<> dis(min_, max_);

    // Подгоняем размер данных под тот, что указали в конструкторе
    m_weights.resize(9, std::vector<float>(15));

    for (std::vector<float>& row : m_weights) {
        for (float& num : row) {
            num = dis(gen);
        }
    }

}

std::string perceptron::predict(const std::vector<int>& test_data)
{
    std::vector<float> sums;
    sums.reserve(m_weights.size());
    for (auto row : m_weights)
    {
        float row_sum = 0;
        for (int i = 0; i < test_data.size(); ++i)
        {
            if (test_data[i] == 1) 
            {
                row_sum += test_data[i] * row[i];
            }
        }
        sums.push_back(row_sum);
    }

    auto max_it = std::max_element(sums.begin(), sums.end());
    size_t max_index = std::distance(sums.begin(), max_it);

    return m_numbers[max_index];
}

void perceptron::fit(const std::vector<std::vector<int>>& training_data, const std::vector<std::string>& targets, int epochs, float step) {
    if (training_data.size() != targets.size()) {
        std::cerr << "Error: training_data and targets sizes do not match." << std::endl;
        return;
    }

    for (size_t epoch = 0; epoch < epochs; epoch++) {

        this->m_errors = 0;

        for (size_t i = 0; i < training_data.size(); ++i) {
            const auto& data = training_data[i];
            const auto& target = targets[i];

            std::vector<float> sums;
            sums.reserve(m_weights.size());

            for (const auto& row : m_weights) {
                float row_sum = 0;
                for (size_t j = 0; j < data.size(); ++j) {
                    if (data[j] == 1) {
                        row_sum += row[j];
                    }
                }
                sums.push_back(row_sum);
            }

            auto max_it = std::max_element(sums.begin(), sums.end());
            size_t max_index = std::distance(sums.begin(), max_it);

            if (m_numbers[max_index] != target) {
                this->m_errors++;

                // Уменьшаем веса для максимального индекса
                for (size_t j = 0; j < data.size(); ++j) {
                    if (data[j] == 1) {
                        this->m_weights[max_index][j] -= step;
                    }
                }

                // Увеличиваем веса для правильного индекса
                auto target_it = std::find(m_numbers.begin(), m_numbers.end(), target);
                if (target_it != m_numbers.end()) {
                    int target_index = std::distance(m_numbers.begin(), target_it) - 1;
                    std::cout << target_index << std::endl;
                    for (size_t j = 0; j < data.size(); ++j) {
                        if (data[j] == 1) {
                            this->m_weights[target_index][j] += step;
                        }
                    }
                }
                else {
                    std::cerr << "Invalid target: " << target << std::endl;
                }
            }
        }

        std::cout << "Epoch " << epoch + 1 << " completed with " << this->m_errors << " errors." << std::endl;
    }
}
void perceptron::get_weigths() const
{
    for (const auto& row : m_weights) {
        for (const auto& elem : row) {
            std::cout << std::setw(6) << elem << ' ';
        }
        std::cout << '\n';
    }
}
