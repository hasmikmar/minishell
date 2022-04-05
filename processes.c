/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:16:58 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/05 17:21:17 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//cat /dev/urandom | head -10

void	child_p(int num)
{
	char	**env;
	//stugel redirection ka te hce, ete ka dra het dup anel, ete che pipei, verjin commandy stdouti het dup anel
	// if (dup2(fd[1], 1) == -1)
	// printf("Can't duplicate\n");
	env = list_to_arr();
	if (!g_g.cmds[1].name && !check_builtin(g_g.cmds[num].name))
	{
		if ((dup2(g_g.cmds[num].out, 1) == -1)
			&& (dup2(g_g.cmds[num].in, 0) == -1))
			printf("Error...Can't duplicate\n");
	}
	if (g_g.cmds[num].args[0][0] == '/')
		execve(g_g.cmds[num].name, g_g.cmds[num].args, env);
	else
		is_builtins(num, env);
}
