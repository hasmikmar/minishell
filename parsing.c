/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tapetros <tapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:43:33 by tapetros          #+#    #+#             */
/*   Updated: 2022/03/30 13:57:42 by tapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	is_env(char **s)
// {
// 	int	i;

// 	i = 0;
// 	while ((*s) && (*s)[i])
// 	{
// 		if ((*s)[i] == '\'' && is_quote(s, &i))
// 			return ;
// 		if ((*s)[i] && (*s)[i] == '\\')
// 		{

// 		}
// 	}
// }

void	env_free(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
		free(s[i++]);
	free(s);
}

int	without_spaces(char *s, int i)
{
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	return (i);
}

// int	name_check(char *s, char c)
// {
// 	int		i;
// 	int		j;
// 	char	q;

// 	i = -1;
// 	j = 1;
// 	while (s[++i])
// 	{
// 		if (s[i] == '\\' && (s[i + 1] == '\'' || s[i + 1] == '"'
// 				|| s[i + 1] == '\\' || s[i + 1] == c))
// 			i++;
// 		else if (s[i] == c)
// 			j++;
// 		else if (s[i] && (s[i] == '"' || s[i] == '\''))
// 		{
// 			q = s[i++];
// 			while (s[i] && s[i] != q)
// 			{
// 				if (s[i] == '\\' && (s[i] + 1 == q || s[i] + 1 == '\\')
// 					&& q == '"')
// 					i++;
// 				i++;
// 			}
// 		}
// 	}
// 	return (j);
// }

char	*dollar_sign(char *s, int *i)
{
	char	*str;
	int		j;
	t_list	*tmp;

	j = 0;
	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	(*i)++;
	while (s[*i] != ' ' && s[*i] != '\0' && s[*i] != '\'' && s[*i] != '\"')
	{
		str[j] = s[*i];
		j++;
		(*i)++;
	}
	tmp = find_element(str);
	free(str);
	if (tmp == NULL)
		return (NULL);
	return (tmp->val);
}

char	*quote_checker(char *s, int *i, char c)
{
	char	*str;
	int		j;
	char	*tmp;

	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	j = 0;
	(*i)++;
	while (s[*i] != c && s[*i])
	{
		if (s[*i] == '$' && s[*i + 1] != ' ' && s[*i + 1] != '\0' && c != '\'')
		{
			tmp = str;
			if (dollar_sign(s, i) != NULL)
				str = ft_strjoin(tmp, dollar_sign(s, i));
			j = ft_strlen(str);
			while (s[*i] != ' ' && s[*i] != '\0' && s[*i]
				!= '\'' && s[*i] != '\"')
				i++;
		}
		else
		{
			str[j] = s[*i];
			j++;
			(*i)++;
		}
	}
	str[j] = '\0';
	return (str);
}
//OPEN FILE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int	parse_file(char *s, int i, int num)
{
	i = without_spaces(s, i);
	g_g.cmds[num].file = quote_handling(s, &i);
	while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
		i++;
	return (i);
}

char	*quote_handling(char *s, int *i)
{
	int		len;
	char	*buf;
	char	*res;

	len = 0;
	buf = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!buf)
		ft_error("Can't malloc", 0);
	while (s[*i] != ' ' && s[*i] && s[*i] != '>' && s[*i] != '<')
	{
		res = buf;
		if (s[*i] == '$' && s[*i + 1] != ' ' && s[*i + 1] != '\0')
		{
			if (dollar_sign(s, i) != NULL)
				buf = ft_strjoin(res, dollar_sign(s, i));
			len = ft_strlen(buf);
		}
		else if (s[*i] == '\"')
		{
			buf = ft_strjoin(res, quote_checker(s, i, '\"'));
			len = ft_strlen(buf);
		}
		else if (s[*i] == '\'')
		{
			buf = ft_strjoin(res, quote_checker(s, i, '\''));
			len = ft_strlen(buf);
		}
		else
		{
			buf[len] = s[*i];
			len++;
		}
		(*i)++;
	}
	buf[len] = '\0';
	return (buf);
}

void	parse_redirects(char *s, int num)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
		{
			if (s[i] == '>')
				g_g.cmds[num].red = 'o';
			else
				g_g.cmds[num].red = 'i';
			s[i] = ' ';
			i++;
			if (s[i] == '>' || s[i] == '<')
			{
				g_g.cmds[num].lvl = 2;
				s[i] = ' ';
				i++;
			}
			else
				g_g.cmds[num].lvl = 1;
			j = i;
			i = parse_file(s, i, num);
			while (j != i)
			{
				s[j] = ' ';
				j++;
			}
		}
		else
			i++;
	}
}

void	parsing(char *s, int num)
{
	int		i;
	char	*buf;
	int		len;
	int		ex;

	parse_redirects(s, num);
	len = 0;
	buf = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!buf)
		ft_error("Can't malloc", 0);
	g_g.cmds[num].name = "";
	i = without_spaces(s, 0);
	len = i;
	g_g.cmds[num].name = quote_handling(s, &i);
	// printf("%s --- %d\n", g_g.cmds[num].name, i);
	// printf("%c --- %d ---- %s\n", g_g.cmds[num].red, g_g.cmds[num].lvl, g_g.cmds[num].file);
	ex = ft_strlen(g_g.cmds[num].name) + len;
	while (len < ex)
	{
		s[len] = ' ';
		len++;
	}
	g_g.cmds->str_arg = ft_strtrim(s, " ");
	parse_args(s, num, i);
}
