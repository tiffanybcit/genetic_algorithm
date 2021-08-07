//
// Created by Tiffany Gu on 2020-11-23.
// This is the city class header file.
//

#ifndef INC_3522ASN2_CITY_HPP
#define INC_3522ASN2_CITY_HPP

#include <string>
#include <climits>

class City {
private:
    int x;
    int y;
    char name;
public:

    // constructor
    City(char char1, int x1, int y1);

    // getters and setters for variables
    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    char getName() const;

    void setName(char name);
};


#endif //INC_3522ASN2_CITY_HPP
