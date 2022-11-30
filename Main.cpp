#include <iostream>
#include <vector>
#include "CGAIndividual.h"
#include "CMax3SatProblem.h"
#include "CGAOptimizer.h"
#include "Timer.h"
#include <cstdlib>
#include <time.h>
#include <exception>
using namespace TimeCounters;
using namespace std;


#define dMAX_TIME 1 *  60


void vRunExperiment(CMax3SatProblem* pcProblem)
{
	try
	{
		CTimeCounter c_time_counter;

		double d_time_passed;

		CGAOptimizer c_optimizer(pcProblem);

		c_time_counter.vSetStartNow();


		c_optimizer.initialize();

		c_time_counter.bGetTimePassed(&d_time_passed);

		while (d_time_passed <= dMAX_TIME)
		{
			c_optimizer.runIteration();
			c_optimizer.pcGetBestFound();
			c_time_counter.bGetTimePassed(&d_time_passed);
		//	cout << c_optimizer.bestResult() << endl;
		}//while (d_time_passed <= MAX_TIME)
		//cout <<pcProblem->bestResult(c_optimizer.pcGetBestFound());
		cout << c_optimizer.bestResult();
	}//try
	catch (exception& c_exception)
	{
		cout << c_exception.what() << endl;
	}//catch (exception &c_exception)
}//void vRunExperiment(const CEvaluator &cConfiguredEvaluator)


int main()
{
	srand(time(NULL));
	CMax3SatProblem* c_problem;
	c_problem = new CMax3SatProblem();

	if (c_problem->load("m3s_50_0.txt") == true)
	{
		//vRunExperiment(c_problem);
		CGAOptimizer optimizer(c_problem);
		optimizer.initialize();
		optimizer.runIteration();
		cout << optimizer.bestResult();

	}
	/*if (c_problem->load("m3s_100_0.txt") == true)
	{
		vRunExperiment(c_problem);
	}*/
	/*if (c_problem->load("m3s_150_0.txt") == true)
	{
		vRunExperiment(c_problem);
	}*/
	/*if (c_problem->load("m3s_200_0.txt") == true)
	{
		vRunExperiment(c_problem);
	}*/
	/*if (c_problem->load("m3s_250_0.txt") == true)
	{
		vRunExperiment(c_problem);
	}*/
	/*if (c_problem->load("m3s_300_0.txt") == true)
	{
		vRunExperiment(c_problem);
	}*/
}
