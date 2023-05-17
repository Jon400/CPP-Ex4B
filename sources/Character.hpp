#pragma once
#include "Point.hpp"
#include <string>

namespace ariel{
    class Character{
        protected:
            ariel::Point position; // represents the position of the character
            int healthPoints; // represents the health points of the character
            std::string name; // represents the name of the character
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

            // for tidy
            Character(const Character&) = default; // copy constructor
            Character& operator=(const Character&) = default; // assignment operator
            Character(Character&&) = default; // move constructor
            Character& operator=(Character&&) = default; // move assignment operator
    };

     class Ninja: public Character{
        protected:
            int velocity; // represents the velocity of the ninja
        public:
            Ninja(const std::string&, const ariel::Point&, int, int); // constructor
            void move(const Character*); // cause the ninja to move towards the other character
            void slash(Character*); // receive a pointer to other character and slash the other character
            std::string print() const override; // prints the ninja, override the print function of the Character class
    }; 

    class YoungNinja: public Ninja{
        public:
            YoungNinja(const std::string&, const ariel::Point&); // constructor
    };

    class TrainedNinja: public Ninja{
        public:
            TrainedNinja(const std::string&, const ariel::Point&); // constructor
    };

    class OldNinja: public Ninja{
        public:
            OldNinja(const std::string&, const ariel::Point&); // constructor
    };

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