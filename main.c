/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:55:20 by radib             #+#    #+#             */
/*   Updated: 2025/10/27 16:27:22 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	give_forks(int i, t_table *t, t_arg *arg)
{
	while (++i < arg->nop)
	{
		t->p[i]->l_f = t->mutex[i];
		if (i + 1 != arg->nop)
			t->p[i]->r_f = t->mutex[i + 1];
		else
			t->p[i]->r_f = t->mutex[0];
	}
}

int	free_struct(int i, t_table *t, int y, t_arg *arg)
{
	if (y >= 4)
		pthread_mutex_destroy(t->p[i]->check);
	if (y >= 3)
		free(t->mutex[i]);
	if (y >= 2)
		free(t->p[i]->check);
	if (y >= 1)
		free(t->p[i]);
	while (--i >= 0)
	{
		pthread_mutex_destroy(t->mutex[i]);
		pthread_mutex_destroy(t->p[i]->check);
		free(t->mutex[i]);
		free(t->p[i]->check);
		free(t->p[i]);
		pthread_join(t->thread[i + 1], NULL);
	}
	pthread_join(t->thread[i + 1], NULL);
	free_x(5, t, 2);
	free(arg);
	free(t->thread);
	free(t);
	return (0);
}

int	put_in_struct(int i, t_arg *arg, t_table *t)
{
	while (++i < arg->nop)
	{
		t->p[i] = malloc (sizeof(t_philo));
		if (!t->p[i])
			return (free_struct(i, t, 0, arg));
		t->p[i]->pnbr = i + 1;
		t->p[i]->nop = arg->nop;
		t->p[i]->ttd = arg->ttd;
		t->p[i]->tte = arg->tte;
		t->p[i]->tts = arg->tts;
		t->p[i]->notme = arg->notme;
		t->p[i]->timeeaten = 0;
		t->p[i]->table = t;
		t->p[i]->check = malloc (sizeof(pthread_mutex_t));
		if (!t->p[i]->check)
			return (free_struct(i, t, 1, arg));
		t->mutex[i] = malloc (sizeof(pthread_mutex_t));
		if (!t->mutex[i])
			return (free_struct(i, t, 2, arg));
		if (pthread_mutex_init(t->p[i]->check, NULL) != 0)
			return (free_struct(i, t, 3, arg));
		if (pthread_mutex_init(t->mutex[i], NULL) != 0)
			return (free_struct(i, t, 4, arg));
	}
	return (1);
}

int	main(int argc, char const *argv[])
{
	int			i;
	t_arg		*arg;
	t_table		*t;
	pthread_t	*thread;

	arg = malloc (sizeof (t_arg));
	if (!arg)
		return (0);
	verif_argc(arg, argc, (char **)argv);
	t = malloc (sizeof (t_table));
	thread = malloc (sizeof(pthread_t) * (ft_atoi(argv[1], 1, 0, 0) + 1));
	if (!anti_leak(arg, t, thread, argv))
		return (0);
	pthread_mutex_lock(t->startallowed);
	i = -1;
	while (++i < arg->nop && usleep(1000) == 0)
		pthread_create(&thread[i], NULL, philosophers, t->p[i]);
	t->timeatstart = time_at_start();
	createandcheck(0, t);
	pthread_create(&thread[i], NULL, watchers, t);
	pthread_mutex_unlock(t->startallowed);
	while (createandcheck(2, t) != -1)
		usleep(1000);
	return (free_struct(arg->nop, t, 0, arg));
}
