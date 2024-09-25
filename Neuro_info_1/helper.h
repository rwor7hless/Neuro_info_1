#ifndef HELPER_H
#define HELPER_H
#include "includes.h"

/*
Функция последовательно идет по файлу с тренировочными данными и разбивает его на 2 массива: массив входных данных и массив разметки

Данные идут в формате: {Данные} {разметка}
прим: 000101101 0 - ненужное для распознавания 
      011001010 1 - нужное для распознавания
*/

std::pair<std::vector<std::vector<int>>, std::vector<int>> readTrainDataFromFile(const std::string& filename) {
    std::vector<std::vector<int>> data;
    std::vector<int> targets;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return { data, targets };
    }

    while (std::getline(file, line)) {
        std::vector<int> row;
        std::istringstream iss(line);
        std::string token;
        iss >> token;
        for (char c : token) {
            if (c == '0' || c == '1') {
                row.push_back(c - '0');
            }
        }
        data.push_back(row);

        iss >> token;
        targets.push_back(std::stoi(token));
    }

    file.close();
    return { data, targets };
}

std::pair<std::vector<std::vector<int>>, std::vector<std::string>> readTrainDataFromFile_p(const std::string& filename) {
    std::vector<std::vector<int>> data;
    std::vector<std::string> targets;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return { data, targets };
    }

    while (std::getline(file, line)) {
        std::vector<int> row;
        std::istringstream iss(line);
        std::string token;
        iss >> token;
        for (char c : token) {
            if (c == '0' || c == '1') {
                row.push_back(c - '0');
            }
            else {
                std::cerr << "Invalid character in data: " << c << std::endl;
                return { data, targets };
            }
        }
        data.push_back(row);

        iss >> token;
        targets.push_back(token);
    }

    file.close();
    return { data, targets };
}

std::vector<std::vector<int>> readTestDataFromFile(const std::string& filename) {
    std::vector<std::vector<int>> data;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return data;
    }

    while (std::getline(file, line)) {
        std::vector<int> row;
        for (char c : line) {
            if (c == '0' || c == '1') {
                row.push_back(c - '0');
            }
        }
        data.push_back(row);
    }

    file.close();
    return data;
}

void shuffle_data(std::vector<std::vector<int>>& data, std::vector<int>& targets) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<std::pair<std::vector<int>, int>> combined; // Создаем совмещенный ветор, (Входные данные) - (разметка для них)
    for (size_t i = 0; i < data.size(); ++i) {
        combined.emplace_back(data[i], targets[i]); // заполняем вектор 
    }
    std::shuffle(combined.begin(), combined.end(), g); // перемешиваем его

    /*
    Этот цикл нужен для того, чтобы восстановить соответствие между данными и разметками для них
    По большому счету мы просто перезаписываем вектор
    */

    for (size_t i = 0; i < combined.size(); ++i) {
        data[i] = combined[i].first;
        targets[i] = combined[i].second;
    }
}

void shuffle_data_perceptron(std::vector<std::vector<int>>& data, std::vector<std::string>& targets) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<std::pair<std::vector<int>, std::string>> combined; // Создаем совмещенный ветор, (Входные данные) - (разметка для них)
    for (size_t i = 0; i < data.size(); ++i) {
        combined.emplace_back(data[i], targets[i]); // заполняем вектор 
    }
    std::shuffle(combined.begin(), combined.end(), g); // перемешиваем его

    /*
    Этот цикл нужен для того, чтобы восстановить соответствие между данными и разметками для них
    По большому счету мы просто перезаписываем вектор
    */

    for (size_t i = 0; i < combined.size(); ++i) {
        data[i] = combined[i].first;
        targets[i] = combined[i].second;
    }
}

#endif // !HELPER_H