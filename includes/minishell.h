/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:17:59 by ataji             #+#    #+#             */
/*   Updated: 2022/11/22 13:10:45 by kfaouzi          ###   ########.fr       */
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
# include"parsing.h"
# include<fcntl.h>
# include<stdbool.h>
# include<signal.h>
# include<paths.h>
# include<dirent.h>

# define W 1
# define R 0

typedef struct s_norm_exp
{
	int		i;	
	int		k;
	int		c;
	char	**tab;	
}	t_norm_exp;

typedef struct s_norm
{
	int		i;	
	int		k;
	int		c;
	char	**tab;	
}	t_norm;

typedef struct s_red_exe
{
	int	k;
	int	j;
	int	c;
	int	check__;
}	t_red_exe;

/*********************************************************/
/******************* builtin_commands ********************/
/*********************************************************/

int			builtin_commands(t_execlst *el);
int			echo_cmd(t_execlst *el, int k, int c, int check__);
int			pwd_cmd(t_execlst *el);
int			cd_cmd(char **line);
int			env_cmd(t_execlst *el);
int			unset_befor(char *line);
int			check_if_builtin(t_execlst *el);
int			unset_env(char **line);
int			unset_exp(char **line);
void		add_variable(char **line, t_env *dt);
int			exit_cmd(t_execlst *el);
void		mini_unset_env(t_env *tmp, t_env *tmp2);
void		mini_unset_exp(t_env *tmp, t_env *tmp2);
int			mini_echo(t_execlst *el);
int			check_directory(char **line);
void		print_echo(t_execlst *el);

void		print_echo_n(t_execlst *el, int j);
void		write_red_echo(t_execlst *el);
void		write_red_echo_n(t_execlst *el, int k);
int			red_echo(t_execlst *el);
int			echo_heredc(t_execlst *el, int k, int c, int check__);
int			red_out_echo(t_execlst *el, int k, int c, int check__);

/*********************************************************/
/********************** get_export ***********************/
/*********************************************************/

//sort_exp.c
size_t		ft_strlen_exp(const char *str);
char		*ft_substr_exp(char const *s, unsigned int start, size_t len);
void		ft_swap(char **a, char **b);
void		ft_swapint(int *a, int *b);
void		sort_exp(t_env *dt);

//get_exp.c
/********************** exp_empty ************************/
void		get_exp_empty(t_env *dt);
/*********************************************************/
t_env		*init_explst(void);
void		get_exp(t_env *dt);

//get_exp_utils4.c
int			ft_strcmp_exp(const char *s1, const char *s2);
int			count_words_exp(const char *str, char c);

//get_exp_utils3.c
int			ft_check_plus_exp(char *line);
void		ft_replace_value_variable_exp(t_env *dt, char *var, char *val);
int			ft_replace_value_exp(t_env *dt, char *var, char *val);
int			plus_cmp_exp(char *var);

//get_exp_utils2.c
char		**ft_freeing_exp(char **tab);
char		*get_var_name_exp(const char *s, int index);
char		*get_var_value_exp(const char *s, int index);
char		**set_words_exp(char const *s, char c);
char		**ft_split_exp(char const *s, char c);

//get_exp_utils.c
void		add_before_with_plus_one(char *var, t_env *dt);
void		add_before_with_plus_exp(char *var, t_env *tmp);
void		ft_concat_plus_exp(t_env *dt, char *line);
char		*ft_strdup_exp(const char *s1);
char		*ft_strjoin_exp(char const *s1, char const *s2);

//ft_split_one.c
int			ft_strcmp_exp_first(const char *s1, const char *s2);
int			count_words_exp_first(const char *str, char c);

//ft_split_exp_first.c
char		**ft_freeing_exp_first(char **tab);
char		*get_var_name_exp_first(const char *s, int index);
char		*get_var_value_exp_first(const char *s, int index);
char		**set_words_exp_first(char const *s, char c);
char		**ft_split_exp_first(char const *s, char c);

//export_cmd.c
int			check_plus_exist_exp(t_env *dt, char *str1);
bool		find_equal_export(char *str);
int			export_cmd(char **line, t_execlst *el);
void		red_export(t_execlst *el, t_env *dt);
void		print_export(t_env *dt, int t);
int			add_var_exp_env(char **line);

//export_cmd_helper3.c
int			find_it_exp(char *line);
int			handle_special_char_exp(char *line);

//export_cmd_helper2.c
void		add_variable_exp(char *line, t_env **dt);
void		add_var_helper(char *line, char **tab, t_env *dt);
void		add_var_helper1(t_env *dt, char **tab);
char		**add_var_helper2(char *line, t_env **dt, char **tab);
int			add_var_helper3(char *line);

//export_cmd_helper.c
int			exist_or_not_exp(char **tab, char *line);
int			check_if_in_export(char *variable);
int			find_equal_exp(char *line);
int			check_if_dollar(char *dollar);
int			special_char(char *line, char **tab);

/*********************************************************/
/************************ get_env ************************/
/*********************************************************/

//get_env.c
/********************** exp_empty ************************/
void		get_env_empty(t_env *dt);
/*********************************************************/
t_env		*init_envlst(void);
void		get_env(t_env *dt);

char		*getenv_from_my_env(char *key);

//get_env_utils3.c
int			ft_strcmp_env(const char *s1, const char *s2);
int			count_words_env(const char *str, char c);
char		*ft_strjoin_env(char const *s1, char const *s2);

//get_env_utils2.c
size_t		ft_strlen_env(const char *str);
char		*ft_strdup_env(const char *s1);
char		*ft_substr_env(char const *s, unsigned int start, size_t len);

//get_env_utils.c
char		**ft_freeing_env(char **tab);
char		*get_var_name_env(const char *s, int index);
char		*get_var_value_env(const char *s, int index);
char		**set_words_env(char const *s, char c);
char		**ft_split_env(char const *s, char c);

//get_env_first.c
int			ft_strcmp_env_first(const char *s1, const char *s2);
int			count_words_env_first(const char *str, char c);

//ft_split_env_first.c
char		**ft_freeing_env_first(char **tab);
char		*get_var_name_env_first(const char *s, int index);
char		*get_var_value_env_first(const char *s, int index);
char		**set_words_env_first(char const *s, char c);
char		**ft_split_env_first(char const *s, char c);

//env_two.c
int			check_plus_exist_env(t_env *dt, char *str1);
int			plus_cmp_env(char *var);
void		add_before_with_plus_two(t_env *dt, char *var);
void		add_before_with_plus_env(char *var, t_env *tmp);

//env_three.c
int			ft_replace_value_env(t_env *dt, char *var, char *val);
void		ft_replace_value_variable_env(t_env *dt, char *var, char *val);
void		ft_concat_plus_env(t_env *dt, char *line);
char		**add_variable_env_one(char *line, t_env **dt, char **tab);

//env_one.c
int			ft_check_plus_env(char *line);
int			find_equal_env(char *line);
int			exist_or_not_env(char **tab, char *line);
bool		find_equal_environment(char *str);
int			add_val_if_not_exist(t_env *dt, char *line, char **tab);

//env_four.c
void		add_variable_env(char *line, t_env **dt);

//env_cmd.c
int			envcmd(t_execlst *el);
void		add_variable_env_two(t_env *dt, char **tab, char *line);
void		add_variable_env_three(t_env *dt, char **tab);
void		redin_env(t_env *tmp);
int			redout_env(t_execlst *el, t_env *tmp);

/*********************************************************/
/********************* exec_commands *********************/
/*********************************************************/

// void	execve_function(t_execlst *el);
void		execve_function(t_execlst *el);
void		cmd(t_execlst *el, int __pipe[2]);
char		*add_path(t_execlst *el);

/*********************************************************/
/******************** other_functions ********************/
/*********************************************************/

// void    get_env(char *line);
// void	path_exec(char **line);
// int    add_befor(char *line);
// t_env *init_envlst(void);
// void	ft_swap(char **s1, char **s2);
int			check_path(char *var, char *p);
char		*join_path(t_execlst *el);
void		preexec(t_execlst *el, int pipe[2]);
void		postexec(t_execlst *el, int pipe[2]);
int			check_if_builtin(t_execlst *el);
void		sort_env(t_env *dt);
char		*creat_execution_file(char *path);
// void	sort_env(char **line);
// int     check_export(char *line);
t_env		*init_envlst(void);
int			ft_check_plus(char *line);
void		ft_concat_plus(t_env *dt, char *line);
int			ft_red(t_execlst *el, int *dup1, int *dup0);

/*********************************************************/
/************************ errors *************************/
/*********************************************************/

void		print_error_builtin(char *s1, char *s2, int error);
void		print_error(char *s1, char *s2, int error);
int			check_access_file(t_execlst *el);

/*********************************************************/
/************************ garbege ************************/
/*********************************************************/

void		add_to_garbege(t_gc **data, t_gc *new);
void		add_to_garbege2(t_exp_env **data, t_exp_env *new);
t_gc		*ft_new_gc(void *data);
t_exp_env	*ft_new_gc2(void *data);
void		*ft_malloc(size_t size);
void		ft_free_inside(void);
void		ft_free_env_exp(void);
void		ft_exit(int ex);

/*********************************************************/
/*********************************************************/
/*********************************************************/

int			check_redir(t_execlst *el);
void		mini_token_and_exec(t_execlst *el);
void		msg_error(char *str);

/*********************************************************/
/************************ garbege ************************/
/*********************************************************/

size_t		my_strlen(const char *s);
char		*my_strdup(const char *s1);
char		*my_substr(char const *s, unsigned int start, size_t len);
char		*my_strjoin(char const *s1, char const *s2);
char		**my_split(char const *s, char c);
int			count_words(const char *str, char c);
int			my_strcmp(const char *s1, const char *s2);
int			my_strlendm(char **tab);
char		*my_strdup1(const char *s1);

#endif
