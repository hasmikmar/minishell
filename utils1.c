/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:57:50 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/04 21:35:15 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_oldpwd(char *value)
{
	t_list	*tmp;
	t_list	*old;

	old = find_element("OLDPWD");
	if (!old)
	{
		tmp = ft_lstnew("OLDPWD", without_quotes(value), 1);
		ft_lstadd_front(&g_g.lenv, tmp);
	}
	else
		old->val = without_quotes(value);
}

int	is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
