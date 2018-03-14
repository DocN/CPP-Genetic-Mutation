#include "Population.hpp"
#include "Cities.hpp"

using namespace std;

Population::Population() {
	generatePop();
	shortestTourInPopulation = 0;
}
void Population::generatePop() {
	Cities * newCityList = new Cities();
	newCityList->generateCities();
	for (int i = 0; i < POPULATION_SIZE; i++) {
		popList.push_back(copyCities(newCityList));
	}
}

void Population::printPopulation() {
	for (int i = 0; i < popList.size(); i++) {
		cout << "--------------------------------------------------" << endl;
		popList.at(i).printCities();
	}
}

void Population::shufflePop() {
	for (int i = 0; i < popList.size(); i++) {
		popList.at(i).shuffleCities();
	}
}

Cities Population::copyCities(Cities * masterList) {
	Cities * cityCopy = new Cities();
	std::vector<City> cityList = masterList->getCityList();
	for (int i = 0; i < cityList.size(); i++) {
		cityCopy->insertCity(cityList.at(i));
	}
	return *cityCopy;
}

void Population::setShortTourIndex(int _shortTourIndex) {
	shortTourIndex = _shortTourIndex;
}

int Population::getShortTourIndex() {
	return shortTourIndex;
}

void Population::setShortestTourInPopulation(double _shortestTourInPopulation) {
	shortestTourInPopulation = _shortestTourInPopulation;
}

double Population::getShortestTourInPopulation() {
	return shortestTourInPopulation;
}


void Population::determine_fitness() {
	setShortTourIndex(0);
	shortestTourInPopulation = (double)RAND_MAX; // Begin by assuming distance is enormous
	double candidate_distance = 0;
	for (int i = 0; i < popList.size(); i++) {
		candidate_distance = popList.at(i).get_tour_distance();
		popList.at(i).setFitness(FITNESS_SCALER / candidate_distance);
		if (candidate_distance <= shortestTourInPopulation) {
			shortTourIndex = i;
			shortestTourInPopulation = candidate_distance;
		}
	}
}

void Population::moveFittest() {
	Cities bestRoute = popList.at(shortTourIndex);
	popList.at(shortTourIndex) = popList.at(0);
	popList.at(0) = bestRoute;
}





