/*
** EPITECH PROJECT, 2019
** myftp
** File description:
** cmd gestion
*/

#include "my.h"

void quit(char **tab, element *clt)
{
    tab = tab;
    dprintf(clt->sockfd, "221 Loged out\n");
    printf("Deconnection from %s:%d\n", inet_ntoa(clt->serv_client.sin_addr), \
htons(clt->serv_client.sin_port));
    clt->log = -1;
    close(clt->sockfd);
}

void pasv(char **tab, element *clt)
{
    tab = tab;
    if (clt->log != 1) {
		dprintf(clt->sockfd, "530 Please login with USER and PASS.\n");
	    return;
    }
    if (clt->mode == 1){
        dprintf(clt->sockfd, "540 Passive mode already activated.\n");
	    return;
    }
    clt->mode = 1;
    dprintf(clt->sockfd, "227 Enable passive mode for data transfer.\n");
}

void port(char **tab, element *clt)
{
    int port;

    if (clt->log != 1) {
		dprintf(clt->sockfd, "530 Please login with USER and PASS.\n");
	    return;
    }
    if (tab[1] == NULL || atoi(tab[1]) <= 0){
        dprintf(clt->sockfd, "540 Wrong port.\n");
	    return;
    }
    port = atoi(tab[1]);
    if (clt->mode == port){
        dprintf(clt->sockfd, "540 This port is already used.\n");
	    return;
    }
    clt->mode = port;
    dprintf(clt->sockfd, "200 Enable active mode for data transfer with port %s.\n", tab[1]);
}

void do_cmd(char **tab, element *clt)
{
	static const char *function[11] = {"HELP", "USER", "PASS", "DELE", "NOOP", "PWD", "CWD", "CDUP", "QUIT", "PASV", "PORT"};
    static void (*func[11])(char **tab, element *clt) = {&display_help, &user, &password, &delete, &noop, &pwd, &cwd, &cdup, &quit, &pasv, &port};

	for (int i = 0; i < 11 ; i++){
		if (strcasecmp(tab[0], function[i]) == 0) {
            (*func[i])(tab, clt);
            return;
		}
	}
    dprintf(clt->sockfd, "500 Unknow command.\n");
}   