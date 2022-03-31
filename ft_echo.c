/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tapetros <tapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:58:29 by tapetros          #+#    #+#             */
/*   Updated: 2022/03/28 18:59:52 by tapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_with_n(char *args)
{
	int	i;

	i = 1;
	if (ft_strlen(args) < 2 || args[0] != '-' || args[1] != 'n')
		return (0);
	while (args[i])
	{
		if (args[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	flag;
	int	i;

	i = 0;
	while (args[i] && is_with_n(args[i]))
		i++;
	if (i != 0)
		flag = 1;
	else
		flag = 0;
	if (!args[i])
	{
		if (!flag)
			printf("\n");
		return (0);
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[++i])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	return (0);
}
