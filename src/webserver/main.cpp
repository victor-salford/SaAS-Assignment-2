#include <iostream>
#include <utility>
#include <thread>
#include <sstream>
#include <memory>
#include <boost/asio.hpp>
#include "server.hpp"
#include "server.interface.hpp"

int main()
{
    try
    {
        boost::asio::io_context ctx;
        const int thread_pool_size = 4;
        const unsigned short port = 8080;

        std::unique_ptr<IServer> server = std::make_unique<Server>(ctx, port);

        std::cout << "Server running on port 8080\n";

        // Set up signal handling for graceful shutdown
        boost::asio::signal_set signals(ctx, SIGINT, SIGTERM);
        signals.async_wait(
            [&](auto, auto) {
                server->stop();
                ctx.stop();
            });
        
        std::cout << "Server running on port " << port << "\n";
        std::cout << "Using " << thread_pool_size << " worker threads\n";
        std::cout << "Press Ctrl+C to exit...\n";

        server->start();

       // Create thread pool
        std::vector<std::thread> threads;
        threads.reserve(thread_pool_size);
        for (int i = 0; i < thread_pool_size; ++i) {
            threads.emplace_back([&ctx, i]() {
                std::stringstream ss;
                ss << std::this_thread::get_id();
                std::cout << "Thread " << i + 1 << " started  (ID " << ss.str() << ")\n";
                try {
                    ctx.run();
                } catch (const std::exception& e) {
                    std::cerr << "Thread exception: " << e.what() << "\n";
                }
            });
        }
        
        // Wait for all threads to complete
        for (auto& thread : threads) {
            thread.join();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}