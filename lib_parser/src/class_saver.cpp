#include "../include/LibParserSaver/class_saver.h"
#include "../include/LibParserSaver/class_parser.h"
#include <iostream>
#include <string>
#include <vector>
#include "pugixml.hpp"


void Saver::saveState(const char* file_name) {
    Parser parser;
    pugi::xml_document doc;

    // Загружаем XML-документ
    if (!doc.load_file(file_name)) {
        std::cerr << "Could not load XML file!" << std::endl;
    }

    // Парсим XML и получаем данные
    State data = parser.parseState(doc);

    // Выводим результат
    std::cout << "Version: " << data.version << std::endl;
    std::cout << "TypeState: " << data.typeState << std::endl;
}

void Saver::saveData(const char* file_name) {
    Parser parser;
    pugi::xml_document doc;

    // Загружаем XML-документ
    if (!doc.load_file(file_name)) {
        std::cerr << "Could not load XML file!" << std::endl;
    }

    // Парсим XML в структуру
    PlmlData plml = parser.parseData(doc);

    // Выводим результат
    std::cout << "PLML Version: " << plml.version << std::endl;
    for (const auto& state : plml.states) {
        std::cout << "State Name: " << state.name << std::endl;
        std::cout << "State Code: " << state.state << std::endl;
        std::cout << "State String: " << state.state_string << std::endl;
        std::cout << "State Type: " << state.state_type << std::endl;
        std::cout << "State Date: " << state.state_date << std::endl;
        std::cout << "State ID: " << state.id << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
}