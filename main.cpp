#include <iostream>
#include <thread>

#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include "SimpleServer.h"
#include "Client.h"

using namespace boost::asio;

boost::property_tree::ptree json_from_string(const std::string& s_json) {
    std::stringstream jsonEncoded(s_json);
    boost::property_tree::ptree root;
    boost::property_tree::read_json(jsonEncoded, root);

    return root;
}

boost::property_tree::ptree extract_weather(const boost::property_tree::ptree & tree) {
    boost::property_tree::ptree raw_weather = tree.get_child("weather");
    boost::property_tree::ptree::iterator w_iter = raw_weather.begin();
    boost::property_tree::ptree weather;
    for(; w_iter != raw_weather.end(); ++w_iter) {
        weather = w_iter->second;
    }

    return weather;
}

void print_weather(const boost::property_tree::ptree & tree) {
    boost::property_tree::ptree weather = extract_weather(tree);

    std::cout << "coords: (" << tree.get<double>("coord.lon") << "; " << tree.get<double>("coord.lat") << ")" << std::endl;
    std::cout << "temperature: " << tree.get<double>("main.temp") << " K" << std::endl;
    std::cout << "general condition: " << weather.get<std::string>("main") << std::endl;
    std::cout << "city: " << tree.get<std::string>("name") << std::endl;
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
    std::cout << ep.address().to_string() << std::endl;

    // ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 80);
    ip::tcp::socket sock(service);

    Client client(boost::shared_ptr<ip::tcp::socket>(new ip::tcp::socket(service)));
    client.set_endpoint(ep);
    client.connect();

    std::string response = client.request(target);

    client.disconnect();

    std::cout << response << std::endl;

    boost::property_tree::ptree tree = json_from_string(response);

    while (true) {
        print_weather(tree);
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(10s);
    }


    return 0;
}