/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tapetros <tapetros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:40:33 by tapetros          #+#    #+#             */
/*   Updated: 2022/03/18 14:48:21 by tapetros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	int		a[2];
	char	*new;

	a[0] = 0;
	a[1] = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	new = (char *)malloc(l1 + l2 + 1);
	if (!new)
		return (0);
	while (s1[a[0]] != '\0')
	{
		new[a[0]] = s1[a[0]];
		a[0]++;
	}
	while (s2[a[1]] != '\0')
	{
		new[a[0]] = s2[a[1]];
		a[0]++;
		a[1]++;
	}
	new[a[0]] = '\0';
	return (new);
}

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	size_t	l1;
	size_t	l2;
	int		a[2];
	char	*new;

	a[0] = 0;
	a[1] = 0;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	new = (char *)malloc(l1 + l2 + 1);
	if (!new)
		return (0);
	while (s1[a[0]] != '\0')
	{
		new[a[0]] = s1[a[0]];
		a[0]++;
	}
	while (s2[a[1]] != '\0')
	{
		new[a[0]] = s2[a[1]];
		a[0]++;
		a[1]++;
	}
	new[a[0]] = '\0';
	return (new);
}
