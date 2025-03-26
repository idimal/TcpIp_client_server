/// Клиент
#include <iostream>
#include <unistd.h>
#include "class_client.h"


int main()
{
    Client client;
    
    if (client.establish_connection(22011, "127.0.0.2", "127.0.0.1")) {
        while (true) {
            client.accept_file();
            // do something, probably with DB, here
            client.transfer_file("../src/client_data.xml");
            sleep(6);
        }
    }
    else {
        std::cout << "Reconnect" << std::endl;
        if (client.establish_connection(22011, "127.0.0.4", "127.0.0.3")) {
            while (true) {
                client.accept_file();
                // do something, probably with DB, here
                client.transfer_file("../src/client_data.xml");
                sleep(6);
            }
        }
        else {
            std::cout << "Failed to connect client" << std::endl;
        }
    }

    return 0;
}