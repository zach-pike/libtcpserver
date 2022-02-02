#pragma once

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#include <vector>
#include <thread>
#include <memory>
#include <mutex>
#include <functional>

#include <libtcpserver/socket/socket.h>


class socket_server {
    private:
        std::vector<std::shared_ptr<socket_client>> clients;
        mutable std::mutex clients_mutex;

        int server_fd;
        sockaddr_in server_address;

        int port;
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
        const socket_client& get_client(int index);

        void loop_over_clients(std::function<void(socket_client&)> callback);

        // Get the number of clients
        int get_client_count() const;

        // Close client connection
        void close_client(int index);

        // Close client via fd
        void close_client_by_fd(int fd);
};