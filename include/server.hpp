#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include "session.hpp"
#include "server.interface.hpp"

using boost::asio::ip::tcp;

class Server : public IServer {
public:
  Server (boost::asio::io_context& context, unsigned short port);
  void start();
  void stop();

private:
  void listen_for_incoming_connections();
  tcp::acceptor acceptor;
};

#endif
