/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:17:59 by ataji             #+#    #+#             */
/*   Updated: 2022/11/17 10:09:33 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include"readline/history.h"
# include"readline/readline.h"
# include<errno.h>
# include<string.h>
# include"../execution/libft/libft.h"
# include"../includes/parsing.h"
# include<fcntl.h>
# include<stdbool.h>
# include<signal.h>
# include<paths.h>
# include<dirent.h>

# define W 1
# define R 0

/*********************************************************/
/******************* builtin_commands ********************/
/*********************************************************/

int		builtin_commands(t_execlst *el);
int		echo_cmd(t_execlst *el);
int		pwd_cmd(t_execlst *el);
int		cd_cmd(char **line);
int		env_cmd(t_execlst *el);
int		unset_befor(char *line);
int		check_if_builtin(t_execlst *el);
int		unset_env(char **line);
int		unset_exp(char **line);
void	add_variable(char **line, t_env *dt);
void	exit_cmd(void);
void	mini_unset_env(t_env *tmp, t_env *tmp2);
void	mini_unset_exp(t_env *tmp, t_env *tmp2);
int	    mini_echo(t_execlst *el);
int     check_directory(char **line);

/*********************************************************/
/********************** get_export ***********************/
/*********************************************************/

/********************** exp_empty ************************/
void	get_exp_empty(t_env *dt);

size_t	ft_strlen_exp(const char *str);
char	*ft_substr_exp(char const *s, unsigned int start, size_t len);
void	ft_swap(char **a, char **b);
void	ft_swapint(int *a, int *b);
void	sort_exp(t_env *dt);

t_env	*init_explst(void);
void	get_exp(t_env *dt);

int		ft_strcmp_exp(const char *s1, const char *s2);
int		count_words_exp(const char *str, char c);
char	**ft_freeing_exp(char **tab);
char	*get_var_name_exp(const char *s, int index);
char	*get_var_value_exp(const char *s, int index);
char	**set_words_exp(char const *s, char c);
char	**ft_split_exp(char const *s, char c);

int		ft_check_plus_exp(char *line);
int		ft_replace_value_exp(t_env *dt, char *var, char *val);
int		plus_cmp_exp(char *var);
void	ft_replace_value_variable_exp(t_env *dt, char *var, char *val);
void	add_before_with_plus_exp(char *var, t_env *tmp);
void	ft_concat_plus_exp(t_env *dt, char *line);
char	*ft_strdup_exp(const char *s1);
char	*ft_strjoin_exp(char const *s1, char const *s2);

int		exist_or_not_exp(char **tab, char **line);
int		find_equal_exp(char **line);
int		check_if_in_export(char *variable);
int		check_if_dollar(char *dollar);
int		special_char(char *line, char **tab);
int		find_it_exp(char **tab);
int		handle_special_char_exp(char **line);
int		check_plus_exist_exp(t_env *dt, char *str1);
int		export_cmd(char **line, t_execlst *el);
bool	find_equal_export(char *str);
void	add_variable_exp(char **line, t_env *dt);

int		ft_strcmp_exp_first(const char *s1, const char *s2);
int		count_words_exp_first(const char *str, char c);
char	**ft_freeing_exp_first(char **tab);
char	*get_var_name_exp_first(const char *s, int index);
char	*get_var_value_exp_first(const char *s, int index);
char	**set_words_exp_first(char const *s, char c);
char	**ft_split_exp_first(char const *s, char c);

int		check_redir(t_execlst *el);
void	mini_token_and_exec(t_execlst *el);

/*********************************************************/
/************************ get_env ************************/
/*********************************************************/

/********************** exp_empty ************************/

void	get_env_empty(t_env *dt);

int		ft_check_plus_env(char *line);
int		find_equal_env(char **line);
int		exist_or_not_env(char **tab, char **line);
int		ft_replace_value_env(t_env *dt, char *var, char *val);
int		check_plus_exist_env(t_env *dt, char *str1);
int		plus_cmp_env(char *var);
int		env_cmd(t_execlst *el);
void	add_before_with_plus_env(char *var, t_env *tmp);
void	ft_replace_value_variable_env(t_env *dt, char *var, char *val);
void	ft_concat_plus_env(t_env *dt, char *line);
void	add_variable_env(char **line, t_env *dt);
bool	find_equal_environment(char *str);

int		ft_strcmp_env_first(const char *s1, const char *s2);
int		count_words_env_first(const char *str, char c);
char	**ft_freeing_env_first(char **tab);
char	*get_var_name_env_first(const char *s, int index);
char	*get_var_value_env_first(const char *s, int index);
char	**set_words_env_first(char const *s, char c);
char	**ft_split_env_first(char const *s, char c);

int		ft_strcmp_env(const char *s1, const char *s2);
int		count_words_env(const char *str, char c);
char	*ft_strjoin_env(char const *s1, char const *s2);
char	**ft_freeing_env(char **tab);
char	*get_var_name_env(const char *s, int index);
char	*get_var_value_env(const char *s, int index);
char	**set_words_env(char const *s, char c);
char	**ft_split_env(char const *s, char c);

size_t	ft_strlen_env(const char *str);
char	*ft_strdup_env(const char *s1);
char	*ft_substr_env(char const *s, unsigned int start, size_t len);

t_env	*init_envlst(void);
void	get_env(t_env *dt);

/*********************************************************/
/********************* exec_commands *********************/
/*********************************************************/

// void	execve_function(t_execlst *el);
void	execve_function(t_execlst *el);
void	cmd(t_execlst *el, int __pipe[2]);
char	*add_path(t_execlst *el);

/*********************************************************/
/******************** other_functions ********************/
/*********************************************************/

// void    get_env(char *line);
// void	path_exec(char **line);
// int    add_befor(char *line);
// t_env *init_envlst(void);
// void	ft_swap(char **s1, char **s2);
int		check_path(char *var, char *p);
char	*join_path(t_execlst *el);
void	preexec(t_execlst *el, int pipe[2]);
void	postexec(t_execlst *el, int pipe[2]);
int		check_if_builtin(t_execlst *el);
void	sort_env(t_env *dt);
char	*creat_execution_file(char *path);
// void	sort_env(char **line);
// int     check_export(char *line);
t_env	*init_envlst(void);
int		ft_check_plus(char *line);
void	ft_concat_plus(t_env *dt, char *line);
int     ft_red(t_execlst *el, int *dup1, int *dup0);

/*********************************************************/
/************************ errors *************************/
/*********************************************************/

void	print_error_builtin(char *s1, char *s2, int error);
void	print_error(char *s1, char *s2, int error);
int		check_access_file(t_execlst *el, int check_next);

/*********************************************************/
/*********************************************************/
/*********************************************************/

#endif
