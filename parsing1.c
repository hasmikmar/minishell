/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmargary <hmargary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:43:33 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/10 14:27:25 by hmargary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_args(char *s, int num, int i)
{
	int		j;

	j = 1;
	g_g.cmds[num].args = malloc(sizeof(char **) * ((ft_strlen(s) / 2) + 1));
	g_g.cmds[num].args[0] = g_g.cmds[num].name;
	while (s[i])
	{
		i = without_spaces(s, i);
		g_g.cmds[num].args[j] = quote_handling(s, &i);
		if (is_space(g_g.cmds[num].args[j]))
			g_g.cmds[num].args[j] = NULL;
		j++;
	}
	g_g.cmds[num].args[j] = NULL;
}
