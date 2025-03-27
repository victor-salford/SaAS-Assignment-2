#ifndef SESSION_HPP
#define SESSION_HPP

#include <boost/asio.hpp>
#include <array>
#include <memory>

class Session : public std::enable_shared_from_this<Session>
{
public:
  explicit Session(boost::asio::ip::tcp::socket socket);
  void start();

private:
  void read_request_data();
  void do_write(std::size_t length);
  void handle_request();
  bool validate_input(const std::string &request_from_client);
  bool custom_starts_with(const std::string &text, const std::string &prefix);

  boost::asio::ip::tcp::socket socket_;
  std::array<char, 1024> data_;
  std::string response_;
};

#endif