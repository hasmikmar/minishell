/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmargary <hmargary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:51:34 by tapetros          #+#    #+#             */
/*   Updated: 2022/03/29 21:00:04 by hmargary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fintuflyushka(void)
{
	int	len;

	len = ft_strlen("░▒▓██████████►╬◄██████████▓▒░\n");
	write(1, "░▒▓██████████►╬◄██████████▓▒░\n", len);
	write(1, "░▒▓██►╔╦╦╦═╦╗╔═╦═╦══╦═╗◄██▓▒░\n", len);
	write(1, "░▒▓██►║║║║╩╣╚╣═╣║║║║║╩╣◄██▓▒░\n", len);
	write(1, "░▒▓██►╚══╩═╩═╩═╩═╩╩╩╩═╝◄██▓▒░\n", len);
	write(1, "░▒▓██████████►╬◄██████████▓▒░\n", len);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;

	(void)argc;
	(void)argv;
	fill_env(env);
	fintuflyushka();
	sig_init();
	while (1)
	{
		str = readline("minishell: ");
		if (!str)
		{
			free(str);
			ft_error("exit", 0);
		}
		if (ft_strlen(str))
			add_history(str);
		if (!check_quotes(str) || !check_sem_and_pipe(str) || !check_red(str))
		{
			printf("Syntax error\n");
			continue ;
		}
		start(str);
	}
	free(str);
	return (0);
}
