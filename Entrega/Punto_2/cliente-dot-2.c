#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
    char *server_ip = argv[1];
    int tamanios[] = {10, 100, 1000, 10000, 100000, 1000000};
    int n = sizeof(tamanios) / sizeof(tamanios[0]); // calculo el tamaño del array

    for (int i = 0; i < n; i++)
    {
        int size = tamanios[i];
        char *buffer = malloc(size);
        memset(buffer, 'A', size); // lleno de 'A'

        // creo el socket
        int fd_cliente = socket(AF_INET, SOCK_STREAM, 0);
        if (fd_cliente < 0)
        {
            perror("socket");
            exit(1);
        }

        // configuro al servidor
        struct sockaddr_in servidor;
        servidor.sin_family = AF_INET;
        inet_pton(AF_INET, server_ip, &servidor.sin_addr);
        servidor.sin_port = htons(8080);

        if (connect(fd_cliente, (struct sockaddr *)&servidor, sizeof(servidor)) < 0)
        {
            perror("connect");
            exit(1);
        }

        struct timeval start1, start2, end1, end2;
        gettimeofday(&start1, NULL);

        // envío el mensaje
        write(fd_cliente, buffer, size);

        gettimeofday(&end1, NULL);

        gettimeofday(&start2, NULL);
        // para el ping-pong:
        read(fd_cliente, buffer, size);

        gettimeofday(&end2, NULL);

        double elapsed1 = (end1.tv_sec - start1.tv_sec) +
                          ((end1.tv_usec - start1.tv_usec) / 1000000.0);

        double elapsed2 = (end2.tv_sec - start2.tv_sec) +
                          ((end2.tv_usec - start2.tv_usec) / 1000000.0);

        printf("Tamaño: %d bytes, Tiempo write: %f segundos, Tiempo read: %f segundos\n", size, elapsed1, elapsed2);

        close(fd_cliente);
        free(buffer);
    }

    return 0;
}
