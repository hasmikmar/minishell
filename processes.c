/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmargary <hmargary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:16:58 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/10 14:29:17 by hmargary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//cat /dev/urandom | head -10

void	fd_close(void)
{
	int	i;

	i = 0;
	while (i < g_g.pipam)
	{
		if (g_g.cmds[i].out != 1)
			close(g_g.cmds[i].out);
		if (g_g.cmds[i].in != 0)
			close(g_g.cmds[i].in);
		i++;
	}
}

void	child_process(int num)
{
	char	**env;
	
	env = list_to_arr();
	if (!g_g.cmds[1].name || !check_builtin(g_g.cmds[num].name))
	{
		if ((dup2(g_g.cmds[num].out, 1) == -1)
			|| (dup2(g_g.cmds[num].in, 0) == -1))
			printf("Error...Can't duplicate\n");
		fd_close();
		g_g.cmds[num].out = 1;
	}
	if (g_g.cmds[num].args[0][0] == '.' || g_g.cmds[num].args[0][0] == '/')
	{
		execve(g_g.cmds[num].name, g_g.cmds[num].args, env);
		printf("%s: command not found\n", g_g.cmds[num].args[0]);
		ft_error("", 0);
	}
	else
		is_builtins(num, env);
}
