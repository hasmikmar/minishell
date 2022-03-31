/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal_sign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tapetros <tapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:34:25 by tapetros          #+#    #+#             */
/*   Updated: 2022/03/28 16:36:43 by tapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	equal_handling2(char **s)
{
	t_list	*tmp;

	if (s[1])
		tmp = ft_lstnew(without_quotes(s[0]),
				without_quotes(s[1]), 0);
	else
		tmp = ft_lstnew(without_quotes(s[0]),
				NULL, 0);
	tmp->equal_sign = 1;
	ft_lstadd_front(&g_g.lenv, tmp);
	free(s[0]);
	free(s[1]);
}

void	equal_handling1(char **s)
{
	t_list	*tmp;
	int		flag;

	flag = 0;
	tmp = g_g.lenv;
	while (tmp)
	{
		if (!ft_strncmp_quote(s[0], tmp->var))
		{
			if (s[1])
			{
				tmp->val = without_quotes(s[1]);
				tmp->equal_sign = 0;
			}
			else
				tmp->equal_sign = 1;
			free(s[1]);
			free(s[0]);
			flag = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (!flag)
		equal_handling2(s);
}

void	equal_handling(int num)
{
	int		i;
	char	**s;

	i = 0;
	while (g_g.cmds[num].args[i])
	{
		if (!is_equal_present(g_g.cmds[num].args[i]))
		{
			printf("%s: command not found\n", g_g.cmds[num].args[i]);
			return ;
		}
		i++;
	}
	s = ft_split_for_export(g_g.cmds[num].name);
	equal_handling1(s);
	i = 0;
	while (g_g.cmds[num].args[i])
	{
		s = ft_split_for_export(g_g.cmds[num].args[i]);
		equal_handling1(s);
		i++;
	}
}
