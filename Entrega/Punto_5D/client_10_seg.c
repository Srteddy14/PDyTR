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
    printf("Cliente durmiendo 10 segundos\n");
    sleep(10);
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

        struct timeval start, end;
        gettimeofday(&start, NULL);

        // envío el mensaje
        write(fd_cliente, buffer, size);

        // para el ping-pong:
        read(fd_cliente, buffer, size);

        gettimeofday(&end, NULL);

        double elapsed = (end.tv_sec - start.tv_sec) +
                         ((end.tv_usec - start.tv_usec) / 1000000.0);

        printf("Tamaño: %d bytes, Tiempo ida-vuelta: %f segundos, Tiempo ida: %f segundos\n", size, elapsed, elapsed / 2.0);

        close(fd_cliente);
        free(buffer);
    }

    return 0;
}
