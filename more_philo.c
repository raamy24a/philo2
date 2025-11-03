/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:22:10 by radib             #+#    #+#             */
/*   Updated: 2025/11/03 13:52:55 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check(t_table *t)
{
	pthread_mutex_lock(t->checkallowed);
	if (t->everyone_is_alive == 0)
	{
		pthread_mutex_unlock(t->checkallowed);
		return (0);
	}
	pthread_mutex_unlock(t->checkallowed);
	return (1);
}

void	prnt_s(char *s, int philo, t_table *t, int i)
{
	unsigned long long	time;

	pthread_mutex_lock(t->print);
	if (check(t) == 1)
	{
		time = timems(t);
		ft_putnbr_fd(time, 1);
		write (1, " ", 1);
		ft_putnbr_fd(philo, 1);
		write (1, " ", 1);
		write (1, s, i + 1);
	}
	pthread_mutex_unlock(t->print);
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
	return (0);
}

int	invalid_input(void)
{
	printf("invalid input\n");
	return (0);
}
