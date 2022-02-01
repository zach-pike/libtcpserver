#include "socket/socket.h"

#include "server/server.h"

// Socket client constructor
socket_client::socket_client(int client_fd, sockaddr_in client_address, socket_server* server):
    connection(socket_connection{ client_fd, client_address }),
    worker(this, server)
{
    // Start the socket worker and fill the buffer with zeros
    worker.run();
}

// Socket client destructor
socket_client::~socket_client() {
    // Stop the socket
    stop();
}

// Print the client address
void socket_client::print_address() const {
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &connection.client_address.sin_addr, client_ip, INET_ADDRSTRLEN);
    int client_port = ntohs(connection.client_address.sin_port);

    std::cout << "Client connected: " << client_ip << ":" << client_port << std::endl;
}

// Stop the socket client
void socket_client::stop() {
    // Stop the socket worker
    worker.stop();

    // Close the socket
    close(connection.client_fd);
}

// Get the client buffer
buffer_t& socket_client::get_buffer() {
    return buffer;
}

// Send a buffer to the client
void socket_client::send_buffer(const char* buffer, int buffer_size) const {
    // Send the buffer
    send(connection.client_fd, buffer, buffer_size, 0);
}

// Get the client file descriptor
int socket_client::get_client_fd() const {
    return connection.client_fd;
}