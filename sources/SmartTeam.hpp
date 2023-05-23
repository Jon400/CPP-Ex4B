#pragma once
#include "Team.hpp"

namespace ariel
{
    class SmartTeam: public Team{
        public:
            class smartIterator: public Team::Iterator{
                private:
                    std::vector<ariel::Character*> other_members;
                public:
                    smartIterator(std::vector<ariel::Character*>, std::vector<ariel::Character*>, size_t); // constructor
                    Iterator& operator++() override; // prefix increment operator
            };
            SmartTeam(ariel::Character*); // constructor, receves a pointer to the head character of the team
            Iterator* begin() const override; // returns an iterator to the first character in the team
            Iterator* end() const override; // returns an iterator to the last character in the team
    };
}