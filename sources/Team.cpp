#include "Team.hpp"
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
        Iterator it = this->begin();
        Iterator it_end = this->end();
        while (it != it_end){
            if ((*it)->isAlive()){
                double tmp = (*it)->distance(this->leader);
                if (tmp < min){
                    min = tmp;
                    newLeader = *it;
                }
            }
            ++it;
        }
        
        // for (size_t i = 0; i < this->members.size(); i++){
        //     if (this->members[i]->isAlive()){
        //         int tmp = this->members[i]->distance(this->leader);
        //         if (tmp < min){
        //             min = tmp;
        //             newLeader = this->members[i];
        //         }
        //     }
        // }
        this->leader = newLeader;
    }
    // choose the victim who is closet to the leader of the attacking team
    double min = std::numeric_limits<double>::max();
    Character* victim = nullptr;
    
    Iterator it = other->begin();
    Iterator it_end = other->end();
    while (it != it_end){
        if ((*it)->isAlive()){
            double tmp = this->leader->distance(*it);
            if (tmp < min){
                min = tmp;
                victim = *it;
            }
        }
        ++it;
    }
    // for (size_t i = 0; i < other->members.size(); i++){
    //     if (other->members[i]->isAlive()){
    //         int tmp = this->leader->distance(other->members[i]);
    //         if (tmp < min){
    //             min = tmp;
    //             victim = other->members[i];
    //         }
    //     }
    // }
    // if there is no victim, stop the attack
    if (victim == nullptr){
        return;
    }
    // attack the victim
    it = this->begin();
    it_end = this->end();
    while (it != it_end){
        Cowboy* tmp_cowboy = nullptr;
        Ninja* tmp_ninja = nullptr;
        if ((tmp_cowboy = dynamic_cast<Cowboy*>(*it))){
            if (tmp_cowboy->isAlive()){
                if (tmp_cowboy->hasboolets()){
                    tmp_cowboy->shoot(victim);
                }
                else{
                    tmp_cowboy->reload();
                }
            }
        }
        else if ((tmp_ninja = dynamic_cast<Ninja*>(*it))){
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
            break;
        }       
        // check if the victim is dead, if so, choose a new victim that is closest to the leader of the attacking team
        if (!victim->isAlive()){
            // choose the victim who is closet to the leader of the attacking team
            min = std::numeric_limits<double>::max();
            victim = nullptr;
            it = other->begin();
            it_end = other->end();
            while (it != it_end){
                if ((*it)->isAlive()){
                    double tmp = this->leader->distance(*it);
                    if (tmp < min){
                        min = tmp;
                        victim = *it;
                    }
                }
                ++it;
            }
            // for (size_t i = 0; i < other->members.size(); i++){
            //     if (other->members[i]->isAlive()){
            //         int tmp = this->leader->distance(other->members[i]);
            //         if (tmp < min){
            //             min = tmp;
            //             victim = other->members[i];
            //         }
            //     }
            // }
        }
        ++it;
    }
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
    for (size_t i = 0; i < members.size(); i++){
        std::cout << "Character: " << members[i]->print() << std::endl;
    }
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
ariel::Team::Iterator ariel::Team::begin() const{// begin with the first alive cowboy, if there is no alive cowboy, begin with the first alive Ninja
    Cowboy* tmp_cowboy = nullptr;
    for (size_t i = 0; i < this->members.size(); i++){
        if ((tmp_cowboy = dynamic_cast<Cowboy*>(this->members[i]))){
            return Iterator(this->members, i);
        }
    }
    for (size_t i = 0; i < this->members.size(); i++)
    {
        return Iterator(this->members, i);
    }
    throw std::runtime_error("No alive characters");
}
ariel::Team::Iterator ariel::Team::end() const{// end with the last alive ninja, if there is no alive cowboy, end with the last alive cowboy
    Ninja* tmp_ninja = nullptr;
    for (size_t i = this->members.size(); i > 0; i--){
        if ((tmp_ninja = dynamic_cast<Ninja*>(this->members[i-1]))){
            return Iterator(this->members, i-1);
        }
    }
    for (size_t i = this->members.size(); i > 0; i--){
        return Iterator(this->members, i-1);
    }
    throw std::runtime_error("No alive characters");
}
ariel::Team2::Team2(ariel::Character* head): Team(head){}
ariel::Team::Iterator ariel::Team2::begin() const{return Iterator(std::vector<ariel::Character*>(), 0);}
ariel::Team::Iterator ariel::Team2::end() const{return Iterator(std::vector<ariel::Character*>(), 0);}
ariel::SmartTeam::SmartTeam(ariel::Character* head): Team(head){}
ariel::Team::Iterator ariel::SmartTeam::begin() const{return Iterator(std::vector<ariel::Character*>(), 0);}
ariel::Team::Iterator ariel::SmartTeam::end() const{return Iterator(std::vector<ariel::Character*>(), 0);}
ariel::Team2::derivedIterator::derivedIterator(std::vector<ariel::Character*> members, size_t index): Iterator(members, index){}
ariel::Team::Iterator& ariel::Team2::derivedIterator::operator++(){return *this;}
ariel::SmartTeam::smartIterator::smartIterator(std::vector<ariel::Character*> members, size_t index): Iterator(members, index){}
ariel::Team::Iterator& ariel::SmartTeam::smartIterator::operator++(){return *this;}