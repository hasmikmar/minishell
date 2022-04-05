/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 12:58:37 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/04 16:43:16 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(char *var_inf, char *val_inf, int is_exp)
{
	t_list	*l;

	l = (t_list *)malloc(sizeof(t_list));
	if (!l)
		return (0);
	l->var = var_inf;
	l->val = val_inf;
	l->exp = is_exp;
	l->next = NULL;
	l->prev = NULL;
	return (l);
}

void	ft_lstadd_front(t_list **lst, t_list *neww)
{
	if (*lst)
	{
		neww->next = *lst;
		(*lst)->prev = neww;
		*lst = neww;
	}
	else
		*lst = neww;
}

void	ft_lstdel(t_list **lst, t_list *del)
{
	if (*lst == NULL || del == NULL)
		return ;
	if (*lst == del)
		*lst = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	free(del);
	return ;
}

void	print_list(void)
{
	t_list	*tmp;

	tmp = g_g.lenv;
	while (g_g.lenv)
	{
		if (g_g.lenv->exp && g_g.lenv->val)
			printf("%s=%s\n", g_g.lenv->var, g_g.lenv->val);
		else if (g_g.lenv->exp && g_g.lenv->equal_sign)
			printf("%s=\n", g_g.lenv->var);
		g_g.lenv = g_g.lenv->next;
	}
	g_g.lenv = tmp;
}

void	print_export(void)
{
	t_list	*tmp;

	tmp = g_g.lenv;
	while (g_g.lenv)
	{
		if (g_g.lenv->val && g_g.lenv->exp)
			printf("declare -x %s=\"%s\"\n", g_g.lenv->var, g_g.lenv->val);
		else if (g_g.lenv->exp && g_g.lenv->equal_sign)
			printf("declare -x %s=\"\"\n", g_g.lenv->var);
		else if (g_g.lenv->exp)
			printf("declare -x %s\n", g_g.lenv->var);
		g_g.lenv = g_g.lenv->next;
	}
	g_g.lenv = tmp;
}
