/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:26:12 by kfaouzi           #+#    #+#             */
/*   Updated: 2022/11/19 10:26:20 by kfaouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"

int	sizehrdc(char *file)
{
	int	i;
	int	sz;

	sz = 0;
	i = -1;
	while (file[++i])
	{
		if (file[i] == '\'')
			while (file[++i] && file[i] != '\'')
				sz++;
		else if (file[i] && file[i] == '\"')
			while (file[++i] && file[i] != '\"')
				sz++;
		else
		{
			sz++;
			while (file[++i] && file[i] != '\"' && file[i] != '\'')
				sz++;
			if (!file[i] || file[i] == '\"' || file[i] == '\'')
				i--;
		}
	}
	return (sz);
}

char	*expand_hrdc(int i, int j, char *name_file, char *file)
{
	i = sizehrdc(file);
	name_file = ft_malloc(i + 1);
	i = -1;
	while (file[++i])
	{
		if (file[i] == '\'')
			while (file[++i] && file[i] != '\'')
				name_file[j++] = file[i];
		else if (file[i] == '\"')
			while (file[++i] && file[i] != '\"')
				name_file[j++] = file[i];
		else
		{
			name_file[j++] = file[i];
			while (file[++i] && file[i] != '\'' && file[i] != '\"')
				name_file[j++] = file[i];
			if (!file[i] || file[i] == '\"' || file[i] == '\'')
				i--;
		}
	}
	return (name_file[j] = '\0', name_file);
}

int	ft_open(t_enum type, char **file)
{
	*file = _expander(*file, 0);
	if (type == REDOUT)
		return (open(*file, O_WRONLY | O_TRUNC | O_CREAT, 0644));
	else if (type == REDIN)
		return (open(*file, O_RDONLY));
	else
		return (open(*file, O_APPEND | O_CREAT | O_RDWR, 0644));
}

int	__check_open_error(int fd, int __errno)
{
	if (fd == -1)
		return (__errno);
	return (0);
}

void	put_in_fd(char *del, int fd, int nbdel)
{
	if (nbdel)
	{
		del = expander_hrdc(del);
		ft_putstr_fd(del, fd);
	}
	else
		ft_putstr_fd(del, fd);
	write(fd, "\n", 1);
}
