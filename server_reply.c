#include <stdio.h>
#include <stdlib.h> // Para exit, atoi y otras funciones estándar
#include <string.h> // Para bzero y otras funciones de cadenas
#include <unistd.h> // Para read, write y otras funciones de E/S
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // for inet_ntoa

int main()
{
    char buffer[20];
    // fgets(buffer, 20, stdin);
    // printf("Lo que escribiste es: %s", buffer);

    struct sockaddr_in servidor;
    servidor.sin_addr.s_addr = INADDR_ANY; // socket address= internet adress any (escucha de cualquier interfaz)
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(8080); // host to networkS transdormar el dato de computadora host a datos de red, al reves es ntohs, network to hostS
    int file_descriptor_servidor;
    file_descriptor_servidor = socket(AF_INET, SOCK_STREAM, 0);                        // AF_INET = address family: internet
    bind(file_descriptor_servidor, (struct sockaddr_in *)&servidor, sizeof(servidor)); // no quiero que sea random los valores del socket

    listen(file_descriptor_servidor, 4);

    struct sockaddr_in cliente; // por si quiero usar su puerto e ip
    socklen_t cliente_length = sizeof(cliente);

    int file_descriptor_cliente = accept(file_descriptor_servidor, (struct sockaddr_in *)&cliente, &cliente_length);

    read(file_descriptor_cliente, buffer, 20); // los arrays en C son punteros a la cabeza del array ntohs(cliente.sin_addr.s_addr)
    printf("El cliente con IP: %s y puerto %d me dijo: %s", inet_ntoa(cliente.sin_addr), ntohs(cliente.sin_port), buffer);

    close(file_descriptor_cliente);
    close(file_descriptor_servidor);
}