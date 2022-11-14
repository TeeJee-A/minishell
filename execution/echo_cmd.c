// #include "minishell.h"
#include "../includes/minishell.h"

int    echo_heredc(t_execlst *el)
{
    int     i;
    int     j;
    int     n;
    t_red   *red;

    red = el->red;
    n = 1;
    while (el->cmd[n] && !ft_strcmp(el->cmd[n], "-n"))
        n++;
    i = n;
    while (el->cmd[i])
    {
        j = 0;
        while (el->cmd[i][j])
        {
            write(1, &el->cmd[i][j], 1);
            j++;
        }
        i++;
        if (el->cmd[i])
            write(1, " ", 1);
    }
    if (n == 1)
        write(1, "\n", 1);
    return (1);
}

int    echo_cmd(t_execlst *el)
{
    int     i;
    int     j;
    int     n;
    int     m;
    int     k;
    t_red   *red;

    red = el->red;
    n = 1;
    m = 0;
    if (red && red->fd)
    {
        while (el->cmd[n] && !ft_strcmp(el->cmd[n], "-n"))
            n++;
        i = n;
        if (red->type == HEREDC || red->type == REDIN)
        {
            echo_heredc(el);
            return (1);
        }
        while (el->cmd[i])
        {
            j = 0;
            while (el->cmd[i][j])
                write(red->fd, &el->cmd[i][j++], 1);
            i++;
            if (el->cmd[i])
                write(red->fd, " ", 1);
        }
        if (n == 1)
            write(red->fd, "\n", 1);
        return (1);
    }
    k = 1;
    if (!(ft_strcmp(el->cmd[k], "-n")))
    {
        while (el->cmd[k] && !ft_strcmp(el->cmd[k], "-n"))
            k++;
        if (el->cmd && el->cmd[2] == NULL)
            return (1);
        i = k;
        while (el->cmd[i])
        {
            if (!(el->cmd[i + 1]))
            {
                printf("%s", el->cmd[i]);
                return (1);
            }
            printf("%s ", el->cmd[i]);
            i++;
        }
    }
    else
    {
        i = 1;
        while (el->cmd[i])
        {
            printf("%s ", el->cmd[i]);
            i++;
        }
        printf("\n");
    }
    return (1);
}
