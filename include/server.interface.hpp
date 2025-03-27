#ifndef SERVER_INTERFACE_HPP
#define SERVER_INTERFACE_HPP

#include <boost/asio.hpp>


class IServer {
public:
    virtual ~IServer() = default;

    // Pure virtual functions for concrete server class
    virtual void start() = 0;
    virtual void stop() = 0;
};

#endif // SERVER_INTERFACE_HPP