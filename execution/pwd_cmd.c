// #include "minishell.h"
#include "../includes/minishell.h"

int	pwd_cmd(t_execlst *el)
{
	int j;
	char cwd[256];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("error in pwd\n");
		return (0);
	}
	if (el->red && el->red->fd)
	{
        j = 0;
        while (cwd[j])
        {
            write (el->red->fd, &cwd[j], 1);
            j++;
        }
        write (el->red->fd, "\n", 1);
	}
	else
		printf("%s\n", cwd);
	return (1);
}
