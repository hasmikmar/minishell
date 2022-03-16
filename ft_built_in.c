/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:58:29 by akhachat          #+#    #+#             */
/*   Updated: 2022/03/09 19:58:36 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char *str)
{
	char	**spl;
	int		i;
	int		len;
	t_list	*tmp;

	i = 0;
	spl = ft_split(str, ' ');
	while (spl[i])
	{
		len = ft_strlen(spl[i]);
		tmp = g_g.lenv;
		while (tmp)
		{
			if (!ft_strncmp_quote(spl[i], tmp->var, len))
			{
				ft_lstdel(&g_g.lenv, tmp);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	free(spl);
}

void	ft_pwd(void)
{
	char	*str;

	str = malloc(sizeof(char *) * 1024);
	if (!str)
		ft_error("Can't malloc\n", 0);
	getcwd(str, 1024);
	printf("%s\n", str);
	free(str);
}

void	ft_export(char *str)
{
	char	**spl;
	int		i;
	int		len;
	t_list	*tmp;
	char	**s;
	int		flag;
	int		flag1;

	flag1 = 0;
	if (str[0] == '\0')
		print_export();
	else
	{
		i = 0;
		spl = ft_split(str, ' ');
		while (spl[i])
		{
			flag = is_equal_present(spl[i]);
			s = ft_split_for_export(spl[i]);
			tmp = g_g.lenv;
			while (tmp)
			{
				len = ft_strlen(s[0]);
				if (!ft_strncmp_quote(s[0], tmp->var, len))
				{
					if (s[1])
					{
						tmp->val = without_quotes(s[1]);
						tmp->equal_sign = 0;
					}
					else if (flag)
						tmp->equal_sign = 1;
					tmp->exp = 1;
					flag1 = 1;
					break ;
				}
				tmp = tmp->next;
			}
			if (!flag1)
			{
				if (s[1])
					tmp = ft_lstnew(without_quotes(s[0]),
							without_quotes(s[1]), 1);
				else
					tmp = ft_lstnew(without_quotes(s[0]),
							NULL, 1);
				if (flag)
					tmp->equal_sign = 1;
				ft_lstadd_front(&g_g.lenv, tmp);
			}
			i++;
			free(s);
		}
		free(spl);
	}
}
