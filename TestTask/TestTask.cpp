#include <iostream>
#include <clocale>
#include <string>
#include <regex>
#include <algorithm>
#include <stack>

using namespace std;

string deleteSpaces(const string&);
//! А здесь не надо по ссылке передавать? Касается и функции maxMinElement()
//! Про эту функцию забыл
string addEllipsis(const string&, const size_t&);
bool isRightBracketSequence(const string&);
int findSaddlePoint(const vector<vector<int>>&);
int minMaxElement(const vector<vector<int>>&);
int maxMinElement(const vector<vector<int>>&);
void separator(int);
//g

int main()
{
	setlocale(LC_ALL, "russian");
	separator(1);
	string text;
	//    ! Будет ли в данном случае копироваться строка в функцию deleteSpaces()? В каком случае будет копироваться?
		// Строка будет скопирована, потому что передается значение. Если передать по ссылке, строка не будет копироваться.
//	! Не совсем так. Скорее всего компилятор оптимизирует этот случай и память будет выделятся ровно один раз. Надо прочитать про RVO, NRVO, Copy elision
	text = deleteSpaces("  Lorem   ipsum  dolor      sit  amet,    consectetuer adipiscing elit.       Maecenas porttitor congue   massa. Fusce posuere, magna sed  pulvinar ultricies, purus lectus malesuada libero, sit amet commodo magna eros quis     urna.   ");
	cout << addEllipsis(text, 40) << endl;

	separator(2);
	cout << isRightBracketSequence("((x * y) + (2 * (x + y))) * (y + 3)") << endl;
	cout << isRightBracketSequence("((((x * y) + (2 * (x - y)))") << endl;

	separator(3);
	vector<vector<int>> matrix = { {8,-2,9,-3},
								{6,5,6,8},
								{-2,4,-9,5} };
	//    ! А если множество будет множество селовых точек в матрице?
		// Насколько я понял, если седловых точек в матрице несколько, то они все равны по значению.
//	! Ну да. В задаче речи о выводе местоположения элементов не шло
	cout << "Седловая точка: " << findSaddlePoint(matrix) << endl;
}

//Задание1
//! Как передаются аргументы в C/C++? В данном случае надо передавать аргумент по константной ссылке
// По значению и по ссылке.
//! Еще по указателю можно передать аргумент функции. Это пришло из C
string deleteSpaces(const string& text)
{
	//Замена множественных пробелов на единичный
//	! Почему выбрана такая запись регулярного выражения?
	string newText = regex_replace(text, regex("[[:s:]]{2,}"), " ");
	//Обрезаем начало и конец, если присутсвуют пробелы
	newText.erase(0, newText.find_first_not_of(" "));
	newText.erase(newText.find_last_not_of(" ") + 1);
	return newText;
}

string addEllipsis(const string& text, const size_t& m)
{
	//Возврат подстроки не более m символов
//	! Может возникнуть переполнение int. Нужно использовать std::string::size_type
//	! Зачем использовать else, если в блоке, который выполнится при истинности условия, написан return?
//	! Записать, используя тернарный оператор
	return text.size() > m ? text.substr(0, m) + "..." : text;
}

//Задание 2
//! Название функции, мягко говоря, не очень информативное
bool isRightBracketSequence(const string& text)
{
	stack <char> brackets;
	for (size_t i = 0; i < text.length(); i++)
	{
		if (text[i] == ')')
		{
			if (brackets.top() == '(')
			{
				brackets.pop();
			}
			else
			{
				return false;
			}
		}
		else if (text[i] == '(')
		{
			brackets.push('(');
		}
	}
	//    ! Записать по-человечески
	return brackets.empty() ? true : false;
}

// Задание 3

//Возврат седловой точки
int findSaddlePoint(const vector<vector<int>>& matrix)
{
	if(!matrix.empty())
	if (minMaxElement(matrix) == maxMinElement(matrix))
		return minMaxElement(matrix);
	cout << "Седловой точки нет." << endl;
	//    ! Что такое NAN? У меня компилятор не понимает (gcc version 12.2.0)
	return 0;
}

//Поиск минимакса
int minMaxElement(const vector<vector<int>>& matrix)
{
	vector<int> results;
	//    ! Зачем выставлять переменную там, где она не нужна?
	for (size_t i = 0; i < matrix.size(); i++)
	{
		//        	! Для поиска максимума или минимума есть стандартные функции        
//		! Просто так разыменовывать указатель опасно. Что если придет пустой массив?
		// В голову приходит только try catch или проверка массива на пустоту перед вызовом функций.
		results.push_back(*max_element(matrix[i].begin(), matrix[i].end()));
	}
	//    ! Для поиска максимума или минимума в массиве есть стандартные функции
	return *min_element(results.begin(), results.end());
}

//Поиск максимина
int maxMinElement(const vector<vector<int>>& matrix)
{
	vector<int> results;
	int min;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		min = matrix[i][0];
		for (size_t j = 0; j < matrix[0].size(); j++)
		{
			if (matrix[i][j] < min)
			{
				min = matrix[i][j];
			}
		}
		results.push_back(min);
	}
	int maxMin = results[0];
	for (size_t i = 0; i < results.size(); i++)
	{
		if (results[i] > maxMin)
		{
			maxMin = results[i];
		}
	}
	return maxMin;
}

void separator(int taskNum)
{
	cout << endl << endl;
	//    ! Как-то надо бы без дублирования кода
	cout << "*****************" << endl;
	cout << "*               *" << endl;
	cout << "*   Задание " << taskNum << "   *" << endl;
	cout << "*               *" << endl;
	cout << "*****************" << endl;
	cout << endl;
}
