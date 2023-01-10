//
// Created by Stephan on 09.01.2023.
//

#ifndef WEATHER_APP_C_WEATHER_H
#define WEATHER_APP_C_WEATHER_H

#include <string>
#include <boost/property_tree/ptree.hpp>

struct S_Coord {
    double lon{};
    double lat{};
};

struct S_Weather {
    size_t id{};
    std::string main;
    std::string description;
    std::string icon;

    explicit S_Weather(const boost::property_tree::ptree & tree) :
    id(tree.get<size_t>("id")), main(tree.get<std::string>("main")),
    description(tree.get<std::string>("description")), icon(tree.get<std::string>("icon"))
    {}
};

struct S_Indicators {
    double temp{};
    double feels_like{};
    double temp_min{}, temp_max{};
    double pressure{};
    double humidity{};
    double sea_level{};
    double grnd_level{};

    explicit S_Indicators(const boost::property_tree::ptree & tree) :
    temp(tree.get<double>("temp")), feels_like(tree.get<double>("feels_like")),
    temp_min(tree.get<double>("temp_min")), temp_max(tree.get<double>("temp_max")),
    pressure(tree.get<double>("pressure")), humidity(tree.get<double>("humidity")),
    sea_level(tree.get<double>("sea_level")), grnd_level(tree.get<double>("grnd_level"))
    {}
};

struct S_Wind {
    double speed{};
    double deg{};
    double gust{};

    explicit S_Wind(const boost::property_tree::ptree & tree) :
        speed(tree.get<double>("speed")), deg(tree.get<double>("deg")), gust(tree.get<double>("gust"))
    {}
};

struct S_Sys {
    size_t type{};
    size_t id{};
    std::string country{};
    size_t sunrise{};
    size_t sunset{};

    S_Sys(const boost::property_tree::ptree & tree) :
        type(tree.get<size_t>("type")), id(tree.get<size_t>("id")),
        country(tree.get<std::string>("country")), sunrise(tree.get<size_t>("sunrise")),
        sunset(tree.get<size_t>("sunset"))
    {}
};

class C_Weather {
private:
    S_Coord coord;
    S_Weather weather;
    S_Indicators indicators;
    S_Wind wind;
    S_Sys sys;

    std::string base;
    double visibility{};
    double clouds{};
    size_t dt{};
    size_t timezone{};
    size_t id{};
    std::string name;
public:
    explicit C_Weather(const boost::property_tree::ptree & tree);
public:
    [[nodiscard]] S_Coord getCoord() const;
    [[nodiscard]] S_Weather getWeather() const;
    [[nodiscard]] S_Indicators getIndicators() const;
    [[nodiscard]] S_Sys getSys() const;

    [[nodiscard]] std::string getName() const;
public:
    void setCoord();
    void setWeather();
    void setIndicators();
    void setSys();
};


#endif //WEATHER_APP_C_WEATHER_H
