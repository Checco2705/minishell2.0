/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffebbrar <ffebbrar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:31:39 by ffebbrar          #+#    #+#             */
/*   Updated: 2025/07/04 13:11:51 by ffebbrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_single_token_quotes(t_token *token)
{
	char	*result;

	if (!token || !token->value || token->type != TOKEN_WORD)
		return ;
	result = process_token_quotes(token->value);
	if (!result)
		return ;
	free(token->value);
	token->value = ft_strdup(result);
	free(result);
}

void	handle_quotes(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
			handle_single_token_quotes(current);
		current = current->next;
	}
}
