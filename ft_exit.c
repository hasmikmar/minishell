/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:58:29 by akhachat          #+#    #+#             */
/*   Updated: 2022/04/04 16:43:16 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_atoi_exit_1(char *str)
{
	char	*s;
	int		len;

	len = 0;
	while (str[len] != ' ' && str[len] != '\0')
			len++;
	if (str[0] != '\'' && str[0] != '\"')
		s = ft_substr(str, 0, len);
	else if (str[len - 1] == '\'' || str[len - 1] == '\"')
		s = ft_substr(str, 1, len - 2);
	else
	{
		str = ft_strtrim(str, "\',\"");
		printf("exit\nexit: %s", str);
		ft_error(": numeric argument required", 255);
		return ;
	}
	printf("exit\nexit: %s", s);
	ft_error(": numeric argument required", 255);
	free(s);
}

void	ft_atoi_exit_2(char *str, int i, int num, int flag)
{
	int	min;

	min = 1;
	if ((str[0] == '-' && !flag) || (str[1] == '-' && flag))
		min = -1;
	if (str[i] == '\"' || str[i] == '\'')
	{
		i++;
		flag = 0;
	}
	if (str[i] == '\0')
		ft_exit(num * min);
	if ((str[i] == ' ' && flag) || str[i] != ' ')
		ft_atoi_exit_1(str);
	else
		printf("exit\nexit: too many arguments\n");
}

void	ft_atoi_exit(char *str)
{
	int					i;
	unsigned long long	num;
	int					flag;

	i = 0;
	num = 0;
	flag = 0;
	if (str[i] == '\"' || str[i] == '\'')
	{
		i++;
		flag = 1;
	}
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		num = num * 10;
		num = num + str[i++] - '0';
	}
	if (num > 9223372036854775807)
	{
		printf("exit\nexit: %llu", num);
		ft_error(": numeric argument required", 255);
	}
	ft_atoi_exit_2(str, i, num, flag);
}

void	ft_exit(int code)
{
	while (code <= 0)
		code += 256;
	if (code >= 256)
		code %= 256;
	printf("exit\n");
	exit(code);
}
