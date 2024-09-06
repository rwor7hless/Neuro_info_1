#ifndef NEURON_H
#define NEURON_H
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iomanip>
class neuron
{

private:
	std::vector<float>	weights; // Веса каждого нейрона
	float				threshold; // Пороговое значение, при котором произойдет активация
	int					v_error = 0; // Количество ошибок при обучении

public:
	neuron(int size, int min_, int max_, float threshold); // В конструкторе задаем входной размер, мин\макс значения для заполнения и порог
	void fit(const std::vector<std::vector<int>>& training_data, const std::vector<int>& targets, int epochs, float step); // Обучение, на вход получаем данные, разметку, кол-во эпох и шаг обучения
	std::vector<int> predict(const std::vector<std::vector<int>>& test_data);// Уже для обученного нейрона попытка предсказать неразмеченные данные
	void printW(); // вывод весов
	int getErrors(); // получить количество ошибок при обучении
};


#endif // !NEURON_H


