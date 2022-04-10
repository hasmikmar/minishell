/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmargary <hmargary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:37:01 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/10 14:28:03 by hmargary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	connect_pipes(int i)
{
	int	fd[2];

	if (pipe(fd) == -1)
		printf("Error while creating a pipe\n");
	if (g_g.cmds[i - 1].out != 1)
		close(fd[1]);
	else
		g_g.cmds[i - 1].out = fd[1];
	if (g_g.cmds[i].in != 0)
		close(fd[0]);
	else
		g_g.cmds[i].in = fd[0];
}

int	get_index(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], "PATH", 4)))
			return (i);
		++i;
	}
	return (0);
}

char	*env_path(char **env, char *ar)
{
	char	**path;
	int		j;
	char	*final_path;
	int		fd;
	char	*cur;

	path = ft_split(env[get_index(env)] + 5, ':');	
	j = -1;
	while (path[++j])
	{
		cur = ft_strjoin(path[j], "/");
		final_path = ft_strjoin(cur, ar);
		fd = open(final_path, O_RDONLY);
		if (fd > -1)
		{
			close(fd);
			free(cur);
			return (final_path);
		}
		free(cur);
	}
	return (final_path);
}
