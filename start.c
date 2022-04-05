/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:52:59 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/05 17:19:50 by akhachat         ###   ########.fr       */
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

void	start(char *str)
{
	char	**spl;
	int		i;
	pid_t	pid;

	i = -1;
	spl = ft_split(str, '|');
	g_g.pipam = rows_amount(spl);
	g_g.cmds = malloc(sizeof (t_cmds) * g_g.pipam);
	if (!g_g.cmds)
		ft_error("Can't malloc struct\n", 0);
	while (spl[++i])
		parsing(spl[i], i);
	g_g.cmds[i].name = NULL;
	if (g_g.cmds[1].name == NULL && check_builtin(g_g.cmds->name))
		child_p(0);
	i = 0;
	while (i < g_g.pipam)
	{
		pid = fork();
		if (pid == -1)
			printf("Can't fork\n");
		else if (pid == 0)
			child_p(i);
		i++;
	}
	sig_ignore();
	waitpid(-1, 0, 0);
	sig_init();
}
