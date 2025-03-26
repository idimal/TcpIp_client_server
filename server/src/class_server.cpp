#include "class_server.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <cstdlib>
#include <cstddef>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "LibParserSaver/class_saver.h"


void Server::start_server(int server_port, const char* server_ip) {
    // Создаем сокет
    this->listener = socket(AF_INET, SOCK_STREAM, 0);
    if(this->listener < 0)
    {
        perror("socket");
        exit(1);
    }

    // Настраиваем адрес сервера
    memset(&this->server_addr, 0, sizeof(this->server_addr));
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_port = htons(server_port); // Порт сервера
    this->server_addr.sin_addr.s_addr = inet_addr(server_ip); // Принимаем подключения на все интерфейсы

    // Привязываем сокет к адресу сервера
    if(bind(this->listener, (struct sockaddr *)&this->server_addr, sizeof(this->server_addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    // Прослушиваем входящие подключения
    listen(this->listener, 1);

}

void Server::stop_server() {
    close(this->listener);
    std::cout << "Server stopped" << std::endl;
}

bool Server::connect_client() {
    // Принимаем подключение от клиента
    this->client_addr_len = sizeof(this->client_addr);
    this->client_sock = accept(this->listener, (struct sockaddr *)&this->client_addr, &this->client_addr_len);
    if(this->client_sock < 0)
    {
        perror("accept");
        return false;
    }

    // Выводим IP-адрес клиента
    printf("Client connected: %s %d\n", inet_ntoa(this->client_addr.sin_addr), this->client_addr.sin_port);
    return true;
}

void Server::disconnect_client() {
    close(this->client_sock);

    printf("Client disconnected: %s\n", inet_ntoa(this->client_addr.sin_addr));
}

void Server::accept_file() {
    char buf[1024];
    int bytes_read;

    // Принимаем длину имени файла
    size_t file_name_len;
    if (recv(this->client_sock, &file_name_len, sizeof(file_name_len), 0) < 0) {
        perror("recv file name length");
        close(this->client_sock);
      //  continue;
    }

    // Принимаем имя файла
    char file_name[256]; // Буфер для имени файла
    if (recv(this->client_sock, file_name, file_name_len, 0) < 0) {
        perror("recv file name");
        close(this->client_sock);
      //  continue;
    }
    printf("Receiving file: %s\n", file_name);

    // Принимаем размер файла
    off_t file_size;
    if (recv(this->client_sock, &file_size, sizeof(file_size), 0) < 0) {
        perror("recv file size");
        close(this->client_sock);
      //  continue;
    }
    printf("Receiving file of size: %ld bytes\n", file_size);

    // Создаем файл для записи
    const char* file_path = file_name; // Укажите путь для сохранения файла
    int file_fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_fd < 0) {
        perror("open file");
        close(this->client_sock);
       // continue;
    }

    // Принимаем данные файла и записываем их
    off_t remaining_bytes = file_size;
    while (remaining_bytes > 0) {
        bytes_read = recv(this->client_sock, buf, sizeof(buf), 0);
        if (bytes_read <= 0) {
            perror("recv file data");
            break;
        }
        if (write(file_fd, buf, bytes_read) < 0) {
            perror("write file");
            break;
        }
        remaining_bytes -= bytes_read;
    }

    // Закрываем файл и сокет клиента
    close(file_fd);

    Saver saver;
    saver.saveData(file_name);

    if (remaining_bytes == 0) {
        printf("File received successfully: %s\n", file_path);
    } else {
        printf("File reception failed or incomplete.\n");
    }

}

void Server::transfer_file(const char* file_path) {
    // Открываем файл для передачи
    int file_fd = open(file_path, O_RDONLY);
    if (file_fd < 0) {
        perror("open");
        close(this->client_sock);
        exit(4);
    }

    // Получаем размер файла
    struct stat file_stat;
    if (fstat(file_fd, &file_stat) < 0) {
        perror("fstat");
        close(file_fd);
        close(this->client_sock);
        exit(5);
    }
    off_t file_size = file_stat.st_size;

     // Отправляем имя файла
    size_t file_name_len = strlen(file_path) + 1; // +1 для завершающего нуля
    if (send(this->client_sock, &file_name_len, sizeof(file_name_len), 0) < 0) {
        perror("send file name length");
        close(file_fd);
        close(this->client_sock);
        exit(6);
    }
    if (send(this->client_sock, file_path, file_name_len, 0) < 0) {
        perror("send file name");
        close(file_fd);
        close(this->client_sock);
        exit(7);
    }

    // Отправляем размер файла на сервер
    if (send(this->client_sock, &file_size, sizeof(file_size), 0) < 0) {
        perror("send file size");
        close(file_fd);
        close(this->client_sock);
        exit(6);
    }

    // Используем sendfile для передачи файла
    off_t offset = 0;
    ssize_t sent_bytes = sendfile(this->client_sock, file_fd, &offset, file_size);
    if (sent_bytes < 0) {
        perror("sendfile");
        close(file_fd);
        close(this->client_sock);
        exit(7);
    }

    printf("File sent successfully. Sent %zd bytes.\n", sent_bytes);

    // Закрываем файл и сокет
    close(file_fd);
    sleep(0.01);
}