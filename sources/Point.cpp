#include "Point.hpp"
#include <cmath>
#include <string>

ariel::Point::Point(double x, double y){
    this->x = x;
    this->y = y;
}
ariel::Point::Point(const ariel::Point& other){
    this->x = other.x;
    this->y = other.y;
}
ariel::Point& ariel::Point::operator=(const Point& other){
    this->~Point();
    this->x = other.x;
    this->y = other.y;
    return *this;
}
ariel::Point::~Point(){
}
// compute the euclidean distance between two points
double ariel::Point::distance(const Point& other) const{
    return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
}
double ariel::Point::getX() const{
    return this->x;
}
double ariel::Point::getY() const{
    return this->y;
}
// return the point with the format (x,y)
std::string ariel::Point::print() const{
    return "(" + std::to_string(this->x) + "," + std::to_string(this->y) + ")";
}
ariel::Point ariel::Point::moveTowards(const ariel::Point& source, const ariel::Point& destination, double distance){
    if (distance < 0){
        throw std::invalid_argument("distance can't be negative");
    }
    double d = source.distance(destination);
    double x,y;
    if (d <= distance){
        x = destination.getX();
        y = destination.getY();
    }
    else{
        x = source.getX() + (distance * (destination.getX() - source.getX()) / d);
        y = source.getY() + (distance * (destination.getY() - source.getY()) / d);
    }
    ariel::Point p = ariel::Point(x,y);
    return p;
}