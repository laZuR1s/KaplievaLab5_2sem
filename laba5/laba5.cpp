#include <iostream>
#include <string>
#include <fstream>
#include<Windows.h>

std::string token(" ,.:;-");
const int n = 35;
const int m = 15;


// interface

int check_file(std::ifstream& file);
int create_matrix(std::ifstream& file, std::string matrix[n], std::string& combination);
void out_matrix(std::ofstream& file, std::string matrix[n], int row);


// task

void reverseStr(std::string& str);
bool contains_on(const std::string& word, std::string& combination);
void simple_choice_sort(std::string matrix[n], int row);
void task(std::ifstream& input, std::ofstream& output,std::string& combination);

int main()
{
	SetConsoleOutputCP(1251);

	bool correctfile{ false };
	do
	{
		

		bool flag = true;
		std::string filename;
		while (flag)
		{
			std::cout << "\nВведите имя файла(полностью, с .txt): ";
			std::cin >> filename;
			std::cin.ignore();
			std::ifstream input1(filename);
			if (check_file(input1)==1)
				flag = false;
		}
		std::ifstream input(filename);

		
			std::cout << "\nВведите подстроку: ";
			std::string combination;
			std::cin >> combination;
			correctfile = true;
			std::cout << "\nФайл output.txt был создан \n";
			std::ofstream output("output.txt");
			task(input, output, combination);
			input.close();
			output.close();

		
	} while (!correctfile);
	std::cin.ignore(std::cin.rdbuf()->in_avail()).get();;
}

// interface

int check_file(std::ifstream& file)
{
	int res = 1;
	if (!file)
	{
		res = -1;
		std::cout << "Файл не найден!\n";
	}
	else
		if (file.peek() == EOF)
		{
			res = 0;
			std::cout << "Файл пустой\n";
		}
	return res;
}

int create_matrix(std::ifstream& file, std::string matrix[n],std::string& combination)
{
	int row{};
	std::string line;
	while (getline(file, line) && row < n)
	{
		size_t start{}, end{};
		while ((start = line.find_first_not_of(token, end)) != std::string::npos && row < n)
		{
			end = line.find_first_of(token, start);
			matrix[row] = line.substr(start, end - start);
			if (contains_on(matrix[row],combination))
				row++;
		}
	}
	return row;
}

void out_matrix(std::ofstream& file, std::string matrix[n], int row)
{
	for (int i{}; i < row; ++i)
		file << matrix[i] << '\n';
}

// task 


bool contains_on(const std::string& word,  std::string& combination)
{
	bool result = false;
	if (word.find(combination) != std::string::npos)
		result = true;
	reverseStr(combination);
	if (word.find(combination)!=std::string::npos)
		result = true;

	return result;
}

void reverseStr(std::string& str)
{
	int n = str.length();

	for (int i = 0; i < n / 2; i++)
		std::swap(str[i], str[n - i - 1]);
}

void simple_choice_sort(std::string matrix[n], int row)
{
	for (int i{}; i < row; ++i)
		for (int j{}; j < row - i - 1; ++j)
		{
			if (matrix[j].compare(matrix[j + 1]) > 0)
				std::swap(matrix[j], matrix[j + 1]);
		}
}

void task(std::ifstream& input, std::ofstream& output, std::string& combination)
{
	std::string matrix[n];
	int row = create_matrix(input, matrix, combination);
	simple_choice_sort(matrix, row);
	out_matrix(output, matrix, row);
}

