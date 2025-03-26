#pragma once
#include <netinet/in.h>


class Client {
    public:
        Client(){}
        bool establish_connection(int server_port, const char* server_ip, const char* client_ip);
        void transfer_file(const char* file_path);
        void accept_file();
        ~Client(){}

    private:
        int client_sock;
        struct sockaddr_in client_addr, server_addr;
};