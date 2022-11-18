/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:21:12 by ataji             #+#    #+#             */
/*   Updated: 2022/11/18 12:00:11 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

void	*my_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	s;

	s = count * size;
	ptr = ft_malloc(s);
	my_bzero(ptr, s);
	return (ptr);
}
