#include "../include/LibParserSaver/class_parser.h"
#include <string>
#include <vector>
#include "pugixml.hpp"


// Функция для парсинга XML и заполнения структуры
State Parser::parseState(const pugi::xml_document& doc) {
    State data;
    // Получаем корневой элемент
    pugi::xml_node plmlNode = doc.child("plml");
    if (plmlNode) {
        // Получаем атрибут version
        data.version = plmlNode.attribute("version").as_string();

        // Получаем элемент getState
        pugi::xml_node getStateNode = plmlNode.child("getState");
        if (getStateNode) {
            // Получаем атрибут typeState
            data.typeState = getStateNode.attribute("typeState").as_int();
        }
    }

    return data;
}

PlmlData Parser::parseData(const pugi::xml_document& doc) {
    PlmlData plml;

    // Получаем корневой элемент <plml>
    pugi::xml_node plmlNode = doc.child("plml");

    // Парсим атрибут version
    plml.version = plmlNode.attribute("version").as_int();

    // Парсим все элементы <state>
    for (pugi::xml_node stateNode : plmlNode.children("state")) {
        Data state;
        state.name = stateNode.attribute("name").as_string();
        state.state = stateNode.attribute("state").as_int();
        state.state_string = stateNode.attribute("state_string").as_string();
        state.state_type = stateNode.attribute("state_type").as_int();
        state.state_date = stateNode.attribute("state_date").as_string();
        state.id = stateNode.attribute("id").as_string();

        plml.states.push_back(state);
    }

    return plml;
}