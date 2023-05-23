#pragma once
#include "Character.hpp"

namespace ariel{
    class Ninja: public Character{
        private:
            int velocity; // represents the velocity of the ninja
        protected:
            void setVelocity(int); // set the velocity of the ninja
            int getVelocity() const; // returns the velocity of the ninja
        public:
            Ninja(const std::string&, const ariel::Point&, int, int); // constructor
            void move(const Character*); // cause the ninja to move towards the other character
            void slash(Character*); // receive a pointer to other character and slash the other character
            std::string print() const override; // prints the ninja, override the print function of the Character class
    }; 
}