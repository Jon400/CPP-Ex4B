#pragma once
#include "Team.hpp"

namespace ariel
{
    class Team2: public Team{
        public:
            class derivedIterator: public Team::Iterator{
                public:
                    derivedIterator(std::vector<ariel::Character*>, size_t); // constructor
                    Iterator& operator++() override; // prefix increment operator
            };
            Team2(ariel::Character*); // constructor, receves a pointer to the head character of the team
            Iterator* begin() const override; // returns an iterator to the first character in the team
            Iterator* end() const override; // returns an iterator to the last character in the team
    };
}