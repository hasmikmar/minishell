/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:32:38 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/04 18:10:22 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cancel(void)
{
	struct termios	termios_p;

	if (tcgetattr(0, &termios_p))
		return ;
	termios_p.c_lflag &= ~ECHO;
	termios_p.c_lflag &= ~ECHOCTL;
	termios_p.c_lflag |= ECHO;
	if (tcsetattr(0, 0, &termios_p))
		return ;
}

static	void	reprompt(int sig)
{
	(void)sig;

	ft_cancel();
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static		void	sigquit(int sig)
{
	(void)sig;
	ft_cancel();
	rl_on_new_line();
	rl_redisplay();
}

void	sig_init(void)
{
	signal(SIGINT, reprompt);
	signal(SIGQUIT, sigquit);
}

// static void interrupt(int sig)
// {
//     (void)sig;
//     ft_cancel();
//     rl_on_new_line();
//     rl_redisplay();
//     exit(1);
// }

void	sig_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
