//  MFO_main.cpp
//
//  Author:
//       Ahmad Dajani <eng.adajani@gmail.com>
//
//  Copyright (c) 2020 Ahmad Dajani
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <Problem.h>
#include <Algorithm.h>
#include <Solution.h>
#include <ProblemFactory.h>
#include <iostream>
#include <MFO.h>
#include <time.h>

int main(int argc, char ** argv) {
	clock_t t_ini, t_fin;

	Problem *problem;     // The problem to solve
	Algorithm *algorithm; // The algorithm to use

	if (argc>=2) {
		problem = ProblemFactory::getProblem(argc, argv);
		cout << "Selected problem: " << problem->getName() << endl;
	} else {
		cout << "No problem selected." << endl;
		cout << "Default problem will be used: Sphere" << endl;
		problem = ProblemFactory::getProblem(const_cast<char *>("Sphere"));
	}

	algorithm = new MFO(problem);

	int swarmSize = 30;
	int maxIterations = 1000;
	algorithm->setInputParameter("searchAgentsCount",&swarmSize);
	algorithm->setInputParameter("maxIterations",&maxIterations);

	// Execute the Algorithm
	t_ini = clock();
	SolutionSet * population = algorithm->execute();
	t_fin = clock();
	double secs = (double) (t_fin - t_ini);
	secs = secs / CLOCKS_PER_SEC;

	// Result messages
	cout << "Total execution time: " << secs << "s" << endl;
	cout << "Variables values have been written to file VAR" << endl;
	population->printVariablesToFile("VAR");
	cout << "Objectives values have been written to file FUN" << endl;
	population->printObjectivesToFile("FUN");

	delete algorithm;
	delete population; 
} // main
