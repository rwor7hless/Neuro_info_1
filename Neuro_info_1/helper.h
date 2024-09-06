#ifndef HELPER_H
#define HELPER_H
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <random>

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

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

std::vector<std::vector<int>> parse_data(const std::vector<std::string>& raw_data) {
    std::vector<std::vector<int>> data;
    for (const auto& line : raw_data) {
        std::vector<int> input;
        std::istringstream iss(line);
        std::string token;
        iss >> token;
        for (char c : token) {
            input.push_back(c - '0');
        }
        data.push_back(input);
    }
    return data;
}

std::vector<int> parse_targets(const std::vector<std::string>& raw_data) {
    std::vector<int> targets;
    for (const auto& line : raw_data) {
        std::istringstream iss(line);
        std::string token;
        iss >> token;
        iss >> token;
        targets.push_back(std::stoi(token));
    }
    return targets;
}

void shuffle_data(std::vector<std::vector<int>>& data, std::vector<int>& targets) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<std::pair<std::vector<int>, int>> combined;
    for (size_t i = 0; i < data.size(); ++i) {
        combined.emplace_back(data[i], targets[i]);
    }
    std::shuffle(combined.begin(), combined.end(), g);
    for (size_t i = 0; i < combined.size(); ++i) {
        data[i] = combined[i].first;
        targets[i] = combined[i].second;
    }
}

#endif // !HELPER_H