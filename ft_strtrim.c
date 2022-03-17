/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 18:55:33 by akhachat          #+#    #+#             */
/*   Updated: 2022/03/17 14:39:51 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	else
		return (0);
}

size_t	ft_strlcpy(char *dst, const char *src,
						size_t dstsize)
{
	const char		*t;
	size_t			i;

	t = src;
	i = dstsize;
	if (i != 0)
	{
		while (--i != 0)
		{
			if (*src == '\0')
				break ;
			*dst++ = *src++;
		}
		*dst = *src;
	}
	if (i == 0)
	{
		if (dstsize != 0)
			*dst = '\0';
		while (*src++)
			;
	}
	return (src - t - 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;
	size_t	start;
	char	*result;

	result = 0;
	if (s1 && set)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[start] && ft_strchr(set, s1[start]))
			start++;
		while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > start)
			end--;
		result = (char *)malloc(sizeof(char) * (end - start + 1));
		if (result)
			ft_strlcpy(result, &s1[start], end - start + 1);
	}
	return (result);
}
