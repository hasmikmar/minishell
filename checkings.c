/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:39:02 by tapetros          #+#    #+#             */
/*   Updated: 2022/04/07 13:51:12 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*to_lower(char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (s[i] != '\0')
	{
		if (s[i] >= 65 && s[i] <= 90)
			str[i] = s[i] + 32;
		else
			str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	is_env_arg(int num)
{
	int	i;

	i = 1;
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

int	check_builtin(char *s)
{
	char	*str;

	if (!(ft_strncmp_quote("exit", s)))
		return (1);
	str = to_lower(s);
	if (!(ft_strncmp_quote("echo", str)) || !(ft_strncmp_quote("pwd", str))
		|| !(ft_strncmp_quote("cd", str)) || !(ft_strncmp_quote("env", str))
		|| !(ft_strncmp_quote("export", str))
		|| !(ft_strncmp_quote("unset", str)))
		return (1);
	else
		return (0);
}

//PROCESSY ARDEN SARQVAC AAA
int	is_builtins(int num, char **env)
{
	// printf("env_path%s\n", env_path(env, g_g.cmds[num].name));
	char	*str;
	// printf("%s\n", g_g.cmds[num].args[0]);
	// printf("%s\n", g_g.cmds[0].name);
	// printf(":%s\n", g_g.cmds[num].str_arg);
	// printf("Test\n");
	if (!(ft_strncmp_quote("exit", g_g.cmds[num].name)))
		ft_atoi_exit(g_g.cmds[num].str_arg);
	// printf("Valod\n");
	str = to_lower(g_g.cmds[num].name);
	if (!(ft_strncmp_quote("echo", str)))
	{
		if (g_g.cmds[num].args[1] == NULL)
			printf("\n");
		else
			ft_echo(g_g.cmds[num].args);
	}
	else if (!(ft_strncmp_quote("cd", str)))
		ft_cd(g_g.cmds[num].args[1]);
	else if (!(ft_strncmp_quote("pwd", str)))
		ft_pwd();
	else if (!(ft_strncmp_quote("env", str)))
	{
		//argumentneri pahy kisat a
		// while (is_equal_present(g_g.cmds[num].args[i]))
		if (is_env_arg(num) || !g_g.cmds[num].args
			|| is_space(g_g.cmds[num].args[1]))
			print_list();
	}
	else if (!(ft_strncmp_quote("unset", str)))
	{
		if (is_space_present(num))
			ft_unset(g_g.cmds[num].args);
		else
			printf("Error: not a valid identifier\n");
	}
	else if (!(ft_strncmp_quote("export", str)))
	{
		if (is_space_present(num))
			ft_export(g_g.cmds[num].args);
		else
			printf("Error: not a valid identifier\n");
	}
	else if (is_equal_present(str))
		equal_handling(num);
	else if (execve(env_path(env, g_g.cmds[num].name),
			g_g.cmds[num].args, env) == -1)
	{
		printf("%s: command not found", g_g.cmds[num].args[0]);
		ft_error("", 0);
	}
	free(env);
	return (0);
}
