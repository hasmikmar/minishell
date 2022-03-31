/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tapetros <tapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:43:33 by tapetros          #+#    #+#             */
/*   Updated: 2022/03/27 16:35:55 by tapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_args(char *s, int num, int i)
{
	int	j;

	j = 0;
	g_g.cmds[num].args = malloc(sizeof(char **) * ((ft_strlen(s) / 2) + 1));
	(void)num;
	while (s[i])
	{
		i = without_spaces(s, i);
		g_g.cmds[num].args[j] = quote_handling(s, &i);
		// printf("%s\n", g_g.cmds[num].args[j]);
		j++;
	}
	g_g.cmds[num].args[j] = NULL;
	is_builtins(num);
}
