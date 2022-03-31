/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   early_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tapetros <tapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:39:02 by tapetros          #+#    #+#             */
/*   Updated: 2022/03/17 20:21:21 by tapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] && str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i])
				i++;
			if (str[i] == '\0')
				return (0);
		}
		else if (str[i] == '\"' && str[i])
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (str[i] == '\0')
				return (0);
		}
	}
	return (1);
}

int	check_sem_and_pipe(char *str)
{
	int		i;
	char	*s;

	s = ft_strtrim(str, " ");
	i = 0;
	if (s[i] == '|' || s[ft_strlen(s) - 1] == '|')
	{
		free(s);
		return (0);
	}
	while (s[i])
	{
		if (s[i] == ';' || s[i] == '\\')
		{
			free(s);
			return (0);
		}
		i++;
	}
	free(s);
	return (1);
}

int	check_red(char *str)
{
	int		i;
	char	*s;

	i = 0;
	s = without_quotes(str);
	while (s[i])
	{
		if ((s[i] == '>' && s[i + 1] == '<')
			|| (s[i + 1] == '>' && s[i] == '<'))
		{
			free(s);
			return (0);
		}
		i++;
	}
	free(s);
	return (1);
}
