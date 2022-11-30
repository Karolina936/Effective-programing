#pragma once
#include <iostream>
#include "CGAIndividual.h"
#include <cstdlib>     
#include <time.h> 
using namespace std;

CGAIndividual::CGAIndividual()
{
	quality = 0;
}

CGAIndividual::CGAIndividual(vector<bool> gen)
{
	for (int i = 0; i < gen.size(); i++)
	{
		genotype.push_back(gen[i]);
	}
	quality = 0;
}

CGAIndividual::CGAIndividual(const CGAIndividual& other)
{
	for (int i = 0; i < other.genotype.size();  i++)
	{
		genotype.push_back(other.genotype[i]);
	}
	quality = other.quality;
}


int CGAIndividual::sizeOfGenotype()
{
	return genotype.size();
}

vector<CGAIndividual*> CGAIndividual::crossover(CGAIndividual* other)
{
	vector<bool> child1_vector;
	vector<bool> child2_vector;
	int size = sizeOfGenotype();
	int random;
	for (int i = 0; i < size; i++)
	{
		random = rand() % 2 + 1;
			if (random == 1)
			{
				child1_vector.push_back(genotype[i]);
				child2_vector.push_back(other->genotype[i]);
			}
			else
			{
				child1_vector.push_back(other->genotype[i]);
				child2_vector.push_back(genotype[i]);
			}
	}
	
	vector<CGAIndividual*> result;
	result.push_back(new CGAIndividual(child1_vector));
	result.push_back(new CGAIndividual(child2_vector));
	
	return result;
}

void CGAIndividual::showGenotype()
{
	for (int i = 0; i < sizeOfGenotype(); i++)
	{
		cout << genotype[i] << " ";
	}
	cout << endl;
}

void CGAIndividual::mutation(double probabilityOfMut)
{
	double probability;
	for (int i = 0; i < sizeOfGenotype(); i++)
	{
		probability = (float)rand()/ RAND_MAX;
		if (probability < probabilityOfMut)
		{
			if (genotype[i] == true) genotype[i] = false;
			else genotype[i] = true;
		}

	}
}

int CGAIndividual::fitness()
{
	return quality;
}

void CGAIndividual::setFitness(int adaptation)
{
	quality = adaptation;
}


vector<bool> CGAIndividual:: getGenotype()
{
	return genotype;
}

/*int* CGAIndividual::piGetResultAsTable()
{
	int* table = new int[sizeOfGenotype()];
	for (int i = 0; i < sizeOfGenotype(); i++)
	{
		if (genotype[i] == false) table[i] = 0;
		else table[i] = 1;
	}
	return table;
}*/;

