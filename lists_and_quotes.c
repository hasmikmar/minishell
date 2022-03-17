/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_and_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:57:50 by akhachat          #+#    #+#             */
/*   Updated: 2022/03/17 14:39:51 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
			if (str[i] == '\0')
				ft_error("Quotation error", 0);
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			printf("%c\n", str[i]);
			if (str[i] == '\0')
				ft_error("Quotation error", 0);
		}
		i++;
	}
}

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
		arr[i] = ft_strjoin(arr[i], temp->val);
		i++;
		temp = temp->next;
	}
	arr[i] = NULL;
	return (arr);
}

//NOT WORKING!!!!!!!!!!!!!!!!!!!!!!!!!!!!
t_list	*find_element(char *var_name)
{
	t_list	*tmp;
	int		len;

	len = ft_strlen(var_name);
	tmp = g_g.lenv;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, var_name, len))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
