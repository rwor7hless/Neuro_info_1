//#include "neuron.h"
#include "perceptron.h"
#include "helper.h"
//void getAcc(std::vector<std::vector<int>>& data, neuron& n) {
//    std::cout  
//              << "\nErrors count:\t\t |" << n.getErrors()
//              << "\nTrain data size:\t |" << data.size()
//              << "\nfit accuracy:\t\t |"  << ((data.size() - n.getErrors())*1.0f / data.size()) * 100 << " %\n";
//}

int main() {
    //auto [training_data, targets] = readTrainDataFromFile("data/train_data_corrupted_1.txt");
    //shuffle_data(training_data, targets);


    //neuron neuro(9, -1, 1, 25);  // Создаем нейрон с 9 весами в диапазоне от -1 до 1, порогом классификации 25 
    //std::cout << "Weights before fit:\t"; neuro.printW();
    //neuro.fit(training_data, targets, 5, 1);
    //std::cout << "Weights after fit:\t"; neuro.printW();
    //getAcc(training_data, neuro);

    //std::vector<std::vector<int>> test_data = readTestDataFromFile("data/test_data.txt");
    //// Предсказание значений на тестовых данных
    //std::vector<int> predictions = neuro.predict(test_data);
    //
    //// Вывод предсказаний
    //for (size_t i = 0; i < test_data.size(); ++i) {
    //    std::cout << "Input: ";
    //    for (int val : test_data[i]) {
    //        std::cout << val;
    //    }
    //    std::cout << " Prediction: " << predictions[i] << std::endl;
    //}
    auto [training_data, targets] = readTrainDataFromFile_p("data/perceptron/train_data_corrupted_0.txt");

    if (training_data.empty() || targets.empty()) {
        std::cerr << "No data loaded from file." << std::endl;
        return 1;
    }

    perceptron p(-1.0, 1.0);

    p.get_weigths();
    p.fit(training_data, targets, 1, 1);

    p.get_weigths();
    std::cout << p.predict({ 0,0,0,0,0,0,0,0,0,0,0,0,1,0,0 });
    return 0;
}

