#pragma once
#include <iostream>
#include <vector>    
#include <time.h> 
#include <cstdlib> 
#include "CGAOptimizer.h"
using namespace std;

CGAOptimizer::CGAOptimizer(int populatSize, double probabilityOfCross, double probabilityOfMutat, CMax3SatProblem* prob)
{
	populationSize = populatSize;
	probabilityOfCrossing = probabilityOfCross;
	probabilityOfMutation = probabilityOfMutat;
	problem = prob;
	pc_best_found = NULL;
}

CGAOptimizer::CGAOptimizer(CMax3SatProblem* prob)
{
	populationSize = POPULATION_SIZE;
	probabilityOfCrossing = PROPOPABILITY_OF_CROSSING;
	probabilityOfMutation = PROPABILITY_OF_MUTATION;
	problem = prob;
	pc_best_found = NULL;
}

CGAOptimizer::~CGAOptimizer()
{
	if (problem != NULL) delete problem;
	if (population.size() != 0)
		for(int i=0; i<population.size(); i++)
	{
			delete population[i];
	}
	if (pc_best_found != NULL) delete pc_best_found;
}

void CGAOptimizer::setPcBestFound()
{
	
	int best = 0;
	int index = 0;
	for (int i = 0; i < population.size(); i++)
	{
		if (population[i]->fitness() > best) {
			best = population[i]->fitness();
			index = i;
		}
	}
	if (pc_best_found != NULL)
	{
		if (pc_best_found->fitness() < population[index]->fitness())
		{
		    delete pc_best_found;
			pc_best_found = new CGAIndividual(*population[index]);
			}
		
	}
	else pc_best_found = new CGAIndividual(*population[index]);
	
}
void CGAOptimizer::initialize()
{
	int random;
	int i = 0;
	int numberOfIndividuals = 0;
	vector<bool> genotype;
	while(populationSize > numberOfIndividuals)
	{
		while (problem->size() > i)
		{
			random = rand() % 2 + 1;
			if (random == 1) genotype.push_back(true);
			else genotype.push_back(false);
			i++;
		}
		population.push_back(new CGAIndividual(genotype));
		numberOfIndividuals++;
		genotype.clear();
		i = 0;
	}
	setQuality();
	setPcBestFound();
}

void CGAOptimizer::setQuality()
{
	for (CGAIndividual* individual : population)
	{
		individual->setFitness(problem->compute(individual->getGenotype()));
	}
}

CGAIndividual* CGAOptimizer::selectParent(vector<CGAIndividual*> individuals)
{
	int t = SIZE_OF_TOURNAMENT;
	int random;
	int position = 0;
	int quality = 0;
	while (t > 0)
	{
		random = rand() % populationSize;
		if (individuals[random]->fitness() > quality)
		{
			quality = individuals[random]->fitness();
			position = random;

		}
		t--;
	}
	return individuals[position];


}

vector<CGAIndividual*> CGAOptimizer::crossoverOptimizer(CGAIndividual* parent1, CGAIndividual* parent2)
{
	vector<CGAIndividual*> children;
	if ((float)rand() / RAND_MAX < probabilityOfCrossing)
	{
		children = parent1->crossover(parent2);
	}
	else
	{
		children.push_back(new CGAIndividual(*parent1));
		children.push_back(new CGAIndividual(*parent2));
	}
	return children;
}

CGAIndividual* CGAOptimizer::mutationOptimizer(CGAIndividual* individual)
{
	individual->mutation(probabilityOfMutation);
	return individual;
}

void CGAOptimizer::runIteration()
{
	vector<CGAIndividual*> newPopulation;
	CGAIndividual* parent1;
	parent1 = new CGAIndividual;
	CGAIndividual* parent2;
	parent2 = new CGAIndividual;
	vector<CGAIndividual*> children;
	while (newPopulation.size() < population.size()) 
	{
		parent1 = selectParent(population);
		parent2 = selectParent(population);
		children = crossoverOptimizer(parent1, parent2);
		children[0] = mutationOptimizer(children[0]);
		children[1] = mutationOptimizer(children[1]);
		newPopulation.push_back(children[0]);
		newPopulation.push_back(children[1]);
		children.clear();
		parent1 = NULL;
		parent2 = NULL;
		
	}
	for (int i = 0; i < population.size(); i++)
	{
		delete population[i];
	}
	
	population.clear();

	for (CGAIndividual* individual : newPopulation)
	{
		population.push_back(individual);
	}
	setQuality();
	setPcBestFound();

}


void CGAOptimizer::showIndviduals()
{
	for (CGAIndividual* individual : population)
	{
		individual->showGenotype();
	}
}

double CGAOptimizer::bestResult()
{
	return (double)pc_best_found->fitness() / (double)problem->numberOfClauses();
}