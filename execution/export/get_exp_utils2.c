/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exp_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:13:19 by ataji             #+#    #+#             */
/*   Updated: 2022/11/10 17:51:16 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp_exp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	count_words_exp(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*str)
	{
		if (*str != c && count == 0)
		{
			count = 1;
			i++;
		}
		else if (*str == c)
			count = 0;
		str++;
	}
	return (i);
}

char	**ft_freeing_exp(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char *get_var_name_exp(const char *s, int index)
{
	char	*var_name;
	int		i;

	var_name = malloc(index + 1);
	if (!var_name)
		return (NULL);
	i = 0;
	while(i < index)
	{
		var_name[i] = s[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

char *get_var_value_exp(const char *s, int index)
{
	char	*var_value;
	int		j;

	if(s[index] == '\0')
		return(NULL);
	var_value = malloc(ft_strlen_exp(s) - index + 1);
	if(!var_value)
		return (NULL);
	j = 0;
	while(s[index])
	{
		var_value[j] = s[index];
		index++;
		j++;
	}
	var_value[j] = '\0';
	return(var_value);
	
}

char	**set_words_exp(char const *s, char c)
{
	char	**tab;
	int		i;

	tab = malloc(3 * sizeof(char *));
	if(!tab)
		return(NULL);
	i = 0;
	while(s[i] && s[i] != c)
		i++;
	tab[0] = get_var_name_exp(s, i);
	tab[1] = get_var_value_exp(s, i + 1);
	tab[2] = NULL;
	return(tab);
}

char	**ft_split_exp(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = set_words_exp((char *)s, c);
	return (tab);
}
