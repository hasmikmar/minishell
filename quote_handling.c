/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:55:52 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/09 17:53:47 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*without_quotes(char *str)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		ft_error("Can't malloc\n", 0);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

char	*quote_checker(char *s, int *i, char c)
{
	char	*str;
	int		j;
	char	*tmp;
	char	*ret;

	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	j = 0;
	(*i)++;
	while (s[*i] != c && s[*i])
	{
		if (s[*i] == '$' && s[*i + 1] != ' ' && s[*i + 1] != '\0' && c != '\'')
		{	
			tmp = str;
			ret = dollar_sign(s, i);
			if (ret != NULL)
				str = ft_strjoin(tmp, ret);
			else
				return ("");
			j = ft_strlen(str);
			while (s[*i] != ' ' && s[*i] != '\0' && s[*i]
				!= '\'' && s[*i] != '\"')
				(*i)++;
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

char	*quote_handling(char *s, int *i)
{
	int		len;
	char	*buf;
	char	*res;
	char	*ret;

	len = 0;
	buf = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!buf)
		ft_error("Can't malloc", 0);
	while (s[*i] != ' ' && s[*i] != '\0' && s[*i] != '>' && s[*i] != '<')
	{
		res = buf;
		if (s[*i] == '$' && s[*i + 1] != ' ' && s[*i + 1] != '\0')
		{
			ret = dollar_sign(s, i);
			if (ret != NULL)
				buf = ft_strjoin(res, ret);
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
		else if (s[*i] != '\0')
		{
			buf[len] = s[*i];
			len++;
		}
		(*i)++;
	}
	buf[len] = '\0';
	return (buf);
}
