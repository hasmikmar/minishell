/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:57:50 by akhachat          #+#    #+#             */
/*   Updated: 2022/03/03 19:57:52 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
			if (str[i] == '\0')
				ft_error("Quotation error", 0);
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			printf("%c\n", str[i]);
			if (str[i] == '\0')
				ft_error("Quotation error", 0);
		}
		i++;
	}
}
