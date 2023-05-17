#include "Team.hpp"

ariel::Team::Team(ariel::Character* head){}
ariel::Team::~Team(){}
void ariel::Team::add(ariel::Character* character){}
void ariel::Team::attack(Team* other) const{}
int ariel::Team::stillAlive() const{return 0;}
void ariel::Team::print() const{}
ariel::Team::Iterator::Iterator(std::vector<ariel::Character*> members){}
ariel::Character* ariel::Team::Iterator::operator*(){return nullptr;}
bool ariel::Team::Iterator::operator==(const Iterator* other) const{return false;}
bool ariel::Team::Iterator::operator!=(const Iterator* other) const{return false;}
ariel::Team::Iterator& ariel::Team::Iterator::operator++(){return *this;}
ariel::Team::Iterator ariel::Team::begin() const{return Iterator(std::vector<ariel::Character*>());}
ariel::Team2::Team2(ariel::Character* head): Team(head){}
ariel::Team::Iterator ariel::Team2::begin() const{return Iterator(std::vector<ariel::Character*>());}
ariel::SmartTeam::SmartTeam(ariel::Character* head): Team(head){}
ariel::Team::Iterator ariel::SmartTeam::begin() const{return Iterator(std::vector<ariel::Character*>());}

