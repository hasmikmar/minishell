/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmargary <hmargary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:52:59 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/10 14:31:02 by hmargary         ###   ########.fr       */
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

void	starting_processes(void)
{
	pid_t	pid;
	int		i;

	
	if (g_g.cmds[0].name != NULL && g_g.cmds[1].name == NULL
		&& check_builtin(g_g.cmds[0].name) && !is_space(g_g.cmds[0].name))
		child_process(0);
	else
	{
		i = 0;
		while (g_g.cmds[i].name != NULL && i < g_g.pipam
			&& !is_space(g_g.cmds[i].name))
		{
			printf("MTA\n");
			pid = fork();
			if (pid == -1)
				printf("Can't fork\n");
			else if (pid == 0)
			{
				sig_default();
				child_process(i);
				printf("in fork: %d\n", pid);
			}
			i++;
		}
		fd_close();
		sig_ignore();
		int j = 0;
		while (j++ < g_g.pipam)
		{
			printf("waiting\n");
			wait(NULL);
		}
		sig_init();
	}
}

void	start(char *str)
{
	char	**spl;
	int		i;

	i = -1;
	spl = ft_split(str, '|');
	g_g.pipam = rows_amount(spl);
	g_g.cmds = malloc(sizeof (t_cmds) * g_g.pipam);
	if (!g_g.cmds)
		ft_error("Can't malloc struct\n", 0);
	while (spl[++i])
		parsing(spl[i], i);
	g_g.cmds[i].name = NULL;
	
	int k = -1;
	
	while (++k < g_g.pipam)
	{
		int l = 0;
		while (g_g.cmds[k].args[l])
			printf("cmd: %d, args: %s\n", k, g_g.cmds[k].args[l++]);	
	}
	starting_processes();
}
