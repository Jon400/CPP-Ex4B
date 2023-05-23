#include "Character.hpp"
#include "Ninja.hpp"
#include "TrainedNinja.hpp"
#include "YoungNinja.hpp"
#include "OldNinja.hpp"
#include "Cowboy.hpp"

ariel::Character::Character(const std::string& name, const ariel::Point& position, int healthPoints):
    name{name}, position{position}, healthPoints{healthPoints} { 
        this->isMemberOfTeam = false;
}
bool ariel::Character::isAlive() const{
    return this->healthPoints > 0;
}
double ariel::Character::distance(const Character* other) const{
    return this->getLocation().distance(other->getLocation());
}
void ariel::Character::hit(int damage){
    // damage can't be negative
    if (damage < 0){
        throw std::invalid_argument("damage cannot be negative");
    }
    this->healthPoints -= damage;
    if (this->healthPoints < 0)  //The health points can't be negative
    {
        this->healthPoints = 0;
    }
    return;
}
std::string ariel::Character::getName() const{
    return this->name;
}
ariel::Point ariel::Character::getLocation() const{
    return this->position;
}
ariel::Ninja::Ninja(const std::string& name, const ariel::Point& position, int healthPoints, int velocity) : Character(name, position, healthPoints){
    this->setVelocity(velocity);
}
void ariel::Ninja::move(const Character * other){
    this->setPosition(Point::moveTowards(this->getLocation(), other->getLocation(), this->getVelocity()));
}
void ariel::Ninja::slash(Character * other){
    // no self harm checking
    if (this == other){
        throw std::runtime_error("Ninja cannot slash himself");
    }
    if (!this->isAlive() || !other->isAlive()){
        throw std::runtime_error("characters cannot attack a dead enemy");
    }
    if (this->getLocation().distance(other->getLocation()) < 1)
    {
        other->hit(40);
    }
    return;
}
std::string ariel::Ninja::print() const{
    return "N" + this->getName() + " " + this->getLocation().print() + " " + (this->isAlive()? std::to_string(this->getHealthPoints()) : "") + "\n";
}
void ariel::Ninja::setVelocity(int velocity){
    this->velocity = velocity;
}
int ariel::Ninja::getVelocity() const{
    return this->velocity;
}
ariel::YoungNinja::YoungNinja(const std::string& name, const ariel::Point& position) : Ninja(name, position, 100, 14){
}
ariel::TrainedNinja::TrainedNinja(const std::string& name, const ariel::Point& position) : Ninja(name, position, 120, 12){
}
ariel::OldNinja::OldNinja(const std::string& name, const ariel::Point& position) : Ninja(name, position, 150, 8){
}
ariel::Cowboy::Cowboy(const std::string& name, const ariel::Point& position) : Character(name, position, 110){
    this->numOfBullets = 6;
}
void ariel::Cowboy::shoot(Character * other){
    // no self harm checking
    if (this == other){
        throw std::runtime_error("Cowboy cannot shoot himself");
    }
    if (!this->isAlive() || !other->isAlive()){
        throw std::runtime_error("characters cannot attack a dead enemy, dead cowboys cannot shoot");
    }
    if (this->hasboolets())
    {
        other->hit(10);
        this->numOfBullets--;
    }
    return;
}
void ariel::Cowboy::reload(){
    if (!this->isAlive()){
        throw std::runtime_error("dead cowboys cannot reload");
    }
    this->numOfBullets = 6;
    return;
}
bool ariel::Cowboy::hasboolets() const{
    return this->numOfBullets > 0;
}
std::string ariel::Cowboy::print() const{
    return "C" + this->getName() + " " + this->getLocation().print() + " " 
    + (this->isAlive()? std::to_string(this->getHealthPoints()) : "") + "\n";
}
int ariel::Character::getHealthPoints() const{
    return this->healthPoints;
}
std::string ariel::Character::getcharacterName() const{
    return std::string();
}
bool ariel::Character::IsMemberOfTeam() const{
    return this->isMemberOfTeam;
}
void ariel::Character::setMemberOfTeam(){
    this->isMemberOfTeam = true;
}
// for tidy reasons
void ariel::Character::setPosition(const Point& position){
    this->position = position;
}
void ariel::Character::setHealthPoints(int healthPoints){
    this->healthPoints = healthPoints;
}