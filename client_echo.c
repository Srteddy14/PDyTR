#include <stdio.h>
#include <stdlib.h> // Para exit, atoi y otras funciones estándar
#include <string.h> // Para bzero y otras funciones de cadenas
#include <unistd.h> // Para read, write y otras funciones de E/S
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

int main()
{
    char buffer[256];
    int file_descriptor_cliente = socket(AF_INET, SOCK_STREAM, 0);
    printf("Ingresa un mensaje para enviar al servidor: ");
    fgets(buffer, 255, stdin);

    // configuro al servidor
    struct sockaddr_in servidor;
    servidor.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &servidor.sin_addr); // inet_pton = internet address presentation to network, pasa de string a struct, htons o ntohs es para numeros solitos,no structs
    servidor.sin_port = htons(8080);                     // host to network short

    // aunque parezca redundante repetir AF_INET en la struct sockaddr_in,
    // sirve como consistencia y validación: asegura que la dirección que estás
    // pasando es de la misma familia que el socket que creaste.

    connect(file_descriptor_cliente, (struct sockaddr *)&servidor, sizeof(servidor));

    struct timeval start, end;
    gettimeofday(&start, NULL);
    write(file_descriptor_cliente, buffer, strlen(buffer));
    sleep(5);
    gettimeofday(&end, NULL);

    double elapsed = (end.tv_sec - start.tv_sec) +
                     ((end.tv_usec - start.tv_usec) / 1000000.0);

    printf("Elapsed time: %f seconds\n", elapsed);

    close(file_descriptor_cliente);
}