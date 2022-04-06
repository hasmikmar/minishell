/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:43:33 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/05 19:18:27 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_args(char *s, int num, int i)
{
	int		j;

	j = 1;
	g_g.cmds[num].args = malloc(sizeof(char **) * ((ft_strlen(s) / 2) + 1));
	(void)num;
	g_g.cmds[num].args[0] = g_g.cmds[num].name;
	while (s[i])
	{
		i = without_spaces(s, i);
		g_g.cmds[num].args[j] = quote_handling(s, &i);
		// printf("%s\n", g_g.cmds[num].args[j]);
		j++;
	}
	g_g.cmds[num].args[j] = NULL;
}
