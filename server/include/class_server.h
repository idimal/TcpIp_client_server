#pragma once 

#include <netinet/in.h>
#include <unistd.h>


class Server{
    public:
        Server(){}
        void start_server(int server_port, const char* server_ip);
        void stop_server();
        void accept_file();
        void transfer_file(const char* file_path);
        bool connect_client();
        void disconnect_client();
        ~Server(){close(this->listener);}

    private:
        int client_sock, listener;
        struct sockaddr_in server_addr, client_addr;
        socklen_t client_addr_len;
};