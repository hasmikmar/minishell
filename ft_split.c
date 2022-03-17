/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 18:09:31 by akhachat          #+#    #+#             */
/*   Updated: 2022/03/17 14:39:51 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	char_count(char const *str, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] && str[i++] != c)
			j++;
		if (j)
			count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	int		count;
	char	**d;

	i = 0;
	k = 0;
	count = char_count(s, c);
	d = malloc((count + 1) * sizeof(char *));
	while (i < count)
	{
		j = 0;
		while (s[k] && s[k++] != c)
			j++;
		if (j)
		{
			if (s[k] || s[ft_strlen(s) - 1] == c)
				d[i++] = ft_substr(s, (k - j - 1), j);
			else
				d[i++] = ft_substr(s, (k - j), j);
		}
	}
	d[i] = 0;
	return (d);
}

int	chars_until_equal(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	**ft_split_for_export(char const *s)
{
	int		i;
	int		k;
	int		count;
	char	**d;

	i = 0;
	count = is_equal_present(s) + 1;
	d = malloc(3 * sizeof(char *));
	k = chars_until_equal(s);
	d[0] = ft_substr(s, 0, k);
	if (count == 2)
	{
		d[1] = ft_substr(s, k + 1, ft_strlen(s) - k - 1);
		d[2] = 0;
	}
	else
		d[1] = 0;
	return (d);
}
