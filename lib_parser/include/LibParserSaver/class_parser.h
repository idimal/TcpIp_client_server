#pragma once

#include "pugixml.hpp"
#include "../src/structs.cpp"

class Parser {
    public:
        State parseState(const pugi::xml_document& doc);
        PlmlData parseData(const pugi::xml_document& doc);
};
