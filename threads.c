/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:59:01 by radib             #+#    #+#             */
/*   Updated: 2025/10/28 13:56:12 by radib            ###   ########.fr       */
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
				alive = createandcheck(1, table);
			x++;
		}
		if (everyone_ate_enough(t) == 1 && alive == 1)
		{
			alive = createandcheck(1, table);
			return (NULL);
		}
	}
	return (NULL);
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
			return (NULL);
		eat(philo, 0, 0, (long long) 0);
		pthread_mutex_lock(philo->check);
		philo->timeeaten++;
		pthread_mutex_unlock(philo->check);
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
