/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:51:59 by akhachat          #+#    #+#             */
/*   Updated: 2022/03/17 16:37:54 by akhachat         ###   ########.fr       */
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

typedef struct s_cmds
{
	char	*name;
	char	*flag;
	char	**args;
}		t_cmds;

typedef struct s_list
{
	char			*var;         	//variable
	char			*val;			//value of the variable
	int				exp;			//is variable exported or not? boolean value 
	struct s_list	*next;
	struct s_list	*prev;
	int				equal_sign;

}	t_list;

struct s_global
{
	t_cmds	*cmds;
	t_list	*lenv;
}	g_g;

void	ft_error(char *str, int code);
void	start(char **env, char *str);
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
void	ft_unset(char *str);
int		ft_strncmp_quote(const char *s1, const char *s2, size_t n);
void	ft_pwd(void);
void	print_export(void);
int		is_equal_present(const char *str);
char	*without_quotes(char *str);
void	ft_export(char *str);
char	**ft_split_for_export(char const *s);
char	**free_matrix(char **s);
void	check_quotes(char *str);
int		count_list_elements(void);
void	fill_env(char **env);
char	**list_to_arr(void);
t_list	*find_element(char *var_name);
void	check_oldpwd(char *value);
void	ft_cd(char *p);
int 	is_builtins(char *cmd);


#endif
