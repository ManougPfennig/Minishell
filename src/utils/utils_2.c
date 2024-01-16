/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:30:38 by npatron           #+#    #+#             */
/*   Updated: 2024/01/16 21:01:00 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_error_env(char *str)
{
    write(1, "bash: export: '", 15);
    write(1, str, ft_strlen(str));
    write(1, "': not a valid identifier\n", 27);
}

char    *find_variable(t_cmds *cmd, int j)
{
    char    *var;

    if (there_is_egual(cmd->tab[j]) == 1)
        return (NULL) ;
    else
    {
        var = ft_strdup(cmd->tab[j]);
        return (var);
    }
}

char    *var_env_export(char *s)
{
    char    *result;
    int     i;
    int     j;

    result = malloc(sizeof(char) * (ft_strlen(s) + 4));
    i = 1;
    j = 1;
    result[0] = s[0];
    while (s[i - 1] != '=')
    {
        result[j] = s[i];
        i++;
        j++;
    }
    result[j] = '"';
    j++;
    while (s[i])
    {
        result[j] = s[i];
        i++;
        j++;
    }
    result[j] = '"';
    j++;
    result[j] = '\0';
    return (result);
}

char    *ft_addstring(char *s, char *s2)
{
    char    *result;
    int     i;
    int     j;

    i = ft_strlen(s) + ft_strlen(s2);
    result = malloc(sizeof(char) * i + 1);
    i = 0;
    j = 0;
    while (s[i])
    {
        result[j] = s[i];
        i++;
        j++;
    }
    i = 0;
    while (s2[i])
    {
        result[j] = s2[i];
        j++;
        i++;
    }
    result[j] = '\0';
    return (result);
}

int check_var(char *str)
{
    int i;

    i = 1;
    if ((str[0] >= '!' && str[0] <= '/')
        || (str[0] >= ':' && str[0] <= '?')
        || (str[0] >= '0' && str[0] <= '9')
        || str[0] == '=')
    {
        print_error_env(str);
        return (1);
    }
    while (str[i])
    {
        if ((str[i] >= '!' && str[i] <= '/')
        || (str[i] >= ':' && str[i] <= '<')
        || (str[i] >= '>' && str[i] <= '?'))
        {
            print_error_env(str);
            return (1);
        }
        i++;
    }
    return (0);
}

