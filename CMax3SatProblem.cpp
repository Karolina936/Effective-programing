#pragma once
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <list>
#include <vector>
#include <ctime>
#include "CMax3SatProblem.h"

using namespace std;


bool CMax3SatProblem::load(string dokument)
{
    fstream plik;

  
    vector<string> listOfString;
    plik.open(dokument , ios::in);
    if (plik.good() == false) return false;
    else 
    {
        string line;
        string result;
        do
        {
            getline(plik, line);
            listOfString.push_back(line);
        } while (line != "");
    }
    plik.close();

   
    
    for (string line : listOfString)
    {
        cout << line << endl;
        vector<string> helperList;
        string result;
        for (char znak : line)
        {
            
            if (isdigit(znak) || znak == '-')
            {
                result += znak;
            }
            else if(!result.empty())
            {
                helperList.push_back(result);
                result.clear();
            }
        }
        vectorOfString.push_back(helperList);
    }

    return true;
}

int CMax3SatProblem::size()
{
    int max = 0;
    for (vector<string> list : vectorOfString)
    {
       for(string expression : list)
       {
           int number = stoi(expression);
           if (number > max) max = number;
        }
 
    }
    max += 1;
 
    return max;
}

int CMax3SatProblem::compute(vector<bool> genotype)
{
    int sum = 0;
    int i = 0;
    bool satisfied = false;

    for (vector<string> problem : vectorOfString)
    {
        while(problem.size() > i && !satisfied) 
        {
            if (problem[i].at(0) == '-')
            {
                if (genotype[stoi(problem[i]) * (-1)] == false)
                {
                    satisfied = true; 
                    sum += 1;
                }
            }
            else if (genotype[stoi(problem[i])] == true)
            {
                satisfied = true;
                sum += 1;
            }
            i++;
        }
        i = 0;
        satisfied = false;

    }
    return sum;

}

vector<vector<string>> CMax3SatProblem::getVector()
{
    return vectorOfString;
}

int CMax3SatProblem::numberOfClauses()
{
    int clauses = 0;
    for (vector<string> problem : vectorOfString)
    {
        clauses++;
    }
    return clauses;
}
