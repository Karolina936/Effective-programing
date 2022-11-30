#pragma once
#include <iostream>
#include <list>
#include <vector>
using namespace std;

class CMax3SatProblem
{
public :
	CMax3SatProblem() {};
	~CMax3SatProblem() {};
	bool load(string plik);
	int compute(vector<bool> genotype);
	int size(); 
    vector<vector<string>> getVector();
	int numberOfClauses();


private: 
	vector<vector<string>> vectorOfString;
};
