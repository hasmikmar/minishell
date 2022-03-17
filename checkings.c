/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhachat <akhachat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:39:02 by akhachat          #+#    #+#             */
/*   Updated: 2022/03/17 16:47:29 by akhachat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int executable_check(char *cmd)
{
    
}

int is_builtins(char *cmd)
{
    if(!(ft_strncmp_quote("echo", g_g.cmds->name, ft_strlen(cmd))))
        ft_echo(g_g.cmds->args);
    else if(!(ft_strncmp_quote("cd", g_g.cmds->name, ft_strlen(cmd))))
        ft_cd(g_g.cmds->args[0]);
    else if (!(ft_strncmp_quote("unset", g_g.cmds->name, ft_strlen(cmd))))
        return 1;
    else if (!(ft_strncmp_quote("export", g_g.cmds->name, ft_strlen(cmd))))
        return 2;
    else if (!(ft_strncmp_quote("exit", g_g.cmds->name, ft_strlen(cmd))))
        return 3;
    else if (!(ft_strncmp("pwd", g_g.cmds->name, ft_strlen(cmd))))
        ft_pwd();
    else if (!(ft_strncmp("env", g_g.cmds->name, ft_strlen(cmd))))
        print_list();
    return (0);
}
