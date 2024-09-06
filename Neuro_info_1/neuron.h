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
	std::vector<float>	weights;
	float				threshold;
	int					v_error = 0;
	int					t_error = 0;
	std::vector<int>	value_;

public:
	neuron(int size, int min_, int max_, float threshold, std::vector<int>& value);
	void fit(const std::vector<std::vector<int>>& training_data, const std::vector<int>& targets, int epochs, float step);
	std::vector<int> predict(const std::vector<std::vector<int>>& test_data);
	void printW();
	int getErrors();
};


#endif // !NEURON_H


