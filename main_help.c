/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:49:56 by radib             #+#    #+#             */
/*   Updated: 2025/11/04 15:23:22 by radib            ###   ########.fr       */
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
		return (invalid_input());
	if (argc == 5)
		arg->notme = -1;
	if (argc == 6)
		arg->notme = ft_atoi(argv[5], 1, 0, 0);
	arg->nop = ft_atoi(argv[1], 1, 0, 0);
	arg->ttd = ft_atoi(argv[2], 1, 0, 0);
	arg->tte = ft_atoi(argv[3], 1, 0, 0);
	arg->tts = ft_atoi(argv[4], 1, 0, 0);
	if ((arg->nop < 0 && arg->nop <= 200) || arg->notme == -20000000000
		|| arg->ttd < 0 || arg->tte < 0 || arg->tts < 0)
		return (invalid_input());
	return (1);
}
