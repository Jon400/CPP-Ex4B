#pragma once
#include "Character.hpp"
#include <vector>

namespace ariel{
    const int MAX_NUM_OF_MEMBERS = 10;
    class Team{
        protected:
            std::vector<ariel::Character*> members; // represents the members of the team
            Character* leader; // represents the leader character of the team
        public:
            class Iterator{
                private:
                    std::vector<ariel::Character*> members;
                public:
                    Iterator(std::vector<ariel::Character*>); // constructor
                    virtual Iterator& operator++(); // prefix increment operator
                    ariel::Character* operator*(); // access operator
                    bool operator==(const Iterator*) const; // equal operator
                    bool operator!=(const Iterator*) const; // not equal operator
            };
            Team(ariel::Character*); // constructor, receves a pointer to the head character of the team
            ~Team(); // destructor - releases the memory allocated for the team
            void add(ariel::Character*); // add a character to the team
            void attack(Team*) const; // receive a pointer to other team and attack the other team
            int stillAlive() const; // returns the number of alive characters in the team
            void print() const; // prints the characters in the team
            virtual Iterator begin() const; // returns an iterator to the first character in the team
    };

    class Team2: public Team{
        public:
            class derivedIterator: public Team::Iterator{
                public:
                    derivedIterator(std::vector<ariel::Character*>); // constructor
                    Iterator& operator++() override; // prefix increment operator
            };
            Team2(ariel::Character*); // constructor, receves a pointer to the head character of the team
            Iterator begin() const override; // returns an iterator to the first character in the team
    };
    
    class SmartTeam: public Team{
        public:
            class smartIterator: public Team::Iterator{
                public:
                    smartIterator(std::vector<ariel::Character*>); // constructor
                    Iterator& operator++() override; // prefix increment operator
            };
            SmartTeam(ariel::Character*); // constructor, receves a pointer to the head character of the team
            Iterator begin() const override; // returns an iterator to the first character in the team
    };
}
