#pragma once

#include <libtcpserver/worker/workers.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <iostream>
#include <vector>

constexpr int MAX_BUFFER_SIZE = 4 * 1024;
using buffer_t = std::vector<uint8_t>;

// Don't you love dealing with circular includes?
class socket_server;

struct socket_connection {
    int client_fd;
    sockaddr_in client_address;
};

class socket_client {
    private:
        socket_connection connection;
        socket_worker worker;
        socket_server* server;

        buffer_t buffer;

    public:
        socket_client(int client_fd, sockaddr_in client_address, socket_server* server);
        ~socket_client();

        // Print the address of the client
        void print_address() const;

        // Send a buffer to the client
        void send_buffer(const char* buffer, int buffer_size) const;
        
        // Get reference to the client buffer
        buffer_t& get_buffer();
        
        // Get the client file descriptor
        int get_client_fd() const;

        // Close the client connection and stop the worker
        void stop();

};