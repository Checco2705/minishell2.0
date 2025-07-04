/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffebbrar <ffebbrar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 19:31:43 by ffebbrar          #+#    #+#             */
/*   Updated: 2025/07/04 13:03:41 by ffebbrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Aggiunge un token alla lista.
** 
** @param head: Puntatore alla testa della lista
** @param tail: Puntatore alla coda della lista
** @param tok: Il token da aggiungere
*/
static void	add_token_to_list(t_token **head, t_token **tail, t_token *tok)
{
	if (!*head)
		*head = tok;
	else
		(*tail)->next = tok;
	*tail = tok;
}

/*
** Gestisce l'estrazione e l'aggiunta di una parola.
** 
** @param line: La stringa da processare
** @param i: Puntatore all'indice corrente nella stringa
** @param head: Puntatore alla testa della lista di token
** @param tail: Puntatore alla coda della lista di token
** @return: La lunghezza della parola estratta
*/
static int	handle_word(const char *line, int *i, t_token **head,
	t_token **tail)
{
	char	*word;
	int		len;

	word = extract_word(line, i);
	if (!word)
		return (0);
	len = ft_strlen(word);
	if (len > 0)
		add_token_to_list(head, tail, create_token(word, TOKEN_WORD));
	free(word);
	return (len);
}

static void	skip_whitespace(const char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

static void	process_token(const char *line, int *i, t_token **head,
	t_token **tail)
{
	t_token	*tok;

	if (line[*i] == '\'' || line[*i] == '"')
		handle_word(line, i, head, tail);
	else if (is_operator(line, *i))
	{
		tok = handle_redirection_operator(line, i);
		if (tok)
			add_token_to_list(head, tail, tok);
	}
	else
		handle_word(line, i, head, tail);
}

/*
** Tokenizza una stringa in una lista di token.
** 
** @param line: La stringa da tokenizzare
** @return: La testa della lista di token
*/
t_token	*tokenize(const char *line)
{
	t_token	*head;
	t_token	*tail;
	int		i;

	if (!line)
		return (NULL);
	head = NULL;
	tail = NULL;
	i = 0;
	while (line[i])
	{
		skip_whitespace(line, &i);
		if (!line[i])
			break ;
		process_token(line, &i, &head, &tail);
	}
	return (head);
}
