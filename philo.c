/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:55:48 by radib             #+#    #+#             */
/*   Updated: 2025/10/24 15:21:27 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eat(t_philo *p, int x, int timeeating, long long time)
{
	if (p->pnbr % 2 == 1)
		x = locktwo(p, 1);
	else if (p->pnbr % 2 == 0)
		x = locktwo(p, 2);
	time = timems(p->table);
	pthread_mutex_lock(p->check);
	p->timelasteaten = time;
	pthread_mutex_unlock(p->check);
	timeeating = 0;
	prnt_s("is eating", time, p->pnbr, p->table);
	while (timeeating < p->tte && createandcheck(2, p->table) == 1)
	{
		timeeating = timems(p->table) - time;
		usleep(10);
	}
	unlocktwo(p, x);
	return (1);
}

int	sleep_philo(t_philo *p)
{
	long long	time;
	int			timeslept;

	timeslept = 0;
	time = timems(p->table);
	prnt_s("is sleeping", time, p->pnbr, p->table);
	while (timeslept < p->tts)
	{
		timeslept = timems(p->table) - time;
		usleep(10);
	}
	return (1);
}

void	think(t_philo *p)
{
	int			timethinking;
	long long	time;
	int			max_think;

	max_think = p->ttd - (p->tte + p->tts);
	timethinking = 0;
	time = timems(p->table);
	prnt_s("is thinking", time, p->pnbr, p->table);
	while (timethinking + 10 < max_think)
	{
		timethinking = timems(p->table) - time;
		usleep(10);
	}
}

int	everyone_ate_enough(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->p[0]->nop)
	{
		pthread_mutex_lock(t->p[i]->check);
		if (t->p[i]->timeeaten < t->p[i]->notme)
		{
			pthread_mutex_unlock(t->p[i]->check);
			return (0);
		}
		pthread_mutex_unlock(t->p[i]->check);
		i++;
	}
	return (1);
}

int	check_death(int x, t_table *t)
{
	pthread_mutex_lock(t->p[x]->check);
	if (timems(t) - t->p[x]->timelasteaten >= t->p[x]->ttd)
	{
		prnt_s("died", timems(t), t->p[x]->pnbr, t);
		pthread_mutex_unlock(t->p[x]->check);
		return (1);
	}
	pthread_mutex_unlock(t->p[x]->check);
	return (0);
}
