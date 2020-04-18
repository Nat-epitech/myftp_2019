/*
** EPITECH PROJECT, 2019
** myftp
** File description:
** few of cmd
*/

#include "my.h"

void password(char **tab, element *clt)
{
    clt->password = (tab[1]) ? strdup(tab[1]) : NULL;
    if (clt->username != NULL){
        dprintf(clt->sockfd, "230 User logged in, proceed.\n");
        clt->log = 1;
    }
    else
        dprintf(clt->sockfd, "530 No User name\n");
}

void user(char **tab, element *clt)
{
    if (clt->log == 1){
        dprintf(clt->sockfd, "530 Already loged in.\n");
        return;
    }
    if (tab[1] == NULL || strcmp(tab[1], "Anonymous") != 0){
        dprintf(clt->sockfd, "530 User name wrong.\n");
        return;
    }
    dprintf(clt->sockfd, "331 User name okay, need password.\n");
    clt->username = strdup(tab[1]);
}

void display_help(char **tab, element *clt)
{
    static const char *help[14] = {"USER <SP> <username> <CRLF>   : Specify user for authentic\
ation", "PASS <SP> <password> <CRLF>   : Specify password for authentication", "CWD <SP> <pathname> <CRLF>   : Change working directory", \
"CDUP <CRLF>   : Change working directory to parent directory", "QUIT <CRLF>   : Disconnection", "DELE <SP> <pathname> <CRLF>   : Delete file on the server", \
"PWD  <CRLF>   : Print working directory", "PASV <CRLF>   : Enable 'passive' mode for data transfer", "PORT <SP> <host-port> <CRLF>   : Enable 'active' mode for data transfer", \
"HELP [<SP> <string>] <CRLF>   : List available commands", "NOOP <CRLF>   : Do nothing", "RETR <SP> <pathname> <CRLF>   : Download file from server to client", \
"STOR <SP> <pathname> <CRLF>   : Upload file from client to server", "214 LIST [<SP> <pathname>] <CRLF>   : List files in the current working directory"};

    for (int i = 0; i < 14; i++){
        if (tab[1] == NULL || strstr(help[i], tab[1]) != NULL)
            dprintf(clt->sockfd, "214 %s\n", help[i]);
    }
}

void noop(char **tab, element *clt)
{
	tab = tab;
	if (clt->log <= 0)
		dprintf(clt->sockfd, "530 Please login with USER and PASS.\n");
	else
		dprintf(clt->sockfd, "200 NOOP.\n");
}

void delete(char **tab, element *clt)
{
	if (clt->log != 1) {
		dprintf(clt->sockfd, "530 Please login with USER and PASS.\n");
        return;
	}
    if (tab[1] && remove(tab[1]) == 0)
		dprintf(clt->sockfd, "250 file deleted\n");
	else
		dprintf(clt->sockfd, "550 file not found\n");
}