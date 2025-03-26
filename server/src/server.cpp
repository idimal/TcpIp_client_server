/// Сервер
#include <iostream>
#include <unistd.h>
#include "class_server.h"

int main()
{
    Server server_1;

    server_1.start_server(22011, "127.0.0.2");
    if (server_1.connect_client()) {
        while (true) {
            server_1.transfer_file("../src/server_data.xml");

            server_1.accept_file();
            sleep(6);
        }
        server_1.disconnect_client();
    }
    else {
        std::cout << "Reconnect" << std::endl;
        server_1.stop_server();
        server_1.start_server(22011, "127.0.0.4");

        if (server_1.connect_client()) {
            while (true) {
                server_1.transfer_file("../src/server_data.xml");
    
                server_1.accept_file();
                sleep(6);
            }
            server_1.disconnect_client();
        }
        else {
            std::cout << "Failed to connect client" << std::endl;
        }
    }
   
    server_1.stop_server();

    return 0;
}