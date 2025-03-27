#include <iostream>
#include <utility>
#include <boost/asio.hpp>
#include "server.hpp"
#include "server.interface.hpp"

int main()
{
    try
    {
        boost::asio::io_context ctx;

        std::unique_ptr<IServer> server = std::make_unique<Server>(ctx, 8080);

        std::cout << "Server running on port 8080\n";

        server->start();

        ctx.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}