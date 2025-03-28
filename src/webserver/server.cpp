#include <iostream>
#include "server.hpp"
#include "session.hpp"
#include "server.interface.hpp"

Server::Server(boost::asio::io_context& context, unsigned short port)
   :acceptor(context, tcp::endpoint(tcp::v4(), port))
{
    listen_for_incoming_connections();
}

void Server::start()
{
    listen_for_incoming_connections();
}

void Server::stop()
{
    acceptor.close();
}

void Server::listen_for_incoming_connections()
{
    acceptor.async_accept(
        [this](std::error_code ec, tcp::socket socket) {
            if(!ec) {
               std::make_shared<Session>(std::move(socket))->start();
            }
        }
    );
}
