/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:31:54 by akhachat          #+#    #+#             */
/*   Updated: 2021/02/08 16:52:22 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	if (!n)
		return (0);
	i = 0;
	while (i < n && st1[i] && st2[i] && st1[i] == st2[i])
		i++;
	if (i < n)
		return (st1[i] - st2[i]);
	else
		return (0);
}

int	ft_strncmp_quote(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	size_t			j;
	unsigned char	*st1;
	unsigned char	*st2;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	if (!n)
		return (0);
	i = 0;
	j = 0;
	while ((i < n && st1[i] && st2[j] && st1[i] == st2[j])
		|| st1[i] == '\'' || st1[i] == '\"')
	{
		if (st1[i] != '\"' && st1[i] != '\'')
			j++;
		i++;
	}
	if (i < n)
		return (st1[i] - st2[j]);
	else
		return (0);
}
