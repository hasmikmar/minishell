/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:37:01 by akhachat          #+#    #+#             */
/*   Updated: 2022/03/05 16:37:11 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
