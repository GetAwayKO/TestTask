#include <iostream>
#include <clocale>
#include <string>
#include <regex>
#include <algorithm>
#include <stack>

using namespace std;

string deleteSpaces(const string&);
string addEllipsis(string, size_t);
bool isRightBracketSequence(const string&);
int findSaddlePoint(const vector<vector<int>>&);
int minMaxElement(const vector<vector<int>>&);
int maxMinElement(const vector<vector<int>>&);
void separator(int);

int main()
{
	setlocale(LC_ALL, "russian");
	separator(1);
	string text;
	//    ! ����� �� � ������ ������ ������������ ������ � ������� deleteSpaces()? � ����� ������ ����� ������������?
		// ������ ����� �����������, ������ ��� ���������� ��������. ���� �������� �� ������, ������ �� ����� ������������.
	text = deleteSpaces("  Lorem   ipsum  dolor      sit  amet,    consectetuer adipiscing elit.       Maecenas porttitor congue   massa. Fusce posuere, magna sed  pulvinar ultricies, purus lectus malesuada libero, sit amet commodo magna eros quis     urna.   ");
	cout << addEllipsis(text, 40) << endl;

	separator(2);
	cout << isRightBracketSequence("((x * y) + (2 * (x + y))) * (y + 3)") << endl;
	cout << isRightBracketSequence("((((x * y) + (2 * (x - y)))") << endl;

	separator(3);
	vector<vector<int>> matrix = { {8,-2,9,-3},
								{6,5,6,8},
								{-2,4,-9,5} };
	//    ! � ���� ��������� ����� ��������� ������� ����� � �������?
		// ��������� � �����, ���� �������� ����� � ������� ���������, �� ��� ��� ����� �� ��������.
	cout << "�������� �����: " << findSaddlePoint(matrix) << endl;
}

//�������1
//! ��� ���������� ��������� � C/C++? � ������ ������ ���� ���������� �������� �� ����������� ������
// �� �������� � �� ������.
string deleteSpaces(const string& text)
{
	//������ ������������� �������� �� ���������
//	! ������ ������� ����� ������ ����������� ���������?
	string newText = regex_replace(text, regex("[[:s:]]{2,}"), " ");
	//�������� ������ � �����, ���� ����������� �������
	newText.erase(0, newText.find_first_not_of(" "));
	newText.erase(newText.find_last_not_of(" ") + 1);
	return newText;
}

string addEllipsis(string text, size_t m)
{
	//������� ��������� �� ����� m ��������
//	! ����� ���������� ������������ int. ����� ������������ std::string::size_type
//	! ����� ������������ else, ���� � �����, ������� ���������� ��� ���������� �������, ������� return?
//	! ��������, ��������� ��������� ��������
	return text.size() > m ? text.substr(0, m) + "..." : text;
}

//������� 2
//! �������� �������, ����� ������, �� ����� �������������
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
	//    ! �������� ��-�����������
	return brackets.empty() ? true : false;
}

// ������� 3

//������� �������� �����
int findSaddlePoint(const vector<vector<int>> &matrix)
{
	if (minMaxElement(matrix) == maxMinElement(matrix))
		return minMaxElement(matrix);
	else
		cout << "�������� ����� ���." << endl;
	//    ! ��� ����� NAN? � ���� ���������� �� �������� (gcc version 12.2.0)
	return 0;
}

//����� ���������
int minMaxElement(const vector<vector<int>> &matrix)
{
	vector<int> results;
	//    ! ����� ���������� ���������� ���, ��� ��� �� �����?
	for (size_t i = 0; i < matrix.size(); i++)
	{
		//        	! ��� ������ ��������� ��� �������� ���� ����������� �������        
		results.push_back(*max_element(matrix[i].begin(), matrix[i].end()));
	}
	//    ! ��� ������ ��������� ��� �������� � ������� ���� ����������� �������
	return *min_element(results.begin(), results.end());
}

//����� ���������
int maxMinElement(const vector<vector<int>> &matrix)
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
	//    ! ���-�� ���� �� ��� ������������ ����
	cout << "*****************" << endl;
	cout << "*               *" << endl;
	cout << "*   ������� "<< taskNum<<"   *" << endl;
	cout << "*               *" << endl;
	cout << "*****************" << endl;
	cout << endl;
}