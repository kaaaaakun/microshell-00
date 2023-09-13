/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:14:07 by hhino             #+#    #+#             */
/*   Updated: 2023/09/13 16:31:33 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_env(t_list *env)
{
	char	*str;

	while (env != NULL)
	{
		str = ft_strjoin("declare -x ", env->content);
		insert_doublequotes(str);
		ft_printf("%s\n", str);
		free(str);
		env = env->next;
	}
}

void	append_envlist(t_list *env, char *str)
{
	char	*temp;

	temp = env->content;
	env->content = ft_strjoin(env->content, ft_strchr(str, '=') + 1);
	free(temp);
}

void	overwrite_envlist(t_list *env, char *str)
{
	char	*temp;

	temp = env->content;
	env->content = str;
	free(temp);
}

//0912左辺が存在している時に+=をした次の"export"で死ぬ
void	ex_export(t_info *status, t_stack *data)
{
	int		flag;
	int		i;
	t_list	*list;
	char	*listcontent;

	flag = 0;
	list = data->cmdlist;
	listcontent = list->content;
	if (list->next == NULL)
		print_export_env(status->env);
	else
	{
		list = list->next;
		while (list != NULL)
		{
			flag = plus_equal_or_not(list->content);
			if (valid_left(list->content, flag) == 0)
				ft_printf("%s not a valid identifier\n", list->content);
			else
			{
				i = 0;
				if (flag == 1)
				{
					while (list->content[i] != '+')
						i++;
				}
				else if (flag == 0)
				{
					while (list->content[i] != '=' && list->content[i] != '\0')
						i++;
				}
				if (search_envlist(status, ft_substr(list->content, 0, i)))
				{
					if (flag == 1)
						append_envlist(search_envlist(status, ft_substr(list->content, 0, i)), ft_strdup(list->content));
					else if (flag == 0)
						overwrite_envlist(search_envlist(status, ft_substr(list->content, 0, i)), ft_strdup(list->content));
				}
				else
				{
					if (flag == 1)
						push_back(&status->env, no_left_but_plus(ft_strdup(list->content)));
					else
						push_back(&status->env, ft_strdup(list->content));
				}
			}
			list = list->next;
		}
	}
	return ;
}


// bash-3.2$ export aaa=bbb
// bash-3.2$ export ccc="echo $aaa"
// bash-3.2$ $ccc
// bbb
// bash-3.2$ export aaa=bbb ccc
// bash-3.2$ export ccc="echo $aaa"
// bash-3.2$ $ccc
// bbb
// $の後にくるものは英数字と_のみ
// $$(必須ではない、プロセスID), $?(必須、終了ステータス)
// 左辺が以前に定義したものと同値であれば=以下を書き換える
// 左辺の一文字目が英字以外だった場合は弾かれるが、引数がその後も続く場合は反映される
// export PATH=$PATH:/path/to/new/program
