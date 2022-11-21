/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:12:57 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 13:29:03 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#include "../parser/tree.h"
#include "../lexer/lexer.h"
#include "libft.h"
#include "../lexer/lexer.h"

t_prompt	g_prompt;

int	ft_strlen_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		;
	return (i);
}

void	ft_adjust_exec(t_ctx *ctx, char **tab, int i)
{
	int	j;

	j = -1;
	if (ctx->fd_here_doc)
		ft_free_tab(ctx->fd_here_doc);
	ctx->fd_here_doc = malloc(sizeof(char *) * (i + 2));
	while (tab[++j])
	{
		ctx->fd_here_doc[j] = ft_strdup(tab[j]);
		free(tab[j]);
	}
	ctx->fd_here_doc[j] = 0;
	free(tab);
}

t_ast_node	*ft_skip_to_pair(t_ast_node *node)
{
	while (node && node->data.pair.right)
	{
		if (node->node_type == NODE_AND || node->node_type == NODE_OR)
			return (node->data.pair.right);
		if (node->node_type && node->node_type <= 5)
			node = node->data.pair.right;
		else
			return (NULL);
	}
	return (NULL);
}
