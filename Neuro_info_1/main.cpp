#include "perceptron.h"
#include "helper.h"
void getAcc(std::vector<std::vector<int>>& data, perceptron& n) {
    std::cout  
              << "\nErrors count:\t\t |" << n.get_errors()
              << "\nTrain data size:\t |" << data.size()
              << "\nfit accuracy:\t\t |"  << ((data.size() - n.get_errors())*1.0f / data.size()) * 100 << " %\n";
}

int main() {


    auto [training_data, targets] = readTrainDataFromFile_p("data/perceptron/train_data_corrupted_0.txt");
    auto test_data = readTestDataFromFile("data/perceptron/test_data_p.txt");
    std::vector<std::string> answers;
    if (training_data.empty() || targets.empty()) {
        std::cerr << "No data loaded from file." << std::endl;
        return 1;
    }

    perceptron p(-1,1);


    p.get_weigths();
    p.fit(training_data, targets, 5, 1);
    p.get_weigths();

    for (auto& data : test_data)
    {
        answers.push_back(p.predict(data));
    }

    for (size_t i = 0; i < test_data.size(); ++i) {
        std::cout << "Input: ";
        for (int val : test_data[i]) {
            std::cout << val;
        }
        std::cout << " Prediction: " << p.predict(test_data[i]) << std::endl;
    }
    getAcc(training_data, p);
    return 0;
}

