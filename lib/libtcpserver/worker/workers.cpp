#include <libtcpserver/worker/workers.h>

#include <libtcpserver/server/server.h>
#include <libtcpserver/socket/socket.h>

// Socket worker constructor
socket_worker::socket_worker(socket_client* socket, socket_server* server) {
    this->socket_ptr = socket;
    this->server_ptr = server;
}

// Socket worker run function
void socket_worker::run() {
    if (this->running == true) return;

    this->running = true;
    worker = std::thread(&socket_worker::worker_function, this, this->socket_ptr, this->server_ptr);
}

// Socket worker stop function
void socket_worker::stop() {
    if (this->running == false) return;

    this->running = false;
    worker.join();
}

// Socket worker, worker function
void socket_worker::worker_function(socket_worker* self, socket_client* socket, socket_server* server) {
    while (self->running == true) {
        // To be implemented
        
        int buffer_size = MAX_BUFFER_SIZE - socket->get_buffer().size();


        uint8_t* temp_buffer = new uint8_t[buffer_size];
        bzero(temp_buffer, buffer_size);

        int n = recv(socket->get_client_fd(), temp_buffer, buffer_size, MSG_DONTWAIT);

        if (n > 0) {
            // We received data
            auto new_vector = std::vector<uint8_t>(temp_buffer, temp_buffer + n);

            socket->get_buffer().insert(socket->get_buffer().end(), new_vector.begin(), new_vector.end());
        }

        // Sleep for a bit
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    }
}