/*
** EPITECH PROJECT, 2019
** myftp
** File description:
** serveur gestion
*/

#include "my.h"

void handle_eve_client(List list, fd_set s_read)
{
    char **tab;
    char *line = NULL;
    List tmp;

    for (tmp = list ; tmp != NULL; tmp = tmp->next){
        if (tmp->log == -1)
            continue;
        if (FD_ISSET(tmp->sockfd, &s_read))
            break;
    }
	line = get_next_line(tmp->sockfd);
    tab = str_wordtab(line, "  \t\n\r");
    free (line);
    if (tab == NULL)
        return;
    do_cmd(tab, tmp);
    for (int i = 0; tab[i] != NULL; free(tab[i++]));
    free (tab);
}

List add_client(element *client, List list)
{
    List tmp = list;

    if (list == NULL)
        return (client);
    for (; tmp->next != NULL ; tmp = tmp->next);
    tmp->next = client;
    return (list);
}

int new_client(server_t *server, List *list)
{
    struct sockaddr_in client_address;
    element *client = malloc(sizeof(element));
    socklen_t client_addrlen = sizeof(struct sockaddr_in);
    
    memset(&client_address, 0, sizeof(client_address));
    client->sockfd = accept(server->fd_srv, (struct sockaddr *)&client_address, (socklen_t *)&client_addrlen);
    if (client->sockfd <= 0){
        perror("Accept function failed");
        close (client->sockfd);
        return (-1);
    }
    client->serv_client = client_address;
    getcwd(client->pwd, sizeof(client->pwd));
    client->log = 0;
    getcwd(client->root, sizeof(client->root));
    client->username = NULL;
    client->mode = -1;
    *list = add_client(client, *list);
    printf("Connection from %s:%d\n", inet_ntoa(client_address.sin_addr), \
htons(client_address.sin_port));
    dprintf(client->sockfd, "220 Connected !\n");
    return (client->sockfd);
}

void remake(fd_set *set_read, fd_set *set_write, List *list, int server_fd)
{
    FD_ZERO(set_read);
    FD_ZERO(set_write);
    FD_SET(server_fd, set_read);
    for (List tmp = *list; tmp != NULL; tmp = tmp->next){
        if (tmp->log != -1)
            FD_SET(tmp->sockfd, set_read);
        else
            FD_CLR(tmp->sockfd, set_read);
    }
}

int server_gestion(server_t server)
{
    int max = server.fd_srv;
    int client;
    fd_set s_write;
    fd_set s_read;
    List list = NULL;

    FD_ZERO(&s_read);
    FD_ZERO(&s_write);
    FD_SET(server.fd_srv, &s_read);
    printf("Listening on port %i...\n", server.port);
    while (1) {
        select(max + 1, &s_read, &s_write, NULL, NULL);
        if (FD_ISSET(server.fd_srv, &s_read)){
            client = new_client(&server, &list);
            max = (client == -1) ? max : client;
        }
        else
            handle_eve_client(list, s_read);
        remake(&s_read, &s_write, &list, server.fd_srv);
	}
	close(server.fd_srv);
	return (0);
}