#pragma once
#include "Character.hpp"
#include "Cowboy.hpp"
#include "Ninja.hpp"
#include "TrainedNinja.hpp"
#include "YoungNinja.hpp"
#include "OldNinja.hpp"
#include <vector>

namespace ariel{
    const int MAX_NUM_OF_MEMBERS = 10;
    class Team{
        private:
            std::vector<ariel::Character*> members; // represents the members of the team
            Character* leader; // represents the leader character of the team
        protected:
            std::vector<ariel::Character*> getMembers() const; // returns the members of the team
            Character* getLeader() const; // returns the leader character of the team
        public:
            class Iterator{
                private:
                    std::vector<ariel::Character*> members;
                    size_t index;
                protected:
                    size_t getIndex() const; // returns the index of the iterator
                    void setIndex(size_t); // set the index of the iterator
                    std::vector<ariel::Character*> getMembers() const; // returns the members of the team
                public:
                    Iterator(std::vector<ariel::Character*>, size_t); // constructor
                    virtual Iterator& operator++(); // prefix increment operator
                    ariel::Character* operator*(); // access operator
                    bool operator==(Iterator); // equal operator
                    bool operator!=(Iterator); // not equal operator
                    // for tidy
                    virtual ~Iterator() = default; // destructor
                    Iterator(const Iterator&) = default; // copy constructor
                    Iterator& operator=(const Iterator&) = default; // assignment operator
                    Iterator(Iterator&&) = default; // move constructor
                    Iterator& operator=(Iterator&&) = default; // move assignment operator
            };
            Team(ariel::Character*); // constructor, receves a pointer to the head character of the team
            virtual ~Team(); // destructor - releases the memory allocated for the team
            void add(ariel::Character*); // add a character to the team
            void attack(Team*); // receive a pointer to other team and attack the other team
            int stillAlive() const; // returns the number of alive characters in the team
            void print() const; // prints the characters in the team
            virtual Iterator* begin(std::vector<Character*>) const; // returns an iterator to the first character in the team
            virtual Iterator* end(std::vector<Character*>) const; // returns an iterator to the last character in the team
            // for tidy
            Team(const Team&) = delete; // copy constructor
            Team& operator=(const Team&) = delete; // assignment operator
            Team(Team&&) = delete; // move constructor
            Team& operator=(Team&&) = delete; // move assignment operator
    };
}