#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include "includes.h"

class perceptron
{
private:
	std::vector<std::vector<float>>		m_weights;
	int									m_errors;
	std::vector<std::string>			m_numbers = {
													"1", "0"
													};
public:
	perceptron(int min_, int max_, int nums, int n_lenght);
	std::string predict(const std::vector<int>& test_data);
	void fit(const std::vector<std::vector<int>>& training_data, const std::vector<std::string>& targets, int epochs, float step);
	void get_weigths() const;
	int get_errors() { return this->m_errors; };
};
#endif // !PERCEPTRON_H



