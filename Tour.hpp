//
// Created by Tiffany Gu on 2020-11-23.
// This is the tour class header file.
//

#ifndef INC_3522ASN2_TOUR_HPP
#define INC_3522ASN2_TOUR_HPP

#define CONSTANT_OF_FITNESS 10000
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <random>
#include <algorithm>
#include "City.hpp"

using namespace std;

class Tour {
private:
    bool eliteFlag;
    bool selected;
    string gnome;
    double fitness;
    float totalDistance;
    vector<int> temp_vector;

public:
    vector<City *> population;

    // constructor
    Tour(vector<City> *masterList, int n);

    // function to generated a mutated GNOME
    void mutate(float num);

    // update total distance
    void updateTotalDistance();

    // from start and end
    int rand_num(int start, int end);

    // from start and end
    double determine_fitness(int totalDistance);

    // update fitness helper function
    void updateFitness() {
        fitness = (double) CONSTANT_OF_FITNESS / totalDistance;
    };

    // update the gnome
    void updateSequence();

    // determine if the tour is elite or not
    bool getEliteFlag();

    // set elite flag
    void setEliteFlag(bool state);

    // when doing mutation, determine if this tour has been selected or not
    bool getSelectedFlag();

    // set selected flag when doing mutation
    void setSelectedFlag(bool state);

    // getter for fitness
    double getFitness();

    // getter for total distance
    float getTotalDistance();

    // setter for population in a tour (cities)
    void setPopulation(const vector<City *> &population);

    // helper function to shuffle cities
    const string &getGnome() {
        return gnome;
    }

    // helper to shuffle cities
    void shuffle_cities();

};


#endif //INC_3522ASN2_TOUR_HPP
