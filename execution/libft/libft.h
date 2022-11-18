/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:05:43 by ataji             #+#    #+#             */
/*   Updated: 2022/11/18 12:00:31 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include<stdlib.h>
# include<unistd.h>
# include<stdio.h>
#include "../../includes/parsing.h"
#include "../../includes/minishell.h"

int		my_atoi(const char *str);
void	my_bzero(void *s, size_t n);
void	*my_calloc(size_t count, size_t size);
int		my_isalpha(int c);
int		my_isdigit(int c);
int		my_isalnum(int c);
int		my_isascii(int c);
int		my_isprint(int c);
size_t	my_strlen(const char *s);
void	*my_memset(void *b, int c, size_t len);
void	*my_memcpy(void *dst, const void *src, size_t n);
void	*my_memmove(void *dst, const void *src, size_t len);
size_t	my_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	my_strlcat(char *dst, const char *src, size_t dstsize);
int		my_toupper(int c);
int		my_tolower(int c);
char	*my_strchr(const char *s, int c);
char	*my_strrchr(const char *s, int c);
int		my_strncmp(const char *s1, const char *s2, size_t n);
void	*my_memchr(const void *s, int c, size_t n);
int		my_memcmp(const void *s1, const void *s2, size_t n);
char	*my_strnstr(const char *haystack, const char *needle, size_t len);
char	*my_strdup(const char *s1);
char	*my_substr(char const *s, unsigned int start, size_t len);
char	*my_strjoin(char const *s1, char const *s2);
char	*my_strtrim(char const *s1, char const *set);
char	**my_split(char const *s, char c);
char	*my_itoa(int n);
char	*my_strmapi(char const *s, char (*f)(unsigned int, char));
void	my_striteri(char *s, void (*f)(unsigned int, char*));
void	my_putchar_fd(char c, int fd);
void	my_putstr_fd(char *s, int fd);
void	my_putendl_fd(char *s, int fd);
void	my_putnbr_fd(int n, int fd);
int		count_words(const char *str, char c);
int		my_strcmp(const char *s1, const char *s2);
int		my_strlendm(char **tab);
#endif
