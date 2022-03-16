/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:51:34 by akhachat          #+#    #+#             */
/*   Updated: 2022/03/03 19:51:36 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*str;

	(void)argc;
	(void)argv;
	// (void)env;
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
		start(env, str);
	}
	free(str);
	return (0);
}
