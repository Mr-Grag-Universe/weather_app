#include <iostream>

#include <boost/asio.hpp>

#include "SimpleServer.h"
#include "Client.h"


using namespace boost::asio;
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

//    http::request<http::string_body> req(http::verb::get, target, 11);
//    // Задаём поля HTTP заголовка
//    req.set(http::field::host, host);
//    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    // ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 80);
    ip::tcp::socket sock(service);

    Client client(boost::shared_ptr<ip::tcp::socket>(new ip::tcp::socket(service)));
    client.set_endpoint(ep);
    client.connect();

    client.request(target);

    client.disconnect();

    return 0;
}
