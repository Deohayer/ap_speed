#include <iostream>
#include <string>

#include "infint/InfInt.h"
#include "ttmath/ttmathint.h"
#include "arbitrary_precision/ap_int.h"
#include "time_metric/time_metric.h"

const int ROUNDS = 100;

std::string rstrings[ROUNDS];
std::string lstrings[ROUNDS];

std::string random(int decimal_digits)
{
	std::string result;
	result.resize(decimal_digits);
	result[0] = 1 + rand() % 9 + '0';
	for (int i = 1; i < decimal_digits; ++i)
	{
		result[i] = rand() % 10 + '0';
	}
	return result;
}

std::string random()
{
	int decimal_digits = 20 + rand() % 80;
	std::string result;
	result.resize(decimal_digits);
	result[0] = 1 + rand() % 9 + '0';
	for (int i = 1; i < decimal_digits; ++i)
	{
		result[i] = rand() % 10 + '0';
	}
	return result;
}

template <typename T>
struct add
{
	unsigned long long int operator()(int digit_count) const
	{
		T left;
		T right;
		unsigned long long int time = 0;
		for (int i = 0; i < ROUNDS; ++i)
		{
			left = rstrings[i];
			right = lstrings[i];
			time += measure_execution_time([&]()
				{
					left + right;
				});
		}
		return time / 1000;
	}
};

template <typename T>
struct sub
{
	unsigned long long int operator()(int digit_count) const
	{
		T left;
		T right;
		unsigned long long int time = 0;
		for (int i = 0; i < ROUNDS; ++i)
		{
			left = rstrings[i];
			right = lstrings[i];
			time += measure_execution_time([&]()
				{
					left - right;
				});
		}
		return time / 1000;
	}
};


template <typename T>
struct mul
{
	unsigned long long int operator()(int digit_count) const
	{
		T left;
		T right;
		unsigned long long int time = 0;
		for (int i = 0; i < ROUNDS; ++i)
		{
			left = rstrings[i];
			right = lstrings[i];
			time += measure_execution_time([&]()
				{
					left * right;
				});
		}
		return time / 1000;
	}
};


template <typename T>
struct division
{
	unsigned long long int operator()(int digit_count) const
	{
		T left;
		T right;
		unsigned long long int time = 0;
		for (int i = 0; i < ROUNDS; ++i)
		{
			left = rstrings[i];
			right = lstrings[i];
			time += measure_execution_time([&]()
				{
					left / right;
				});
		}
		return time / 1000;
	}
};

std::string spaced(const std::string & str, int width)
{
	width -= str.size();
	std::string result = str;
	for (int i = 0; i < width; ++i)
	{
		result.push_back(' ');
	}
	return result;
}

template <template <typename T> typename Func>
void run(const std::string & name, void (*generator)(int))
{
	const std::string hdigits = "Digits";
	const std::string htt = "TTmath";
	const std::string hii = "InfInt";
	const std::string hap = "AP";
	const int width = 25;
	std::cout << name << std::endl;
	std::cout << '|' << spaced(hdigits, width) << '|'
		<< spaced(htt, width) << '|'
		<< spaced(hii, width) << '|'
		<< spaced(hap, width) << '|' << std::endl;
	const int first = 100;
	const int second = 1000;
	const int third = 10000;
	auto singleshot = [&](int digit_count)
	{
		generator(digit_count);
		std::cout << '|' << spaced(std::to_string(digit_count), width) << '|'
			<< spaced(std::to_string(Func<ttmath::Int<1250>>{}(digit_count)), width) << '|'
			<< spaced(std::to_string(Func<InfInt>{}(digit_count)), width) << '|'
			<< spaced(std::to_string(Func<ap::int_d>{}(digit_count)), width) << '|'
			<< std::endl;
	};
	singleshot(first);
	singleshot(second);
	singleshot(third);
}

void generator(int digit_count)
{
	for (int i = 0; i < ROUNDS; ++i)
	{
		lstrings[i] = random(digit_count);
		rstrings[i] = random(digit_count);
	}
}

void mulgenerator(int digit_count)
{
	for (int i = 0; i < ROUNDS; ++i)
	{
		lstrings[i] = random(digit_count / 2);
		rstrings[i] = random(digit_count / 2);
	}
}

void divgenerator(int digit_count)
{
	for (int i = 0; i < ROUNDS; ++i)
	{
		lstrings[i] = random(digit_count);
		rstrings[i] = random();
	}
}


int main()
{
	run<add>(std::string("Addition"), generator);
	run<add>(std::string("Addition"), generator);
	run<sub>(std::string("Subtraction"), generator);
	run<mul>(std::string("Multiplication"), mulgenerator);
	run<division>(std::string("Division"), divgenerator);
	ttmath::Int<20> a;
	system("pause");
	return 0;
}

