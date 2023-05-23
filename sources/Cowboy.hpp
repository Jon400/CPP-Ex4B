#pragma once
#include "Character.hpp"

namespace ariel
{
    class Cowboy: public Character // This class extends Character
    {
        private:
            int numOfBullets; // represents the number of bullets the cowboy has
        public:
            Cowboy(const std::string&, const ariel::Point&); // constructor
            void shoot(Character*); // receive a pointer to other character and subtract 1 bullet from the cowboy and hit the other character
            bool hasboolets() const; // return True if the cowboy has bullets, False otherwise
            void reload(); // add 6 bullets to the cowboy
            std::string print() const override; // prints the cowboy, override the print function of the Character class
    };
}
