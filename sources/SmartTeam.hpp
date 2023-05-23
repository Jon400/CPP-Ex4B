#pragma once
#include "Team.hpp"

namespace ariel
{
    class SmartTeam: public Team{
        public:
            class smartIterator: public Team::Iterator{
                private:
                    std::vector<Point> other_members_points;
                public:
                    smartIterator(std::vector<ariel::Character*>, std::vector<Point> other_members_points, size_t); // constructor
                    Iterator& operator++() override; // prefix increment operator
            };
            SmartTeam(ariel::Character*); // constructor, receves a pointer to the head character of the team
            Iterator* begin(std::vector<Character*>) const override; // returns an iterator to the first character in the team
            Iterator* end(std::vector<Character*>) const override; // returns an iterator to the last character in the team
    };
}