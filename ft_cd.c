/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:58:29 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/04 16:43:16 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_minus(char *str)
{
	t_list	*tmp;
	char	*old;

	getcwd(str, 1024);
	tmp = find_element("OLDPWD");
	old = tmp->val;
	check_oldpwd(str);
	tmp = find_element("PWD");
	getcwd(str, 1024);
	tmp->val = str;
	printf("%s\n", tmp->val);
	chdir(old);
}

void	ft_cd(char *p)
{
	char	*str;
	t_list	*tmp;
	char	*old;
	char	*res;

	str = malloc(sizeof(char *) * 1024);
	if (!str)
		ft_error("Can't malloc\n", 0);
	if (p == NULL || p[0] == '~')
	{
		getcwd(str, 1024);
		check_oldpwd(str);
		tmp = find_element("HOME");
		res = tmp->val;
		if (p)
			p = p + 2;
	}
	if (p != NULL && p[0] == '-' && p[1] == '\0')
		cd_minus(str);
	else
	{
		getcwd(str, 1024);
		old = str;
		if (chdir(p) == -1)
		{	
			res = ft_strjoin(res, "/");
			if (p != NULL)
				res = ft_strjoin(res, p);
			if (!chdir(res))
			{
				check_oldpwd(old);
				tmp = find_element("PWD");
				tmp->val = res;
			}
			else
				printf("cd: %s: No such file or directory\n", p);
		}
		else
		{
			check_oldpwd(old);
			tmp = find_element("PWD");
			getcwd(str, 1024);
			tmp->val = str;
		}
	}
	free(str);
}
