/*
** EPITECH PROJECT, 2019
** myftp
** File description:
** main.c
*/

#include "my.h"

int init_value(int port, char *path, server_t *server)
{
    int var = 1;

    server->path = path;
    server->port = port;
    server->fd_srv = socket(AF_INET, SOCK_STREAM, 0);
    server->sock_in_size = sizeof(server->sock_in);
    server->sock_in.sin_family = AF_INET;
    server->sock_in.sin_port = htons(server->port);
    server->sock_in.sin_addr.s_addr = INADDR_ANY;
    setsockopt(server->fd_srv, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &var,
    sizeof(var));
    return ((server->fd_srv == -1) ? 1 : 0);
}

int iniserver(char *port, char *path, server_t *server)
{
    if (path[strlen(path) - 1] == '/')
        path[strlen(path) - 1] = '\0';
    if (chdir(path) == -1 || init_value(atoi(port), path, server))
        return (1);
    if (bind(server->fd_srv, (const struct sockaddr *)&server->sock_in, \
sizeof(server->sock_in)) < 0 || listen(server->fd_srv, 3) < 0)
        return (1);
    return (0);
}

int main(int ac, char **av)
{
    server_t server;

    if (ac != 3 || iniserver(av[1], av[2], &server))
        return (84);
    else{
        server_gestion(server);
        close(server.fd_srv);
        return (0);
    }
}