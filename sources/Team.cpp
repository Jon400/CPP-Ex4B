#include "Team.hpp"
#include "Team2.hpp"
#include "SmartTeam.hpp"
#include <limits>

ariel::Team::Team(ariel::Character* head){
    if(head->IsMemberOfTeam()){
        throw std::runtime_error("The character is already in a team");
    }
    this->leader = head;
    this->members.push_back(head);
    this->leader->setMemberOfTeam();
}
ariel::Team::~Team(){// this function free the memory allocated for each character in the team using the destructor of the character
    for (size_t i = 0; i < members.size(); i++){
        delete members[i];
    }
}
void ariel::Team::add(ariel::Character* character){
    if (this->members.size() == MAX_NUM_OF_MEMBERS){
        throw std::runtime_error("The team is full - only 10 characters are allowed in a team");
    }
    if(character->IsMemberOfTeam()){
        throw std::runtime_error("The character is already in a team");
    }
    this->members.push_back(character);
    character->setMemberOfTeam();
}
void ariel::Team::attack(Team* other){
    if (other == nullptr){
        throw std::invalid_argument("The other team is null");
    }
    if (this == other){
        throw std::runtime_error("The teams are the same");
    }
    if (this->stillAlive() == 0){
        throw std::runtime_error("The team is dead");
    }
    if (other->stillAlive() == 0){
        throw std::runtime_error("The other team is dead");
    }
    if (!this->leader->isAlive()){// check if the leader is alive, if not, choose a new leader that is closest to the dead leader
        double min = std::numeric_limits<double>::max();
        Character* newLeader = nullptr;
        Iterator* it = this->begin(other->members);
        Iterator* it_end = this->end(other->members);
        while (true){
            if ((*(*it))->isAlive()){
                double tmp = (*(*it))->distance(this->leader);
                if (tmp < min){
                    min = tmp;
                    newLeader = (*(*it));
                }
            }
            if ((*it) == (*it_end)){
                break;
            }
            ++(*it);
        }
        delete it;
        delete it_end;
        // for (size_t i = 0; i < this->members.size(); i++){
        //     if (this->members[i]->isAlive()){
        //         int tmp = this->members[i]->distance(this->leader);
        //         if (tmp < min){
        //             min = tmp;
        //             newLeader = this->members[i];
        //         }
        //     }
        // }
        if (newLeader == nullptr){
            return;
        }
        this->leader = newLeader;
    }
    // choose the victim who is closet to the leader of the attacking team
    double min = std::numeric_limits<double>::max();
    Character* victim = nullptr;
    
    // Iterator it = other->begin();
    // Iterator it_end = other->end();
    // while (it != it_end){
    //     if ((*it)->isAlive()){
    //         double tmp = this->leader->distance(*it);
    //         if (tmp < min){
    //             min = tmp;
    //             victim = *it;
    //         }
    //     }
    //     ++it;
    // }
    for (size_t i = 0; i < other->members.size(); i++){
        if (other->members[i]->isAlive()){
            double tmp = this->leader->distance(other->members[i]);
            if (tmp < min){
                min = tmp;
                victim = other->members[i];
            }
        }
    }
    // if there is no victim, stop the attack
    if (victim == nullptr){
        return;
    }
    // attack the victim
    Iterator* it = this->begin(other->members);
    Iterator* it_end = this->end(other->members);
    while (true){
        Cowboy* tmp_cowboy = nullptr;
        Ninja* tmp_ninja = nullptr;
        if ((tmp_cowboy = dynamic_cast<Cowboy*>(*(*it)))){
            if (tmp_cowboy->isAlive()){
                if (tmp_cowboy->hasboolets()){
                    tmp_cowboy->shoot(victim);
                }
                else{
                    tmp_cowboy->reload();
                }
            }
        }
        else if ((tmp_ninja = dynamic_cast<Ninja*>(*(*it)))){
            if (tmp_ninja->isAlive()){
                if (tmp_ninja->distance(victim) < 1){
                    tmp_ninja->slash(victim);
                }
                else{
                    tmp_ninja->move(victim);
                }
            }
        }
        // check if one of the teams is dead, if so, stop the attack
        if (this->stillAlive() == 0 || other->stillAlive() == 0){
            delete it;
            delete it_end;
            return;
        }       
        // check if the victim is dead, if so, choose a new victim that is closest to the leader of the attacking team
        if (!(victim->isAlive())){
            // choose the victim who is closet to the leader of the attacking team
            min = std::numeric_limits<double>::max();
            victim = nullptr;
            // Iterator it_new_victim = other->begin();
            // Iterator it_new_victim_end = other->end();
            // while (it_new_victim != it_new_victim_end){
            //     if ((*it_new_victim)->isAlive()){
            //         double tmp = this->leader->distance(*it_new_victim);
            //         if (tmp < min){
            //             min = tmp;
            //             victim = *it_new_victim;
            //         }
            //     }
            //     ++it_new_victim;
            // }
            for (size_t i = 0; i < other->members.size(); i++){
                if (other->members[i]->isAlive()){
                    double tmp = this->leader->distance(other->members[i]);
                    if (tmp < min){
                        min = tmp;
                        victim = other->members[i];
                    }
                }
            }
            // if there is no victim, stop the attack
            if (victim == nullptr){
                delete it;
                delete it_end;
                return;
            }
        }
        if ((*it) == (*it_end)){
            delete it;
            delete it_end;
            return;
        }
        ++(*it);
    }
    delete it;
    delete it_end;
}
int ariel::Team::stillAlive() const{
    int count = 0;
    for (size_t i = 0; i < members.size(); i++){
        if (members[i]->isAlive()){
            count++;
        }
    }
    return count;
}
void ariel::Team::print() const{
    std::cout << "Team Leader: " << this->leader->print() << std::endl;
    Iterator* it = this->begin(this->members);
    Iterator* it_end = this->end(this->members);
    while (true){
        std::cout << "Character: " << (*(*it))->print() << std::endl;
        if ((*it) == (*it_end)){
            break;
        }
        if ((*it) == (*it_end)){
            break;
        }
        ++(*it);   
    }
    delete it;
    delete it_end;
    // for (size_t i = 0; i < members.size(); i++){
    //     std::cout << "Character: " << members[i]->print() << std::endl;
    // }
}
ariel::Team::Iterator::Iterator(std::vector<ariel::Character*> members, size_t index){
    this->members = members;
    this->index = index;
}
ariel::Character* ariel::Team::Iterator::operator*(){
    if (this->index >= this->members.size()){
        throw std::runtime_error("Out of range");
    }
    return this->members[this->index];
}
bool ariel::Team::Iterator::operator==(Iterator other){
    return *(*this) == *other;
}
bool ariel::Team::Iterator::operator!=(Iterator other){
    return *(*this) != *other;
}
ariel::Team::Iterator& ariel::Team::Iterator::operator++(){//increment the iterator in order of that the first character is the cowboy and the last character is the ninja
    if (this->index >= this->members.size()){
        throw std::runtime_error("Out of range");
    }
    Cowboy* tmp_cowboy = nullptr;
    Ninja* tmp_ninja = nullptr;
    if (this->index + 1 > this->members.size()){
        throw std::runtime_error("Out of range");
    }
    if ((tmp_cowboy = dynamic_cast<Cowboy*>(this->members[this->index]))){
        for (size_t i = this->index + 1; i < this->members.size(); i++){
            if ((tmp_cowboy = dynamic_cast<Cowboy*>(this->members[i]))){
                this->index = i;
                return *this;
            }
        }
        for (size_t i = 0; i < this->index; i++){
            if ((tmp_ninja = dynamic_cast<Ninja*>(this->members[i]))){
                    this->index = i;
                    return *this;
            }
        }
        for (size_t i = this->index + 1; i < this->members.size(); i++){
            if ((tmp_ninja = dynamic_cast<Ninja*>(this->members[i]))){
                this->index = i;
                return *this;
            }
        }
        throw std::runtime_error("Out of range");
    }
    else{
        for (size_t i = this->index + 1; i < this->members.size(); i++){
            if ((tmp_ninja = dynamic_cast<Ninja*>(this->members[i]))){
                this->index = i;
                return *this;
            }
        }
        for (size_t i = 0; i < this->index; i++){
            if ((tmp_ninja = dynamic_cast<Ninja*>(this->members[i]))){
                this->index = i;
                return *this;
            }
        }
        throw std::runtime_error("Out of range");
    } 
    throw std::runtime_error("No alive characters");
}
size_t ariel::Team::Iterator::getIndex() const{
    return this->index;
}
void ariel::Team::Iterator::setIndex(size_t index){
    this->index = index;
}
ariel::Team::Iterator* ariel::Team::begin(std::vector<Character*> other_members) const{// begin with the first alive cowboy, if there is no alive cowboy, begin with the first alive Ninja
    Cowboy* tmp_cowboy = nullptr;
    for (size_t i = 0; i < this->members.size(); i++){
        if ((tmp_cowboy = dynamic_cast<Cowboy*>(this->members[i]))){
            return new Iterator(this->members, i);
        }
    }
    for (size_t i = 0; i < this->members.size(); i++)
    {
        return new Iterator(this->members, i);
    }
    throw std::runtime_error("No alive characters");
}
ariel::Team::Iterator* ariel::Team::end(std::vector<Character*> other_members) const{// end with the last alive ninja, if there is no alive cowboy, end with the last alive cowboy
    Ninja* tmp_ninja = nullptr;
    for (size_t i = this->members.size(); i > 0; i--){
        if ((tmp_ninja = dynamic_cast<Ninja*>(this->members[i-1]))){
            return new Iterator(this->members, i-1);
        }
    }
    for (size_t i = this->members.size(); i > 0; i--){
        return new Iterator(this->members, i-1);
    }
    throw std::runtime_error("No alive characters");
}
std::vector<ariel::Character*> ariel::Team::getMembers() const{
    return this->members;
}
ariel::Character* ariel::Team::getLeader() const{
    return this->leader;
}
ariel::Team2::Team2(ariel::Character* head): Team(head){}
ariel::Team::Iterator* ariel::Team2::begin(std::vector<Character*> other_members) const{// will return an iterator of the first character in the team in the order insertion in the vector
    return new derivedIterator(this->getMembers(), 0);
}
ariel::Team::Iterator* ariel::Team2::end(std::vector<Character*> other_members) const{
    return new derivedIterator(this->getMembers(), this->getMembers().size()-1);
}
ariel::SmartTeam::SmartTeam(ariel::Character* head): Team(head){}
ariel::Team::Iterator* ariel::SmartTeam::begin(std::vector<Character*> other_members) const{// start with the person who his distance cost from the other team is the lowest
    std::vector<Point> other_points;
    for (size_t i = 0; i < other_members.size(); i++)
    {
        other_points.push_back(other_members[i]->getLocation());
    }

    double min = std::numeric_limits<double>::max();
    size_t index = 0;
    for (size_t i = 0; i < this->getMembers().size(); i++)
    {
        double tmp = 0;
        for (size_t j = 0; j < other_points.size(); j++)
        {
            if (other_members[j]->isAlive()){
                tmp += this->getMembers()[i]->getLocation().distance(other_points[j]);
            }
        }
        if (tmp < min){
            min = tmp;
            index= i;
        }
    }
    return new smartIterator(this->getMembers(), other_points, index);
}
ariel::Team::Iterator* ariel::SmartTeam::end(std::vector<Character*> other_members) const{
    std::vector<Point> other_points;
    for (size_t i = 0; i < other_members.size(); i++){
        other_points.push_back(other_members[i]->getLocation());
    }
    double max = std::numeric_limits<double>::min();
    size_t index = 0;
    for (size_t i = 0; i < this->getMembers().size(); i++)
    {
        double tmp = 0;
        for (size_t j = 0; j < other_points.size(); j++){
            if (other_members[j]->isAlive()){
                tmp += this->getMembers()[i]->getLocation().distance(other_points[j]);
            }
        }
        if (tmp > max){
            max = tmp;
            index= i;
        }
    }
    return new smartIterator(this->getMembers(), other_points, index);
}
ariel::Team2::derivedIterator::derivedIterator(std::vector<ariel::Character*> members, size_t index): Iterator(members, index){}
ariel::Team::Iterator& ariel::Team2::derivedIterator::operator++(){
    this->setIndex(this->getIndex()+1);
    return *this;
}
ariel::SmartTeam::smartIterator::smartIterator(std::vector<ariel::Character*> members, std::vector<Point> other_points,
    size_t index): Iterator(members, index){
        this->other_members_points = other_points;
}
ariel::Team::Iterator& ariel::SmartTeam::smartIterator::operator++(){
    // calculate the cost distance of the current character
    double sum = 0;
    for (size_t i = 0; i < this->other_members_points.size(); i++)
    {
        sum += this->getMembers()[this->getIndex()]->getLocation().distance(this->other_members_points[i]);
    }
    double min = std::numeric_limits<double>::max();
    for (size_t i = 0; i < this->getMembers().size(); i++)
    {
        double tmp = 0;
        for (size_t j = 0; j < this->other_members_points.size(); j++){
            tmp += this->getMembers()[i]->getLocation().distance(this->other_members_points[j]);
        }
        if (tmp < min && tmp > sum){
            min = tmp;
            this->setIndex(i);
        }
    }
    return *this;
}
std::vector<ariel::Character*> ariel::Team::Iterator::getMembers() const{
    return this->members;
}