#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BACKLOG 5

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0); // desactiva buffering para poder registrar el log del servidor
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // creo el socket del servidor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("socket");
        exit(1);
    }

    // configuro la dirección del servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // escucha en todas las interfaces
    server_addr.sin_port = htons(PORT);

    // enlazo el socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind");
        exit(1);
    }

    // escucho conexiones entrantes
    if (listen(server_fd, BACKLOG) < 0)
    {
        perror("listen");
        exit(1);
    }

    printf("Servidor escuchando en el puerto %d...\n", PORT);

    while (1)
    {
        // acepto un cliente
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_fd < 0)
        {
            perror("accept");
            continue;
        }

        printf("Cliente conectado: %s\n", inet_ntoa(client_addr.sin_addr));

        // recibo datos en un buffer grande
        char buffer[1024 * 1024]; // hasta 1 MB
        ssize_t bytes_received;

        while ((bytes_received = read(client_fd, buffer, sizeof(buffer))) > 0)
        {
            printf("Recibidos %zd bytes\n", bytes_received);

            // para el ping-pong, devolvés lo recibido:
            write(client_fd, buffer, bytes_received);
        }

        printf("Cliente desconectado\n");
        close(client_fd);
    }

    close(server_fd);
    return 0;
}
