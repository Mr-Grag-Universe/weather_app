//
// Created by Stephan on 08.01.2023.
//

#ifndef WEATHER_APP_SIMPLESERVER_H
#define WEATHER_APP_SIMPLESERVER_H

#include <boost/asio.hpp>
// #include <boost/thread.hpp>

using namespace boost::asio;
class SimpleServer {
    typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
private:
    size_t m_port{};
public:
    [[noreturn]] static void client_session(const socket_ptr& sock) {
        while (true)
        {
            char data[512];
            size_t len = sock->read_some(buffer(data));
            if ( len > 0)
                write(*sock, buffer("ok", 2));
        }
    }

    explicit SimpleServer(size_t port=2001) : m_port(port) {
        io_service service;
        ip::tcp::endpoint ep(ip::tcp::v4(), port);
        ip::tcp::acceptor acc(service, ep);
        while (true)
        {
            socket_ptr sock(new ip::tcp::socket(service));
            acc.accept(*sock);
            // boost::thread(boost::bind(client_session, sock));
        }
    }
};


#endif //WEATHER_APP_SIMPLESERVER_H
