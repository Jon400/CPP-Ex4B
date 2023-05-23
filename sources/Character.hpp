#pragma once
#include "Point.hpp"
#include <string>

namespace ariel{
    class Character{
        private:
            ariel::Point position; // represents the position of the character
            int healthPoints; // represents the health points of the character
            std::string name; // represents the name of the character
            bool isMemberOfTeam; // represents if the character is a member of a team
        protected:
            void setPosition(const ariel::Point&); // set the position of the character
            void setHealthPoints(int); // set the health points of the character
        public:
            Character(const std::string&, const ariel::Point&, int); // constructor
            virtual ~Character() = default; // destructor
            bool isAlive() const; // returns true if the character is alive, false otherwise
            double distance(const Character*) const; // receive a pointer to other character and return the distance between them
            void hit(int damage); // receive the damage and subtract it from the health points
            std::string getName() const; // returns the name of the character
            ariel::Point getLocation() const; // returns the position of the character
            virtual std::string print() const = 0; // prints the character
            int getHealthPoints() const; // returns the health points of the character for testing purposes
            std::string getcharacterName() const; // returns the name of the character for testing purposes
            bool IsMemberOfTeam() const; // returns True if the character is a member of a team, False otherwise
            void setMemberOfTeam(); // set the isMemberOfTeam field to the given value



            // for tidy
            Character(const Character&) = default; // copy constructor
            Character& operator=(const Character&) = default; // assignment operator
            Character(Character&&) = default; // move constructor
            Character& operator=(Character&&) = default; // move assignment operator
    };
}