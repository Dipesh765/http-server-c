#ifndef SERVER_H
#define SERVER_H

typedef struct
{
    int socket_fd;
    int port;
} Server;

void server_init(Server *server, int port);
void server_start(Server *server);
void handle_get_request(int client_sock, char *request);
void handle_patch_request(int client_sock, char *request);
void handle_post_request(int client_sock, char *request);
void handle_delete_request(int client_sock, char *request);

#endif
