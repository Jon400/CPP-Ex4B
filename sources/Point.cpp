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
ariel::Point ariel::moveTowards(const ariel::Point& source, const ariel::Point& destination, double distance){
    double d = source.distance(destination);
    ariel::Point p = ariel::Point(0,0);
    if (d <= distance){
        p.x = destination.getX();
        p.y = destination.getY();
        return p;
    }
    double x = source.getX() + (distance * (destination.getX() - source.getX()) / d);
    double y = source.getY() + (distance * (destination.getY() - source.getY()) / d);
    p.x = x;
    p.y = y;
    return p;
}