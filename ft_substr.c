/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:42:30 by akhachat          #+#    #+#             */
/*   Updated: 2021/02/09 17:47:24 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	l;
	size_t	i;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	str = (char *)malloc(l + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && i + start < l)
	{
		str[i] = s[start + i];
		++i;
	}
	str[i] = '\0';
	return (str);
}
