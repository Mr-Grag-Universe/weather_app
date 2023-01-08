//
// Created by Stephan on 08.01.2023.
//

#ifndef WEATHER_APP_CLIENT_H
#define WEATHER_APP_CLIENT_H
#include <iostream>
#include <utility>

#include <boost/asio.hpp>
// #include <boost/beast.hpp>


using namespace boost::asio;
// using namespace boost::beast;
class Client {
    typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
    typedef boost::shared_ptr<io_service> io_service_ptr;
private:
    socket_ptr m_sock;
    io_service_ptr service;

    size_t m_port{};
    ip::address m_address;
    ip::tcp::endpoint m_ep;
public:
    Client(socket_ptr sock) : m_sock(std::move(sock)) {
        // if (!m_sock->is_open())
            // m_sock->open(ip::tcp::v4());
    }

    void set_endpoint(const ip::tcp::endpoint & ep) {
        m_ep = ep;
        m_port = ep.port();
        m_address = ep.address();
    }

    void connect() {
        try {
            m_sock->connect(m_ep);
        } catch (...) {
            std::cerr << "connection error" << std::endl;
            return;
        }
    }

    void disconnect() {
        if (m_sock->is_open()) {
            m_sock->shutdown(ip::tcp::socket::shutdown_receive);
            m_sock->close();
        }
        else
            std::cerr << "connection is already disable" << std::endl;
    }

    std::string request(const std::string & target) {
        std::string payload = "GET " + target + "\r\n";
        std::cout << "request: " << payload << std::endl;
        // Отправляем реквест через приконекченный сокет
        m_sock->write_some(buffer(payload));
        // std::cout << "bytes available " << m_sock->available() << std::endl;
        char buff[1024];
        size_t read = m_sock->read_some(buffer(buff));
        std::string response = std::string(buff).substr(0, read);
        // std::cout << "size: " << read << "\nresponse: " << response << std::endl;

        return response;
    }
};


#endif //WEATHER_APP_CLIENT_H
