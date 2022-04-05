/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:57:50 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/04 16:43:16 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_list_elements(void)
{
	t_list	*tmp;
	int		count;

	count = 0;
	tmp = g_g.lenv;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**list_to_arr(void)
{
	char	**arr;
	int		count;
	int		i;
	t_list	*temp;

	i = 0;
	temp = g_g.lenv;
	count = count_list_elements();
	arr = malloc(sizeof(char *) * (count + 1));
	while (i != count)
	{
		arr[i] = ft_strjoin(temp->var, "=");
		if (temp->val)
			arr[i] = ft_strjoin(arr[i], temp->val);
		i++;
		temp = temp->next;
	}
	arr[i] = NULL;
	return (arr);
}

t_list	*find_element(char *var_name)
{
	t_list	*tmp;

	tmp = g_g.lenv;
	while (tmp)
	{
		if (!ft_strncmp_quote(tmp->var, var_name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
