#include "neuron.h"
#include "perceptron.h"
#include <format>
#include "helper.h"
void getAcc_p(std::vector<std::vector<int>>& data, perceptron& n) {
    std::cout  
              << "\nErrors count:\t\t |" << n.get_errors()
              << "\nTrain data size:\t |" << data.size()
              << "\nfit accuracy:\t\t |"  << ((data.size() - n.get_errors())*1.0f / data.size()) * 100 << " %\n";
}

void getAcc_n(std::vector<std::vector<int>>& data, neuron& n) {
    std::cout
        << "\nErrors count:\t\t |" << n.getErrors()
        << "\nTrain data size:\t |" << data.size()
        << "\nfit accuracy:\t\t |" << ((data.size() - n.getErrors()) * 1.0f / data.size()) * 100 << " %\n";
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    for (int i = 0; i <= 9; ++i) {
        std::cout << std::format("\n\n_________________________NOW ARE {} ERRORS_________________________",i) << std::endl;
        auto [training_data, targets] = readTrainDataFromFile_p(std::format("data/train_data_corrupted_{}.txt", i));
        shuffle_data(training_data, targets);
        if (training_data.empty() || targets.empty()) {
            std::cerr << "No data loaded from file." << std::endl;
            return 1;
        }

        perceptron p(-5, 5, 2, 9);
        neuron n(9, -5, 5, 25);
        std::cout << "\nPERCEPTRON INITIAL WEIGHS:\n";
        p.get_weigths();
        std::cout << "\nNEURON INITIAL WEIGHS:\n";
        n.printW();
        p.fit(training_data, targets, 4, 1);
        n.fit(training_data, targets, 4, 1);
        std::cout << "\nPERCEPTRON FINAL WEIGHS:\n";
        p.get_weigths();
        std::cout << "\nNEURON FINAL WEIGHS:\n";
        n.printW();
        std::cout << "\nPerceptron accuracy:";
        getAcc_p(training_data, p);
        std::cout << "\nNeuron accuracy:";
        getAcc_n(training_data, n);
        

    }
    return 0;
}

