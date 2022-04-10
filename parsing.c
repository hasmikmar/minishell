/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmargary <hmargary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:43:33 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/10 14:25:52 by hmargary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*dollar_sign(char *s, int *i)
{
	char	*str;
	int		j;
	t_list	*tmp;

	j = 0;
	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	(*i)++;
	while (s[*i] != ' ' && s[*i] != '\0' && s[*i] != '\'' && s[*i] != '\"')
	{
		str[j] = s[*i];
		j++;
		(*i)++;
	}
	(*i)--;
	str[j] = '\0';
	g_g.dollar_len = ft_strlen(str);
	tmp = find_element(str);
	// free(str);
	if (tmp == NULL)
		return (NULL);
	return (tmp->val);
}

//OPEN FILE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int	parse_file(char *s, int i, int num)
{
	int	fd;

	i = without_spaces(s, i);
	g_g.cmds[num].file = quote_handling(s, &i);
	/*
	First of all you cannot open all the files in the samewaybecause files with specific notations need to be opened like this
	if redirection > ....  fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644) => cmd.out = fd
	if redirection >> .... fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644) => cmd.out = fd
	if redirection < ....  fd = open(file, O_CREAT | O_RDONLY, 0644) => cmd.in = fd
	*/
	fd = open(g_g.cmds[num].file, O_CREAT);
	close(fd);
	while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
		i++;
	return (i);
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

	if (is_space(s))
		return ;
	g_g.dollar_len = 0;
	parse_redirects(s, num);
	g_g.cmds[num].in = 0;
	g_g.cmds[num].out = 1;
	if (num)
		connect_pipes(num);
	len = 0;
	buf = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!buf)
		ft_error("Can't malloc", 0);
	g_g.cmds[num].name = "";
	i = without_spaces(s, 0);
	len = i;
	g_g.cmds[num].name = quote_handling(s, &i);
	g_g.cmds->str_arg = ft_strtrim(s, " ");
	parse_args(s, num, i);
}
