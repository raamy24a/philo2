/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:53:16 by radib             #+#    #+#             */
/*   Updated: 2025/11/03 13:45:01 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	unlocktwo(t_philo *p, int x)
{
	if (x == 2)
	{
		pthread_mutex_unlock(p->l_f);
		pthread_mutex_unlock(p->r_f);
		return (x);
	}
	if (x == 1)
	{
		pthread_mutex_unlock(p->r_f);
		pthread_mutex_unlock(p->l_f);
		return (x);
	}
	return (-1);
}

int	locktwo(t_philo *p, int x)
{
	if (x == 2)
	{
		pthread_mutex_lock(p->l_f);
		prnt_s("has taken a fork\n", p->pnbr, p->table, 17);
		pthread_mutex_lock(p->r_f);
		prnt_s("has taken a fork\n", p->pnbr, p->table, 17);
		return (x);
	}
	if (x == 1)
	{
		pthread_mutex_lock(p->r_f);
		prnt_s("has taken a fork\n", p->pnbr, p->table, 17);
		pthread_mutex_lock(p->l_f);
		prnt_s("has taken a fork\n", p->pnbr, p->table, 17);
		return (x);
	}
	return (x);
}

long	ft_atoi(const char *nptr, int sign, int total, int i)
{
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		total *= 10;
		total += nptr[i] - '0';
		if ((total * sign > 0) && sign == -1)
			return (-20000000000);
		if ((total < 0) && sign == 1)
			return (-20000000000);
		i++;
	}
	if (!(nptr[i]) && !(sign == -1 && total == 0 && i == 1))
		return ((long)(total * sign));
	return (-20000000000);
}

long long	timems(t_table *t)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - t->timeatstart);
}

int	hardcoded_one(int ttd)
{
	printf("0 1 has taken a fork\n");
	usleep(1000 * ttd);
	printf("%d 1 died\n", ttd);
	return (0);
}
