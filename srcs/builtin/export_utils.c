/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:06:49 by hhino             #+#    #+#             */
/*   Updated: 2023/09/11 19:28:38 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_doublequotes(char *str)
{
	int		len;
	char	*flag;

	flag = ft_strchr(str, '=');
	len = ft_strlen(str);
	if (flag != NULL)
	{
		ft_memmove(flag + 2, flag + 1, len - (flag - str));
		flag[1] = '"';
	}
	str[len + 1] = '"';
	str[len + 2] = '\0';
}

int	valid_left(char *str, int flag)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) == 0 && str[i] != '_')
		return (0);
	if (flag == 0)
	{
		while (str[i] != '=' && str[i] != '\0')
		{
			if (ft_isalnum(str[i]) == 0 && str[i] != '_')
				return (0);
			i++;
		}
	}
	else if (flag == 1)
	{
		while (str[i] != '+')
		{
			if (ft_isalnum(str[i]) == 0 && str[i] != '_')
				return (0);
			i++;
		}
	}
	return (1);
}

int	plus_equal_or_not(char *str)
{
	int	i;

	i = 0;
	if (ft_strnstr(str, "+=", ft_strlen(str)) != NULL)
	{
		while (str[i] != '+')
		{
			if (str[i] == '=')
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}