#pragma once

#include <thread>
#include <atomic>

// Don't you love dealing with circular includes?
class socket_server;
class socket_client;

class socket_worker {
    private:
        std::thread worker;

        socket_client* socket_ptr;
        socket_server* server_ptr;

        std::atomic_bool running;

        static void worker_function(socket_worker* self, socket_client* socket, socket_server* server);

    public:
        socket_worker(socket_client* socket, socket_server* server);

        void run();
        void stop();
};