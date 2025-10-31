/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:59:01 by radib             #+#    #+#             */
/*   Updated: 2025/10/31 16:32:43 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*watchers(void *table)
{
	t_table	*t;
	int		x;
	int		alive;

	alive = 1;
	t = (t_table *) table;
	pthread_mutex_lock(t->startallowed);
	pthread_mutex_unlock(t->startallowed);
	while (alive)
	{
		x = 0;
		while (x < t->p[0]->nop && alive)
		{
			if (check_death(x, t))
			{
				alive = createandcheck(1, table);
				break ;
			}
			x++;
		}
		if (alive == 1 && everyone_ate_enough(t) == 1)
		{
			alive = createandcheck(1, table);
			return (NULL);
		}
	}
	return (NULL);
}

void	safe_eatcount(t_philo *p)
{
	pthread_mutex_lock(p->check);
	p->timeeaten++;
	pthread_mutex_unlock(p->check);
}

void	safe_stop(t_philo *p)
{
	pthread_mutex_lock(p->check);
	p->stop = 1;
	pthread_mutex_unlock(p->check);
}

void	*philosophers(void *p)
{
	t_philo	*philo;
	int		start;

	start = 1;
	philo = (t_philo *) p;
	pthread_mutex_lock(philo->table->startallowed);
	pthread_mutex_unlock(philo->table->startallowed);
	while (1)
	{
		if (start == 1 && philo->pnbr % 2 == 1)
		{
			start = 0;
			think(philo, 1);
		}
		if (createandcheck(2, philo->table) == -1)
		{
			safe_stop(philo);
			return (NULL);
		}
		eat(philo, 0, 0, (long long) 0);
		safe_eatcount(philo);
		sleep_philo(philo);
		think(philo, 0);
	}
}

long long	time_at_start(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}
