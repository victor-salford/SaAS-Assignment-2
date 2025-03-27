#include <iostream>
#include "server.hpp"
#include "session.hpp"

Server::Server(boost::asio::io_context& context, int port)
   :acceptor(context, tcp::endpoint(tcp::v4(), port))
{
    listen_for_incoming_connections();
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
