/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_leak.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:27:36 by radib             #+#    #+#             */
/*   Updated: 2025/10/27 15:47:46 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_x(int x, t_table *t, int y)
{
	if (y >= 1)
		pthread_mutex_destroy(t->startallowed);
	if (y >= 2)
		pthread_mutex_destroy(t->checkallowed);
	if (x >= 1)
		free(t->p);
	if (x >= 2)
		free(t->mutex);
	if (x >= 3)
		free(t->startallowed);
	if (x >= 4)
		free(t->checkallowed);
	if (x >= 5)
		free(t->print);
	return (0);
}

int	assign_more(t_table *t, pthread_t *thread)
{
	t->checkallowed = malloc(sizeof(pthread_mutex_t));
	if (!t->checkallowed)
		return (free_x(3, t, 1));
	if (pthread_mutex_init(t->checkallowed, NULL) != 0)
	{
		printf("mutex error\n");
		return (free_x(3, t, 1));
	}
	t->print = malloc(sizeof(pthread_mutex_t));
	if (!t->print)
		return (free_x(4, t, 2));
	if (pthread_mutex_init(t->print, NULL) != 0)
	{
		printf("mutex error\n");
		return (free_x(4, t, 2));
	}
	t->thread = thread;
	return (1);
}

int	assign(t_arg *arg, t_table *t, pthread_t *thread, const char **argv)
{
	arg->nop = ft_atoi(argv[1], 1, 0, 0);
	arg->ttd = ft_atoi(argv[2], 1, 0, 0);
	arg->tte = ft_atoi(argv[3], 1, 0, 0);
	arg->tts = ft_atoi(argv[4], 1, 0, 0);
	if (arg->nop == 1)
		return (hardcoded_one(arg->ttd));
	t->p = malloc (sizeof(t_philo *) * arg->nop);
	if (!t->p)
		return (0);
	t->mutex = malloc(sizeof(pthread_mutex_t *) * arg->nop);
	if (!t->mutex)
		return (free_x(1, t, 0));
	t->startallowed = malloc(sizeof(pthread_mutex_t));
	if (!t->startallowed)
		return (free_x(2, t, 0));
	if (pthread_mutex_init(t->startallowed, NULL) != 0)
	{
		printf("mutex error\n");
		return (free_x(2, t, 0));
	}
	return (assign_more(t, thread));
}

int	anti_leak(t_arg *arg, t_table *t, pthread_t *th, const char **argv)
{
	int	i;

	i = -1;
	if (!th && t)
	{
		free(t);
		free(arg);
		return (0);
	}
	if (!t)
	{
		free(arg);
		return (0);
	}
	if (!assign(arg, t, th, argv))
		return (0);
	if (!put_in_struct(-1, arg, t))
		return (0);
	while (++i < arg->nop)
		t->p[i]->timelasteaten = 0;
	give_forks(-1, t, arg);
	return (1);
}
