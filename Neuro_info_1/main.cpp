#include "neuron.h"
#include "helper.h"

std::vector<std::vector<int>> numbers = {
                                            {1, 1, 0, 1, 0, 1, 0, 1, 1}, 
                                            {0, 0, 1, 1, 0, 0, 0, 1, 0},
                                            {0, 1, 0, 1, 0, 0, 1, 0, 1},
                                            {0, 1, 1, 0, 1, 0, 1, 0, 0},
                                            {1, 0, 0, 1, 1, 0, 0, 1, 0},
                                            {1, 1, 0, 0, 1, 0, 0, 1, 1},
                                            {0, 0, 1, 0, 1, 1, 0, 1, 1},
                                            {0, 1, 1, 0, 0, 1, 0, 0, 0},
                                            {1, 1, 0, 1, 1, 1, 0, 1, 1},
                                            {1, 1, 0, 1, 1, 0, 1, 0, 0}
                                        };

void getAcc(std::vector<std::vector<int>>& data, neuron& n) {
    std::cout  
              << "\nКоличество ошибок:\t |" << n.getErrors()
              << "\nДанных для обучения:\t |" << data.size()
              << "\nТочность обучния:\t |"  << ((data.size() - n.getErrors())*1.0f / data.size()) * 100 << " %";
}

int main() {
   
    auto [training_data, targets] = readTrainDataFromFile("data/train_data_corrupted.txt");

    shuffle_data(training_data, targets);


    neuron neuro(9, -1, 1, 25, numbers[3]);  // Создаем нейрон с 9 весами в диапазоне от -1 до 1, порогом классификации 25 и распознаваемым числом - 3

    std::cout << "Веса до обучения:   "; neuro.printW();
    neuro.fit(training_data, targets, 10, 1);
    std::cout << "Веса после обучения:"; neuro.printW();

    std::vector<std::vector<int>> test_data = readTestDataFromFile("data/test_data_corrupted.txt");

    // Предсказание значений на тестовых данных
    std::vector<int> predictions = neuro.predict(test_data);

    // Вывод предсказаний
    for (size_t i = 0; i < test_data.size(); ++i) {
        std::cout << "Input: ";
        for (int val : test_data[i]) {
            std::cout << val;
        }
        std::cout << " Prediction: " << predictions[i] << std::endl;
    }
    getAcc(training_data, neuro);
    return 0;
}

