#pragma once
#include <iostream>
#include <vector>
using namespace std;

class CGAIndividual
{
public :
	CGAIndividual();
	CGAIndividual(vector<bool> gen);
	CGAIndividual(const CGAIndividual& other);
	~CGAIndividual() {};
	vector<CGAIndividual*> crossover(CGAIndividual* other);
	int sizeOfGenotype();
	void showGenotype();
	void mutation(double probabilityOfMut);
	int fitness();
	void setFitness(int adaptation);
	vector<bool> getGenotype();
	//int* piGetResultAsTable();


private :
	vector<bool> genotype;
	int quality;

};
