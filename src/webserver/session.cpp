#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>
#include "session.hpp"
#include "helpers.hpp"

using boost::asio::ip::tcp;

Session::Session(tcp::socket socket) : socket_(std::move(socket)) {}

void Session::start()
{
    read_request_data();
}

void Session::read_request_data()
{
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_),
                            [this, self](std::error_code ec, std::size_t length)
                            {
                                if (!ec)
                                {
                                    do_write(length);
                                }
                            });
}

void Session::do_write(std::size_t length)
{
    auto self(shared_from_this());
    handle_request();
    boost::asio::async_write(socket_, boost::asio::buffer(response_),
                             [this, self](std::error_code ec, std::size_t)
                             {
                                 if (!ec)
                                 {
                                     read_request_data();
                                 }
                             });
}

void Session::handle_request()
{
    std::string request(data_.data());
    if (!validate_input(request))
    {
        std::string error_message = "400 Bad Request";
        response_ = "HTTP/1.1 400 Bad Request\r\n";
        response_ += "Content-Type: text/plain\r\n";
        response_ += "Content-Length: " + std::to_string(error_message.size()) + "\r\n";
        response_ += "\r\n";
        response_ += error_message;
    }
    else
    {
        response_ = "HTTP/1.1 200 OK\r\n";
        response_ += "Content-Type: text/html\r\n";
        response_ += "Content-Length: 54\r\n";
        response_ += "\r\n";
        response_ += "<html><body><h1>Hello from ASIO server!</h1></body></html>";
    }
}

bool Session::validate_input(const std::string &request_from_client)
{
    if ((custom_starts_with(request_from_client, "GET") && custom_starts_with(request_from_client, "POST")))
    {
        return true;
    }

    if (request_from_client.size() <= 1024)
    {
        return true;
    }

    return false;
}

bool Session::custom_starts_with(const std::string &text, const std::string &prefix)
{
    return text.compare(0, prefix.size(), prefix) == 0;
}
