#include <libtcpserver/server/server.h>

#include <string>
#include <chrono>
#include <thread>
#include <iostream>

int main() {
    socket_server server(8080);

    server.start();
    
    // Wait for a connection to be made
    while (server.accept_connections() == false) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    // Get the first client
    server.get_client(0).send_buffer("Hello World!", 12);

    server.get_client(0).print_address();

    // Sleep for a bit
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Get a reference to the clients buffer
    auto& buffer = server.get_client(0).get_buffer();

    // Print the buffer of client 0
    std::cout << std::string{ (char*)buffer.data(), buffer.size() } << std::endl;

    // Stop the server
    server.stop();


    return 0;
}