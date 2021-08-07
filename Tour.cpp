//
// Created by Tiffany Gu on 2020-11-23.
// This is the tour class.
//

#include "Tour.hpp"

// constructor
Tour::Tour(vector<City> *masterList, int n) {

    while (temp_vector.size() < n) {
        int x = rand_num(0, n);
        if (count(temp_vector.begin(), temp_vector.end(), x))
            continue;
        else {
            temp_vector.push_back(x);
        }

    }

    for (int j = 0; j < n; j++) {
        int r = temp_vector[j];
        City *c = &masterList->at(r);
        population.push_back(c);
    }

    shuffle_cities();
    eliteFlag = false;
    selected = false;
    totalDistance = 0;
    fitness = 0;

    for (int i = 0; i < population.size(); i++) {
        if (i == 0) {
            totalDistance += 0;
            totalDistance += 0;
        } else {
            int diffX = abs(population[i]->getX() - population[i - 1]->getX());
            int diffY = abs(population[i]->getY() - population[i - 1]->getY());
            float temp = sqrt(pow(diffX, 2) +
                              pow(diffY, 2) * 1.0);
            totalDistance += temp;
        }

        fitness = determine_fitness(totalDistance);
        updateSequence();
        updateTotalDistance();
        updateFitness();
    }
}

// mutation. if this tour is selected then it will be mutated
void Tour::mutate(float num){
    for (int i = 0; i < population.size(); i++) {
        while (true) {
            int r = rand_num(1, 3);
            float random = (float) rand_num(1, 100) / 100;
            if (i == 0) {
                if ((num - random) > 0) {
                    if (r == 3) {
                        swap(*population[0], *population[1]);
                        break;
                    } else if (r == 2) {
                        break;
                    } else {
                        break;
                    }
                } else {
                    break;
                }


            } else {
                if ((num - random) > 0) {
                    if (r == 2) {
                        swap(*population[i], *population[i - 1]);
                        break;
                    } else if (r == 3) {
                        swap(*population[i], *population[i + 1]);
                        break;
                    } else {
                        break;
                    }
                } else {
                    break;
                }

            }

        }
        updateSequence();
        updateTotalDistance();
        updateFitness();

    }
}

// helper function to update total distance
void Tour::updateTotalDistance(){
    totalDistance = 0;
    for (int i = 1; i < population.size(); i++) {

        if (i == 0) {
            totalDistance += 0;
            totalDistance += 0;
        } else {
            int diffX = abs(population[i]->getX() - population[i - 1]->getX());
            int diffY = abs(population[i]->getY() - population[i - 1]->getY());
            float temp = sqrt(pow(diffX, 2) +
                              pow(diffY, 2) * 1.0);
            totalDistance += temp;
        }

    }
}

// from start and end random generator
int Tour::rand_num(int start, int end) {
    int r = end - start;
    int rnum = start + rand() % r;
    return rnum;
}

// calculate fitness
double Tour::determine_fitness(int totalDistance) {
    double result;
    result = (double) CONSTANT_OF_FITNESS / totalDistance;
    return result;
}

// update genome
void Tour::updateSequence() {
    gnome = "";
    for (int i = 0; i < population.size(); i++) {
        gnome += population[i]->getName();
    }
}

// determine if the tour is elite or not
bool Tour::getEliteFlag(){
    return eliteFlag;
}

// when doing mutation, determine if this tour has been selected or not
bool Tour::getSelectedFlag() {
    return selected;
}

// set elite flag
void Tour::setEliteFlag(bool state) {
    eliteFlag = state;
}

// set selected flag when doing mutation
void Tour::setSelectedFlag(bool state) {
    selected = state;
}

// getter for fitness
double Tour::getFitness() {
    return fitness;
}

// getter for total distance
float Tour::getTotalDistance() {
    return totalDistance;
}

// setter for population in a tour (cities)
void Tour::setPopulation(const vector<City *> &population) {
    Tour::population = population;
}

// helper function to shuffle cities
void Tour::shuffle_cities(){
    random_shuffle(population.begin(), population.end());
}