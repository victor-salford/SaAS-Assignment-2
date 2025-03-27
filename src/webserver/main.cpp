#include <iostream>
#include <utility>
#include <boost/asio.hpp>
#include "server.hpp"


int main() {
    try {
         boost::asio::io_context ctx;
        Server server(ctx, 8080);

        std::cout << "Server running on port 8080\n";
        ctx.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}