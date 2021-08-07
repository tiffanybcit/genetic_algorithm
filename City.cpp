//
// Created by Tiffany Gu on 2020-11-23.
// This is the city class.
//
#include "City.hpp"

// constructor
City::City(char char1, int x1, int y1) {
    name = char1;
    x = x1;
    y = y1;

}

// getter for coordinate x
int City::getX() const {
    return x;
}

// setter for coordinate x
void City::setX(int x) {
    City::x = x;
}

// getter for coordinate y
int City::getY() const {
    return y;
}

// setter for coordinate y
void City::setY(int y) {
    City::y = y;
}

// getter for city name
char City::getName() const {
    return name;
}

// setter for city name
void City::setName(char name) {
    City::name = name;
}

