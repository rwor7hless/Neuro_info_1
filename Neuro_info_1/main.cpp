#include "neuron.h"
#include "reader.h"

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
   
    std::vector<std::vector<int>> training_data = readDataFromFile("data/train_data.txt");
    std::vector<std::vector<int>> test_data = readDataFromFile("data/test_data.txt");
    int count = 1;
    shuffle_data(training_data);
    shuffle_data(test_data);


    neuron neuro(9, -1, 1, 25, numbers[3]);  // Создаем нейрон с 9 весами в диапазоне от -1 до 1, порогом классификации 25 и распознаваемым числом - 3
    std::cout << "Веса до обучения:   "; neuro.printW();
    neuro.fit(training_data, 2 , 1); 
    std::cout << "Веса после обучения:"; neuro.printW();

    for (auto test : test_data) {
        int prediction = neuro.predict(test);
        if (prediction == 1) 
        { 
            std::cout << "Данные: " << count << " Это точно тройка\n"; 
        }
        else 
        { 
            std::cout << "Данные: " << count << " Это точно не тройка\n"; 
        }
        count++;
    }
    getAcc(training_data, neuro);
    return 0;
}

