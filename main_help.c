/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:49:56 by radib             #+#    #+#             */
/*   Updated: 2025/10/31 17:01:27 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_all(int i, t_arg *arg, t_table *t, pthread_t *thread)
{
	(void)i;
	(void)arg;
	(void)t;
	(void)thread;
	return (1);
}

int	verif_argc(t_arg *arg, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (printf ("erreur\n"));
	if (argc == 5)
		arg->notme = -1;
	if (argc == 6)
		arg->notme = ft_atoi(argv[5], 1, 0, 0);
	return (1);
}
