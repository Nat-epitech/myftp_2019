/*
** EPITECH PROJECT, 2018
** str_to_wordtab
** File description:
** some tools
*/

#include "my.h"

void test_space(char *line, element *tmp)
{
    char **test;
    int j = 0;

    test = str_wordtab(line, "\t\n\r");
    if (test != NULL){
        for (j = 0; test[0][j] != '\0' && test[0][j] == ' '; j++);
        if (test[0][j] == '\0')
        dprintf(tmp->sockfd, "500 Unknow command.\n");
        for (int i = 0; test[i] != NULL; free(test[i++]));
        free (test);
    }
}

char **str_wordtab(char *str, char *tok)
{
    int i = 0;
    char **tab = malloc(sizeof(char *));
    char *token = strtok(str, tok);

    if (!str || !tab || !token)
        return (NULL);
    while (token != NULL) {
        tab[i++] = strdup(token);
        tab = realloc(tab, (sizeof(char *) * (i + 1)));
        token = strtok(NULL, tok);
    }
    tab[i] = token;
    free(token);
    return (tab);
}

char *get_next_line(const int fd)
{
    char save[4 + 2];
    int	taille = 1;
    int	readd = 1;
    int	comp = 0;
    char *ret = malloc(sizeof(char) * 100);

    while (readd != 0 && save[taille] != '\n') {
        if (readd <= taille) {
            readd = read(fd, save, 4);
            taille = 0;
        }
        while (readd > taille && save[taille] != '\n')
            ret[comp++] = save[taille++];
    }
    if (comp == 0 && readd == 0)
        return (NULL);
    ret[comp] = '\0';
    return (ret);
}