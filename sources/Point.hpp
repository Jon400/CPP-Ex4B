#pragma once
#include <iostream>

namespace ariel{
    class Point{
        private:
            double x; // represents the x coordinate
            double y; // represents the y coordinate
        public:
            Point(double, double); // constructor that receives x and y coordinates
            Point(const Point&); // copy constructor
            Point& operator=(const Point&); // assignment operator
            ~Point(); // destructor
            double distance(const Point&) const; // returns the euclidean distance between two points
            double getX() const; // returns the x coordinate
            double getY() const; // returns the y coordinate
            std::string print() const; // prints the point with the format (x,y)
            static Point moveTowards(const Point&, const Point&, double); // returns the point that is closer to the destination point by the given distance from the source point  
    };  
}