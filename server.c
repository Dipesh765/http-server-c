#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "server.h"

#define MAX_REQUEST_SIZE 2048
#define RESPONSE_TEMPLATE "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\n\r\n%s"

void handle_request(int client_sock, char *request)
{
    // Determine the HTTP method
    char *method = strtok(request, " ");

    if (strcmp(method, "GET") == 0)
    {
        handle_get_request(client_sock, request);
    }
    else if (strcmp(method, "PATCH") == 0)
    {
        handle_patch_request(client_sock, request);
    }
    else if (strcmp(method, "POST") == 0)
    {
        handle_post_request(client_sock, request);
    }
    else if (strcmp(method, "DELETE") == 0)
    {
        handle_delete_request(client_sock, request);
    }
    else
    {
        // Unsupported method
        const char *response = "<html><body><h1>Unsupported Method</h1></body></html>";
        int response_length = strlen(response);

        char *http_response = (char *)malloc(MAX_REQUEST_SIZE);
        snprintf(http_response, MAX_REQUEST_SIZE, RESPONSE_TEMPLATE, response_length, response);

        send(client_sock, http_response, strlen(http_response), 0);
        free(http_response);
    }
}

void handle_get_request(int client_sock, char *request)
{
    // Logic for handling GET request
    const char *response = "<html><body><h1>GET Request</h1></body></html>";
    int response_length = strlen(response);

    char *http_response = (char *)malloc(MAX_REQUEST_SIZE);
    snprintf(http_response, MAX_REQUEST_SIZE, RESPONSE_TEMPLATE, response_length, response);

    send(client_sock, http_response, strlen(http_response), 0);
    free(http_response);
}

void handle_patch_request(int client_sock, char *request)
{
    // Logic for handling PATCH request
    const char *response = "<html><body><h1>PATCH Request</h1></body></html>";
    int response_length = strlen(response);

    char *http_response = (char *)malloc(MAX_REQUEST_SIZE);
    snprintf(http_response, MAX_REQUEST_SIZE, RESPONSE_TEMPLATE, response_length, response);

    send(client_sock, http_response, strlen(http_response), 0);
    free(http_response);
}

void handle_post_request(int client_sock, char *request)
{
    // Logic for handling POST request
    const char *response = "<html><body><h1>POST Request</h1></body></html>";
    int response_length = strlen(response);

    char *http_response = (char *)malloc(MAX_REQUEST_SIZE);
    snprintf(http_response, MAX_REQUEST_SIZE, RESPONSE_TEMPLATE, response_length, response);

    send(client_sock, http_response, strlen(http_response), 0);
    free(http_response);
}

void handle_delete_request(int client_sock, char *request)
{
    // Logic for handling DELETE request
    const char *response = "<html><body><h1>DELETE Request</h1></body></html>";
    int response_length = strlen(response);

    char *http_response = (char *)malloc(MAX_REQUEST_SIZE);
    snprintf(http_response, MAX_REQUEST_SIZE, RESPONSE_TEMPLATE, response_length, response);

    send(client_sock, http_response, strlen(http_response), 0);
    free(http_response);
}

void server_init(Server *server, int port)
{
    server->socket_fd = -1;
    server->port = port;
}

void server_start(Server *server)
{
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Create a socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1)
    {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Set up the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server->port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Failed to bind socket");
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_sock, 10) == -1)
    {
        perror("Failed to listen for connections");
        exit(EXIT_FAILURE);
    }

    printf("Server started. Listening on port %d...\n", server->port);

    while (1)
    {
        // Accept a client connection
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_len);
        if (client_sock == -1)
        {
            perror("Failed to accept client connection");
            exit(EXIT_FAILURE);
        }

        // Read the request from the client
        char request[MAX_REQUEST_SIZE];
        ssize_t request_size = recv(client_sock, request, MAX_REQUEST_SIZE - 1, 0);
        if (request_size == -1)
        {
            perror("Failed to read request from client");
            exit(EXIT_FAILURE);
        }

        // Null-terminate the request string
        request[request_size] = '\0';

        // Handle the request and send the response
        handle_request(client_sock, request);

        // Close the client connection
        close(client_sock);
    }

    // Close the server socket
    close(server_sock);
}
