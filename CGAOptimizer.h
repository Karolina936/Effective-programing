#pragma once
#include<iostream>
#include<list>
#include "CGAIndividual.h"
#include "CMax3SatProblem.h"
#include <vector>
using namespace std;


#define SIZE_OF_TOURNAMENT  2
#define PROPOPABILITY_OF_CROSSING 0.45
#define PROPABILITY_OF_MUTATION 0.2
#define POPULATION_SIZE 15


class CGAOptimizer
{
public :
	CGAOptimizer(int populationSize, double probabilityOfCross, double probabilityOfMutat, CMax3SatProblem * prob);
	CGAOptimizer(CMax3SatProblem* prob);
	~CGAOptimizer();
	void initialize();
	void showIndviduals();
	CGAIndividual* selectParent(vector<CGAIndividual*> population);
	vector<CGAIndividual*> crossoverOptimizer(CGAIndividual *parent1, CGAIndividual *parent2);
	CGAIndividual* mutationOptimizer(CGAIndividual *individual);
	void runIteration();
	//void addIndividual(vector<CGAIndividual*> newPopulation, CGAIndividual  *child1, CGAIndividual   *child2);
	void setQuality();
	CGAIndividual* pcGetBestFound() { return pc_best_found; }
	void setPcBestFound();
	double bestResult();

private:
	int populationSize;
	double probabilityOfCrossing;
	double probabilityOfMutation;
	vector<CGAIndividual*> population;
	CGAIndividual* pc_best_found;
	CMax3SatProblem* problem;




};
