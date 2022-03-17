/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:51:34 by akhachat          #+#    #+#             */
/*   Updated: 2022/03/17 14:39:51 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*str;

	(void)argc;
	(void)argv;
	fill_env(env);
	while (1)
	{
		str = readline("minishell: ");
		if (str)
			add_history(str);
		if (!str)					 //Ctrl+D
		{
			free(str);
			ft_error("exit", 0);
		}
		check_oldpwd("HOMW");

		// start(env, str);
	}
	free(str);
	return (0);
}
