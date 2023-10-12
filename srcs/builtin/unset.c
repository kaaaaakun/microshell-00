/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:13:55 by hhino             #+#    #+#             */
/*   Updated: 2023/10/12 19:48:32 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

// Returns the previous list of matches

static t_list	*search_envlist_for_unset(t_info *status, char *str)
{
	t_list	*env;
	int		len;
	char	*searched_word;

	env = status->env;
	if (!env)
		return (NULL);
	searched_word = ft_strjoin_free(str, "=", NEITHER_FREE);
	len = ft_strlen(searched_word);
	while (env->next != NULL)
	{
		if (ft_strncmp(env->next->content, searched_word, len) == 0)
			break ;
		else if (ft_strncmp(env->next->content, str, len) == 0)
			break ;
		env = env->next;
	}
	if (env->next == NULL)
	{
		if (ft_strncmp(env->content, searched_word, len) != 0)
		{
			free(searched_word);
			return (NULL);
		}
		else if (ft_strncmp(env->content, str, len) != 0)
		{
			free(searched_word);
			return (NULL);
		}
	}
	free(searched_word);
	return (env);
}

// bash only deletes when only the left side matches,
// but this also deletes when the left side matches or
// the left side and right side match perfectly.

int	unset_the_top_or_not(t_info *status, char *str)
{
	t_list	*env;
	int		len;
	char	*searched_word;

	d_printf("[unset_the_top_or_not]");
	env = status->env;
	if (!env)
		return (0);
	searched_word = ft_strjoin_free(str, "=", NEITHER_FREE);
	len = ft_strlen(searched_word);
	if (env != NULL)
	{
		if (ft_strncmp(env->content, str, len) == 0)
		{
			free(searched_word);
			return (1);
		}
		else if (ft_strncmp(env->content, searched_word, len) == 0)
		{
			free(searched_word);
			return (1);
		}
	}
	free(searched_word);
	return (0);
}

void	ex_unset(t_info *status, t_stack *data)
{
	t_list	*list;
	t_list	*envlist;
	t_list	*temp;
	char	*dup_content;

	list = data->cmdlist->next;
	while (list != NULL)
	{
		dup_content = ft_strdup(list->content);
		if (search_envlist_for_export(status, dup_content) != NULL)
		{
			envlist = search_envlist_for_export(status, dup_content);
			if (unset_the_top_or_not(status, dup_content) == 1)
			{
				temp = envlist;
				status->env = envlist->next;
				free(temp->content);
				free(temp);
			}
			else if (envlist->next == NULL)
			{
				temp = envlist;
				envlist = search_envlist_for_unset(status, dup_content);
				envlist->next = NULL;
				free(temp->content);
				free(temp);
			}
			else if (envlist->next != NULL)
			{
				temp = envlist;
				envlist = search_envlist_for_unset(status, dup_content);
				envlist->next = envlist->next->next;
				free(temp->content);
				free(temp);
			}
		}
		free(dup_content);
		list = list->next;
	}
	status->exit_status = 0;
}
