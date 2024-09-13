#include "neuron.h"
#include "helper.h"

void getAcc(std::vector<std::vector<int>>& data, neuron& n) {
    std::cout  
              << "\nErrors count:\t\t |" << n.getErrors()
              << "\nTrain data size:\t |" << data.size()
              << "\nfit accuracy:\t\t |"  << ((data.size() - n.getErrors())*1.0f / data.size()) * 100 << " %\n";
}

int main() {
    auto [training_data, targets] = readTrainDataFromFile("data/train_data_corrupted_5.txt");
    shuffle_data(training_data, targets);


    neuron neuro(9, -1, 1, 25);  // Создаем нейрон с 9 весами в диапазоне от -1 до 1, порогом классификации 25 
    std::cout << "Weights before fit:\t"; neuro.printW();
    neuro.fit(training_data, targets, 50000, 0.1);
    std::cout << "Weights after fit:\t"; neuro.printW();
    getAcc(training_data, neuro);

    std::vector<std::vector<int>> test_data = readTestDataFromFile("data/test_data.txt");
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

    return 0;
}

