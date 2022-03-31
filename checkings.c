/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tapetros <tapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:39:02 by tapetros          #+#    #+#             */
/*   Updated: 2022/03/27 18:11:32 by tapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_lower(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] >= 65 && s[i] <= 90)
			s[i] += 32;
		i++;
	}
}

int	is_env_arg(int num)
{
	int	i;

	i = 0;
	while (g_g.cmds[num].args[i])
	{
		to_lower(g_g.cmds[num].args[i]);
		if (ft_strncmp_quote("env",
				g_g.cmds[num].args[i]))
			return (0);
		else
			i++;
	}
	return (1);
}

int	is_space_present(int num)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (g_g.cmds[num].args[i])
	{
		while (g_g.cmds[num].args[i][j])
		{
			if (g_g.cmds[num].args[i][j] == ' ')
				return (0);
			j++;
		}	
		i++;
	}
	return (1);
}

//PROCESSY ARDEN SARQVAC AAA
int	is_builtins(int num)
{
	if (!(ft_strncmp_quote("exit", g_g.cmds[num].name)))
		ft_atoi_exit(g_g.cmds[num].str_arg);
	to_lower(g_g.cmds[num].name);
	if (!(ft_strncmp_quote("echo", g_g.cmds[num].name)))
	{
		if (g_g.cmds[num].args[0] == NULL)
			printf("\n");
		else
			ft_echo(g_g.cmds[num].args);
	}
	else if (!(ft_strncmp_quote("cd", g_g.cmds[num].name)))
		ft_cd(g_g.cmds[num].args[0]);
	else if (!(ft_strncmp_quote("pwd", g_g.cmds[num].name)))
		ft_pwd();
	else if (!(ft_strncmp_quote("env", g_g.cmds->name)))
	{
		// while (is_equal_present(g_g.cmds[num].args[i]))
		if (is_env_arg(num) || !g_g.cmds[num].args
			|| is_space(g_g.cmds[num].args[0]))
			print_list();
	}
	else if (!(ft_strncmp_quote("unset", g_g.cmds[num].name)))
	{
		if (is_space_present(num))
			ft_unset(g_g.cmds[num].args);
		else
			printf("Error: not a valid identifier\n");
	}
	else if (!(ft_strncmp_quote("export", g_g.cmds[num].name)))
	{
		if (is_space_present(num))
			ft_export(g_g.cmds[num].args);
		else
			printf("Error: not a valid identifier\n");
	}
	else if (is_equal_present(g_g.cmds[num].name))
		equal_handling(num);
	else if (ft_strncmp_quote("exit", g_g.cmds[num].name))
		printf("%s: command not found\n", g_g.cmds[num].name);
	return (0);
}
