#include <iostream>
#include <thread>

#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "SimpleServer.h"
#include "Client.h"
#include "C_Weather.h"

using namespace boost::asio;

boost::property_tree::ptree json_from_string(const std::string& s_json) {
    std::stringstream jsonEncoded(s_json);
    boost::property_tree::ptree root;
    boost::property_tree::read_json(jsonEncoded, root);

    return root;
}

void print_weather(const boost::property_tree::ptree & tree) {
    C_Weather weather(tree);

    std::cout << "coords: (" << weather.getCoord().lat << "; " << weather.getCoord().lon << ")" << std::endl;
    std::cout << "temperature: " << weather.getIndicators().temp << " K" << std::endl;
    std::cout << "general condition: " << weather.getWeather().main << std::endl;
    std::cout << "city: " << weather.getName() << std::endl;
}

int main() {
    const std::string api_key = "b6773ab431aa1a652d6a359c89125f68";
    const std::string host = "api.openweathermap.org";
    const std::string target = "/data/2.5/weather?id=524901&appid=" + api_key;

    io_service service;

    ip::tcp::resolver resolver(service);
    ip::tcp::resolver::query query(host, "80");
    ip::tcp::resolver::iterator iter = resolver.resolve( query);
    ip::tcp::endpoint ep = *iter;
    // std::cout << ep.address().to_string() << std::endl;

    // ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 80);
    ip::tcp::socket sock(service);

    Client client(boost::shared_ptr<ip::tcp::socket>(new ip::tcp::socket(service)));
    client.set_endpoint(ep);
    client.connect();



    // std::cout << response << std::endl;

    while (true) {
        std::string response = client.request(target);
        boost::property_tree::ptree tree = json_from_string(response);
        print_weather(tree);
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(10s);
    }

    client.disconnect();

    return 0;
}