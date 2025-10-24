/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:55:20 by radib             #+#    #+#             */
/*   Updated: 2025/10/24 15:53:52 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_mutex_error(int i, int x)
{
	i++;
	x++;
	return (0);
}

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

int	put_in_struct(int i, t_arg *arg, t_table *t)
{
	while (++i < arg->nop)
	{
		t->p[i] = malloc (sizeof(t_philo));
		t->p[i]->pnbr = i + 1;
		t->p[i]->nop = arg->nop;
		t->p[i]->ttd = arg->ttd;
		t->p[i]->tte = arg->tte;
		t->p[i]->tts = arg->tts;
		t->p[i]->notme = arg->notme;
		t->p[i]->timeeaten = 0;
		t->p[i]->table = t;
		t->p[i]->timelasteaten = 0;
		t->p[i]->check = malloc (sizeof(pthread_mutex_t));
		if (pthread_mutex_init(t->p[i]->check, NULL) != 0)
			return (printf("mutex error\n"));
		t->mutex[i] = malloc (sizeof(pthread_mutex_t));
		if (pthread_mutex_init(t->mutex[i], NULL) != 0)
			return (printf("mutex error\n"));
	}
	give_forks(-1, t, arg);
	return (0);
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
	t->mutex = malloc(sizeof(pthread_mutex_t *) * arg->nop);
	t->startallowed = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(t->startallowed, NULL) != 0)
		return (printf("mutex error\n"));
	t->checkallowed = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(t->checkallowed, NULL) != 0)
		return (printf("mutex error\n"));
	t->print = malloc(sizeof(pthread_mutex_t));
	if (pthread_mutex_init(t->print, NULL) != 0)
		return (printf("mutex error\n"));
	t->startallowed = malloc (sizeof(pthread_mutex_t));
	if (pthread_mutex_init(t->startallowed, NULL) != 0)
		return (printf("mutex error\n"));
	t->thread = thread;
	return (0);
}

int	main(int argc, char const *argv[])
{
	int			i;
	t_arg		*arg;
	t_table		*t;
	pthread_t	*thread;

	arg = malloc (sizeof (t_arg));
	verif_argc(arg, argc, (char **)argv);
	t = malloc (sizeof (t_table));
	thread = malloc (sizeof(pthread_t) * (ft_atoi(argv[1], 1, 0, 0) + 1));
	if (assign(arg, t, thread, argv) || put_in_struct(-1, arg, t))
		return (free_mutex_error(0, 0));
	pthread_mutex_lock(t->startallowed);
	i = -1;
	while (++i < arg->nop && usleep(1000) == 0)
		pthread_create(&thread[i], NULL, philosophers, t->p[i]);
	t->timeatstart = time_at_start();
	createandcheck(0, t);
	pthread_mutex_unlock(t->startallowed);
	pthread_create(&thread[i], NULL, watchers, t);
	while (createandcheck(2, t) != -1)
		usleep(1000000);
	return (free_all(-1, arg, t, thread));
}
