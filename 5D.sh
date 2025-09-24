#!/bin/bash

# Ruta del archivo donde se escribirá la IP
IP_FILE="./server_ip.txt"

# Compilar el cliente
gcc client_10_seg.c -o cliente_10

# Esperar hasta que el archivo no esté vacío
while [ ! -s "$IP_FILE" ]; do
  echo "Esperando IP..."
  sleep 1
done

# Leer la IP del archivo
IP=$(cat "$IP_FILE" | tr -d '[:space:]')

# Esperar hasta que el servidor esté escuchando en el puerto 8080
until nc -z "$IP" 8080; do
  echo "Esperando servidor en $IP:8080..."
  sleep 1
done

# Ejecutar el cliente con la IP leída
echo "Ejecutando ./cliente_10 $IP"
./cliente_10 "$IP"
