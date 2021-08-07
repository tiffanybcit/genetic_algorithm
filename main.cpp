//
// Created by Tiffany Gu on 2020-11-23.
// This is the driver class for the genetic algorithm for TSP problem.
//
#include <bits/stdc++.h>
#include "City.hpp"
#include "Tour.hpp"

using namespace std;

// Number of cities in TSP
#define V 20

// Initial population size
#define INIT_POP_SIZE 30

// Mutation rate in mutation function
#define MUTATION_RATE 0.20

// Whether iterations should stop
#define IMPROVEMENT_FACTOR 0.80

// Map of the cities
#define MAP_BOUNDARY 1000

// Max number of iterations
#define MAX_ITERATIONS 1000

// Take 2 groups of parents to breed
#define PARENT_POOL_SIZE 5

// some variables
vector<City> masterList;
vector<Tour> population;
float minimum_init;
float best_distance;
float position_after_init;
float base_distance;
string base_route;
string best_route;

// Function to return a random number from start and end
int rand_num(int start, int end) {
    int r = end - start;
    int rnum = start + rand() % r;
    return rnum;
}

// To check if the city address is repeated
bool no_repeat(int x, int y) {
    for (int j = 0; j < masterList.size(); ++j) {
        if (x == masterList[j].getX() && y == masterList[j].getY()) {
            return false;
        }
    }
    return true;
}

//Create masterlist
void create_master_list(vector<City> *masterList) {

    char c = 'A';

    for (int i = 0; i < V; i++) {
        while (true) {
            int tempx = rand_num(1, MAP_BOUNDARY);
            int tempy = rand_num(1, MAP_BOUNDARY);
            if (no_repeat(tempx, tempy)) {
                char name;
                name = c + i;
                masterList->emplace_back(name, tempx, tempy);
                break;
            }
        }
    }
}

// Comparator to compare fitness.
bool less_than(Tour t1,
              Tour t2) {
    return t1.getFitness() > t2.getFitness();
}

// Breed function
void crossover() {
    vector<Tour> pool1 = {};
    vector<Tour> pool2 = {};
    Tour temp1 = Tour(&masterList, V);
    temp1.setPopulation({});

    for (int i = 0; i < PARENT_POOL_SIZE; i++) {
        while (true) {
            int temp1 = rand_num(1, population.size());
            int temp2 = rand_num(1, population.size());
            if (temp1 != temp2 && !population[temp1].getEliteFlag() && !population[temp2].getEliteFlag()) {
                pool1.push_back(population[temp1]);
                pool2.push_back(population[temp2]);
                break;
            }
        }
        sort(pool1.begin(), pool1.end(), less_than);
        sort(pool2.begin(), pool2.end(), less_than);
    }
    int index1 = rand_num(1, V);
    int j;
    for (j = 0; j < index1; j++) {
        temp1.population.push_back(pool1[0].population[j]);
    }
    int flag = j;
    bool flag2 = true;
    int counter = 0;
    while (counter < (pool2[0].population.size())) {

        for (int k = 0; k < index1; k++) {
            if (temp1.population[k]->getName() == pool2[0].population[counter]->getName()) {
                flag2 = false;
                break;
            }
        }
        if (flag2 && flag < V) {
            temp1.population.push_back(pool2[0].population[counter]);
            flag++;
        }
        flag2 = true;
        counter++;
    }
    population.push_back(temp1);
}

// Helper function to get a random percentage
float get_random_percentage() {
    float result;
    result = rand_num(20, 30);
    result = result / 100;
    return result;
}

// Mini report for each iteration
void print_mini_report(int count_of_iterations, int flag_termination) {
    cout << "Iteration #: " << count_of_iterations + 1 << endl;
    cout << fixed << setprecision(3) << "Distance for that iteration: " << best_distance << endl;
    cout << fixed << setprecision(3) << "Best distance so far: " << best_distance << endl;
    cout << fixed << setprecision(3) << "Best fitness so far: " << CONSTANT_OF_FITNESS / best_distance << endl;
    if (flag_termination == 1) {
        cout << "Whether improvement factor was achieved: " << "Yes" << endl;
    } else {
        cout << "Whether improvement factor was achieved: " << "No" << endl;
    }
    cout << fixed << setprecision(3) << "Improvement over base so far: " << base_distance - best_distance << endl;

    cout << "Output of the best route: " << best_route << endl;
    cout << "\n";
}

// Selection
void selection() {
    minimum_init = population[0].getTotalDistance();
    position_after_init = 0;
    best_route = "";

    // Selection occurs
    for (int i = 0; i < INIT_POP_SIZE; i++) {
        if (population[i].getTotalDistance() < minimum_init) {
            minimum_init = population[i].getTotalDistance();
            position_after_init = i;

        }
    }
    population[position_after_init].setEliteFlag(true);
}

// Crossover and breeding
void breed() {
    int counter = 0;
    while (counter < INIT_POP_SIZE - 1) {
        crossover();
        counter++;
    }

    int buf = 0;

    int counter_of_erase = 0;
    while (counter_of_erase < INIT_POP_SIZE - 1) {
        if (!population[buf].getEliteFlag()) {
            population.erase(population.begin() + buf);
            counter_of_erase++;
        } else {
            buf++;
        }
    }
    cout << endl;
}

// Mutation
void mutation() {
    int random_percentage = get_random_percentage() * INIT_POP_SIZE;

    int mutate_counter = 0;
    while (mutate_counter < random_percentage) {
        while (true) {
            int temp1 = rand_num(1, V);
            if (!population[temp1].getSelectedFlag() && !population[temp1].getEliteFlag()) {
                population[temp1].mutate(MUTATION_RATE);
                population[temp1].setSelectedFlag(true);
                mutate_counter++;
                break;
            }
        }
    }
}

// Print out final report
void print_final_report(int count_of_iterations, int flag_termination) {
    cout << "Final Report" << endl;
    cout << "Number of iterations: " << count_of_iterations << endl;
    cout << fixed << setprecision(3) << "Report of the base distance: " << base_distance << endl;
    cout << fixed << setprecision(3) << "Report of the best distance: " << best_distance << endl;
    cout << fixed << setprecision(3) << "Report of best fitness: " << CONSTANT_OF_FITNESS / best_distance << endl;
    if (flag_termination == 1) {
        cout << "Whether your improvement factor was achieved: " << "Yes" << endl;
    } else {
        cout << "Whether your improvement factor was achieved: " << "No" << endl;
    }
    cout << "Output of the base route: " << base_route << endl;
    cout << "Output of the best route: " << best_route << endl;
    cout << "\n";
}

// Re-set elite flag to false
void clear_flags() {
    for (int i = 0; i < population.size(); i++) {
        population[i].setEliteFlag(false);
        population[i].setSelectedFlag(false);
    }
}

// Get the best best distance and route
void best_combination() {
    best_distance = population[0].getTotalDistance();
    best_route = population[0].getGnome();

    for (int i = 0; i < INIT_POP_SIZE; i++) {
        if (population[i].getTotalDistance() < best_distance) {
            best_distance = population[i].getTotalDistance();
            best_route = population[i].getGnome();
        }
    }
}

// Print out the initial state
void print_initial_state() {
    cout << "\nTotalDistance    GNOME       FITNESS VALUE\n";
    for (int i = 0; i < INIT_POP_SIZE; i++)
        cout << fixed << setprecision(3) << population[i].getTotalDistance() << "       "
             << population[i].getGnome() << "       "
             << population[i].getFitness() << "     "
             << endl;

    cout << "\n";
    cout << "\n";
}

// Calculate base distance and route
void get_base_combination() {
    base_distance = population[0].getTotalDistance();

    for (int i = 0; i < INIT_POP_SIZE; i++) {
        if (population[i].getTotalDistance() < base_distance) {
            base_distance = population[i].getTotalDistance();
            base_route = population[i].getGnome();
        }
    }
}

// Utility function for TSP problem.
void TSPUtil() {

    int flag_termination = 0;

// Calculate base distance and route
    get_base_combination();

    // Print out the initial state
    print_initial_state();

    // Iterations begin here
    cout << "Iteration beginning..." << endl;

    int count_of_iterations = 0;
    while (count_of_iterations < MAX_ITERATIONS) {
        // Selection
        selection();

        // Crossover and breeding
        breed();

        // Mutation
        mutation();

        // Determine the best route and distance so far
        best_combination();

        // Re-set elite flag to false
        clear_flags();

        // If best distance has achieved the improvement factor
        if ((best_distance / base_distance) < IMPROVEMENT_FACTOR) {
            flag_termination = 1;
        }

        // Mini report for this iteration
        print_mini_report(count_of_iterations, flag_termination);

        // Increment the iterations
        count_of_iterations++;
        if(flag_termination == 1){
            break;
        }
    }
    // Print final report
    print_final_report(count_of_iterations, flag_termination);
}

// Driver method
int main() {
    create_master_list(&masterList);

    for (int i = 0; i < INIT_POP_SIZE; i++) {
        Tour to = Tour(&masterList, V);
        population.push_back(to);
    }

    TSPUtil();
}

