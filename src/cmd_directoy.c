/*
** EPITECH PROJECT, 2019
** myftp
** File description:
** cmd about direcory
*/
#include "my.h"

void pwd(char **tab, element *clt)
{
    tab = tab;
    if (clt->log != 1) {
		dprintf(clt->sockfd, "530 Please login with USER and PASS.\n");
	    return;
    }
    dprintf(clt->sockfd, "257 \"%s\"\n", clt->pwd);
}

void cwd(char **tab, element *clt)
{
    if (clt->log != 1) {
		dprintf(clt->sockfd, "530 Please login with USER and PASS.\n");
	    return;
    }
    if (tab[1] == NULL || chdir(tab[1]) == -1){
        dprintf(clt->sockfd, "501 Syntax error in parameters or arguments.\n");
        return;
    }
    getcwd(clt->pwd, sizeof(clt->pwd));
    dprintf(clt->sockfd, "250 Moved to %s\n", clt->pwd);
}

void cdup(char **tab, element *clt)
{
    tab = tab;
    if (clt->log != 1) {
		dprintf(clt->sockfd, "530 Please login with USER and PASS.\n");
	    return;
    }
    if (chdir(clt->root) == -1){
        dprintf(clt->sockfd, "550 Error can't go to root.\n");
        return;
    }
    getcwd(clt->pwd, sizeof(clt->pwd));
    dprintf(clt->sockfd, "200 Moved to %s\n", clt->pwd);
}