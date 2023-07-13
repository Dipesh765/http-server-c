#include <stdio.h>
#include <stdlib.h>
#include "server.h"

int main()
{
    // Create a new server instance
    Server server;
    server_init(&server, 8080);

    // Start the server
    server_start(&server);

    return 0;
}