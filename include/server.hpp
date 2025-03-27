#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include "session.hpp"

using boost::asio::ip::tcp;

class Server {
public:
  Server (boost::asio::io_context& context, int port);

private:
  void listen_for_incoming_connections();
  tcp::acceptor acceptor;
};

#endif
