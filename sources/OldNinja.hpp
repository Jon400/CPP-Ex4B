#pragma once
#include "Ninja.hpp"

namespace ariel
{
    class OldNinja: public Ninja{
        public:
            OldNinja(const std::string&, const ariel::Point&); // constructor
    };
}