/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:22:10 by radib             #+#    #+#             */
/*   Updated: 2025/10/22 16:33:09 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	prnt_s(char *s, unsigned long long time, int philo, t_table *t)
{
	if (createandcheck(2, t) == 1)
	{
		pthread_mutex_lock(t->print);
		time = timems(t);
		printf("%lld %d %s\n", time, philo, s);
		pthread_mutex_unlock(t->print);
	}
}

int	createandcheck(int x, t_table *t)
{
	if (x == 0)
		t->everyone_is_alive = 1;
	if (x == 1)
	{
		pthread_mutex_lock(t->checkallowed);
		t->everyone_is_alive = 0;
		pthread_mutex_unlock(t->checkallowed);
	}
	if (x == 2)
	{
		pthread_mutex_lock(t->checkallowed);
		if (t->everyone_is_alive == 0)
			x = 3;
		pthread_mutex_unlock(t->checkallowed);
	}
	if (x == 3)
		return (-1);
	return (1);
}
