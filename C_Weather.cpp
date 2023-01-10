//
// Created by Stephan on 09.01.2023.
//

#include "C_Weather.h"


boost::property_tree::ptree extract_weather(const boost::property_tree::ptree & tree) {
    boost::property_tree::ptree raw_weather = tree.get_child("weather");
    boost::property_tree::ptree::iterator w_iter = raw_weather.begin();
    boost::property_tree::ptree weather = w_iter->second;

    return weather;
}

C_Weather::C_Weather(const boost::property_tree::ptree &tree) :
    base(tree.get<std::string>("base")), visibility(tree.get<double>("visibility")), clouds(tree.get<double>("clouds.all")),
    dt(tree.get<size_t>("dt")), timezone(tree.get<size_t>("timezone")), id(tree.get<size_t>("id")), name(tree.get<std::string>("name")),
    coord({tree.get<double>("coord.lon"), tree.get<double>("coord.lat")}),
    weather(S_Weather(extract_weather(tree))),
    indicators(S_Indicators(tree.get_child("main"))),
    wind(S_Wind(tree.get_child("wind"))),
    sys(S_Sys(tree.get_child("sys"))) {}

//=================== getters ====================//

S_Coord C_Weather::getCoord() const {
    return coord;
}

S_Weather C_Weather::getWeather() const {
    return weather;
}

S_Indicators C_Weather::getIndicators() const {
    return indicators;
}

S_Sys C_Weather::getSys() const {
    return sys;
}

//================== setters ================//

void C_Weather::setCoord() {

}

void C_Weather::setWeather() {

}

void C_Weather::setIndicators() {

}

void C_Weather::setSys() {

}

std::string C_Weather::getName() const {
    return name;
}
