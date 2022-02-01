#pragma once

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#include <vector>
#include <thread>
#include <memory>

#include <libtcpserver/socket/socket.h>


class socket_server {
    private:
        std::vector<std::unique_ptr<socket_client>> clients;

        int server_fd;
        sockaddr_in server_address;

        int port;

        void handle_new_connection(int client_fd, sockaddr_in client_address);
    public:
        socket_server(int port);
        ~socket_server();

        // Start listening for connections
        void start();

        // Stop listening for connections
        void stop();

        // Accept new connections to the connection pool
        bool accept_connections();

        // Get a specific client
        socket_client& get_client(int index);

        // Get the number of clients
        int get_client_count() const;

        // Close client connection
        void close_client(int index);
};