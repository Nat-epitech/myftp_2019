/*
** EPITECH PROJECT, 2019
** myftp
** File description:
** server.h
*/

#ifndef MY_H_
#define MY_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>


typedef struct server_s {
	int fd_srv;
	int fd_clt;
	int port;
	char *path;
	struct sockaddr_in sock_in;
	socklen_t sock_in_size;
} server_t;

typedef struct element
{
    int sockfd;
    struct sockaddr_in serv_client;
    char pwd[100];
    char *root;
    int mode;
    int buff_size;
    int log;
    char *username;
    char *password;
    struct element *next;
} element, *List;

int server_gestion(server_t server);
void do_cmd(char **tab, element *clt);
char **str_wordtab(char *str, char *tok);
char	*get_next_line(const int fd);
void password(char **tab, element *clt);
void user(char **tab, element *clt);
void display_help(char **tab, element *clt);
void noop(char **tab, element *clt);
void delete(char **tab, element *clt);
void cdup(char **tab, element *clt);
void cwd(char **tab, element *clt);
void pwd(char **tab, element *clt);
void test_space(char *line, element *tmp);
#endif /* !MY_H_ */
