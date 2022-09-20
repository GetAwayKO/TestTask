#include <iostream>
#include <clocale>
#include <string>
#include <regex>
#include <algorithm>
#include <stack>

using namespace std;

string deleteSpaces(string);
string addEllipsis(string, int);
bool isRight(string);
int findSaddlePoint(vector<vector<int>>);
int minMaxElement(vector<vector<int>>);
int maxMinElement(vector<vector<int>>);
void separator(int);

int main()
{
    setlocale(LC_ALL, "russian");
    
    separator(1);
    string text;
    text = deleteSpaces("  Lorem   ipsum  dolor      sit  amet,    consectetuer adipiscing elit.       Maecenas porttitor congue   massa. Fusce posuere, magna sed  pulvinar ultricies, purus lectus malesuada libero, sit amet commodo magna eros quis     urna.   ");
    cout << addEllipsis(text,40)<<endl;
    
    separator(2);
    cout << isRight("((x * y) + (2 * (x + y))) * (y + 3)")<<endl;
    cout << isRight("((((x * y) + (2 * (x - y)))")<<endl;
    
    separator(3);
    vector<vector<int>> matrix = {{1,0,3,5},
                                {3,2,4,3},
                                {0,1,-1,4} };
    cout << "Седловая точка: " << findSaddlePoint(matrix) << endl;
}

//Задание1

string deleteSpaces(string text)
{
    //Замена множественных пробелов на единичный
    string newText=regex_replace(text,regex("[[:s:]]{2,}")," ");
    //Обрезаем начало и конец, если присутсвуют пробелы
    newText.erase(0, newText.find_first_not_of(" "));
    newText.erase(newText.find_last_not_of(" ")+1);
    return newText;
}

string addEllipsis(string text,int m)
{
    //Возврат подстроки не более m символов 
    if (text.size() > m)
        return text.substr(0,m) + "...";
    else
        return text;
}

//Задание 2

bool isRight(string text)
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
    if (brackets.empty())
        return true;
    else
        return false;
}

// Задание 3

//Возврат седловой точки
int findSaddlePoint(vector<vector<int>> matrix)
{
    int saddlePoint=0;
    int minMax=minMaxElement(matrix);
    int maxMin=maxMinElement(matrix);
    if (minMax == maxMin)
        return saddlePoint = minMax;
    else
        cout << "Седловой точки нет." << endl;
    return NAN;
}

//Поиск минимакса
int minMaxElement(vector<vector<int>>matrix)
{
    vector<int> results; 
    int max;
    for (size_t i = 0; i < matrix[0].size(); i++)
    {
        max = matrix[0][i];
        for (size_t j = 0; j < matrix.size(); j++)
        {
            if (matrix[j][i] > max)
            {
                max = matrix[j][i];
            }
        }
        results.push_back(max);
    }
    int minMax = results[0];
    for (size_t i = 0; i < results.size(); i++)
    {
        if (results[i] < minMax)
        {
            minMax = results[i];
        }
    }
    return minMax;
}

//Поиск максимина
int maxMinElement(vector<vector<int>>matrix)
{
    vector<int> results;
    int min;
    for (size_t i = 0; i < matrix.size(); i++)
    {
        min = matrix[i][0];
        for (size_t j = 0; j < matrix[0].size(); j++)
        {
            if (matrix[i][j] <min)
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
    for (size_t i = 0; i < 20; i++)
    {
        cout << "*";
    }
    cout << endl<<"*";
    for (size_t i = 0; i < 5; i++)
    {
        cout << " ";
    }
    cout << "Задание " + to_string(taskNum);
    for (size_t i = 0; i < 4; i++)
    {
        cout << " ";
    }
    cout << "*"<<endl;
    for (size_t i = 0; i < 20; i++)
    {
        cout << "*";
    }
    cout << endl;
}