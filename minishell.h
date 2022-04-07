/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:51:59 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/07 19:46:13 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <termios.h>

typedef struct s_cmds
{
	char	*name;
	int		file_fd;
	char	*file;
	int		in;
	int		out;
	char	red;
	int		lvl;
	char	**args;
	char	*str_arg;
}		t_cmds;

typedef struct s_list
{
	char			*var;
	char			*val;
	int				exp;
	struct s_list	*next;
	struct s_list	*prev;
	int				equal_sign;

}	t_list;

typedef struct s_exp
{
	char	**spl;
	int		i;
	int		len;
	t_list	*tmp;
	char	**s;
	int		flag;
	int		flag1;
}			t_exp;

struct s_global
{
	t_cmds	*cmds;
	t_list	*lenv;
	t_exp	*e;
	int		pipam;
}	g_g;

void	ft_error(char *str, int code);
void	start(char *str);
int		ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_exit(int code);
void	ft_atoi_exit(char *str);
void	ft_atoi_exit_1(char *str);
void	ft_atoi_exit_2(char *str, int i, int num, int min);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strchr(const char *s, int c);
t_list	*ft_lstnew(char *var_inf, char *val_inf, int is_exp);
void	ft_lstadd_front(t_list **lst, t_list *neww);
void	ft_lstdel(t_list **lst, t_list *del);
void	print_list(void);
void	ft_unset(char **args);
int		ft_strncmp_quote(const char *s1, const char *s2);
void	ft_pwd(void);
void	print_export(void);
int		is_equal_present(const char *str);
char	*without_quotes(char *str);
void	ft_export(char **args);
char	**ft_split_for_export(char const *s);
char	**free_matrix(char **s);
int		check_quotes(char *str);
int		count_list_elements(void);
void	fill_env(char **env);
char	**list_to_arr(void);
t_list	*find_element(char *var_name);
void	check_oldpwd(char *value);
void	ft_cd(char *p);
int		ft_echo(char **args);
void	parsing(char *s, int num);
char	*quote_handling(char *s, int *i);
char	*quote_checker(char *s, int *i, char c);
void	parse_args(char *s, int num, int i);
int		without_spaces(char *s, int i);
int		is_builtins(int num, char **env);
int		check_red(char *str);
int		check_sem_and_pipe(char *str);
int		is_space(char *str);
void	equal_handling(int num);
void	sig_init(void);
char	*env_path(char **env, char *ar);
int		rows_amount(char **spl);
void	child_p(int num);
void	sig_default(void);
void	sig_ignore(void);
int		check_builtin(char *s);
void	connect_pipes(int num);
void	fd_close(void);

#endif
