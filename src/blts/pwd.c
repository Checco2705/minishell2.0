/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffebbrar <ffebbrar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:34:54 by ffebbrar          #+#    #+#             */
/*   Updated: 2025/07/04 14:56:56 by ffebbrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <sys/param.h>
#include "libft.h"

#ifndef PATH_MAX
# define PATH_MAX 4096
#endif

// --- CHECCO: inizio funzione ft_pwd ---
// Stampa la directory corrente
int	ft_pwd(char **args)
{
	char	cwd[PATH_MAX];

	(void)args;
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	ft_putendl_fd("pwd: error retrieving current directory", 2);
	return (1);
}
