/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:52:59 by akhachat          #+#    #+#             */
/*   Updated: 2022/03/16 15:40:12 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rows_amount(char **spl)
{
	int	i;

	i = 0 ;
	while (spl[i])
		++i;
	return (i);
}

void	fill_env(char **env)
{
	int		i;
	char	**str;
	t_list	*tmp;

	i = 0;
	while (env[i])
	{
		str = ft_split(env[i], '=');
		tmp = ft_lstnew(str[0], str[1], 1);
		ft_lstadd_front(&g_g.lenv, tmp);
		i++;
	}
	free(str);
}

void	start(char **env, char *str)
{
	int		len;
	char	**spl;

	fill_env(env);
	// printf("--------------------------------------------export\n");
	ft_export(str);
	// printf("--------------------------------------------env\n");
	// print_list();
	// print_export();
	// ft_unset("\"PATH\" PWD");
	// printf("--------------------------------------------\n");
	// print_list();
	spl = ft_split(str, '|');
	len = rows_amount(spl);
	g_g.cmds = malloc(sizeof (t_cmds) * len);
	if (!g_g.cmds)
		ft_error("Can't malloc struct\n", 0);
}
