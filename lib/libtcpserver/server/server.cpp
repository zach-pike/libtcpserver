#include <libtcpserver/server/server.h>

#include <libtcpserver/socket/socket.h>

// Socket server constructor
socket_server::socket_server(int port) {
    this->port = port;
}

// Socket server destructor
socket_server::~socket_server() {
    // Stop the socket server
    stop();
}

// Start the socket server
void socket_server::start() {
    // Create the socket
    server_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK , 0);
    if (server_fd == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return;
    }

    // Set the socket options
    int optval = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    // Bind the socket to the port
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
        throw std::runtime_error("Error binding socket");
        return;
    }

    // Listen for connections
    if (listen(server_fd, 25) == -1) {
        throw std::runtime_error("Error listening for connections");
        return;
    }
}

// Stop the socket server
void socket_server::stop() {
    // Close the socket
    close(server_fd);

    // Stop all the clients
    for (auto& client : clients) {
        client->stop();
    }
}

// Accept new connections to the connection pool
bool socket_server::accept_connections() {
    // Accept new connections
    sockaddr_in client_address;
    socklen_t client_address_length = sizeof(client_address);

    int client_fd = accept(server_fd, (struct sockaddr *) &client_address, &client_address_length);

    if (client_fd == -1) return false;

    // Add the client to the connection pool
    auto object = std::make_unique<socket_client>(client_fd, client_address, this);
    clients.push_back(std::move(object));

    return true;
}

// Get a client from the connection pool
socket_client& socket_server::get_client(int index) {
    return *clients[index];
}

// Get the number of clients in the connection pool
int socket_server::get_client_count() const {
    return clients.size();
}

// Close a client connection
void socket_server::close_client(int index) {
    clients[index]->stop();
    clients.erase(clients.begin() + index);
}