/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: radib <radib@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 21:26:37 by radib             #+#    #+#             */
/*   Updated: 2025/10/28 14:06:38 by radib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>

typedef struct arg
{
	int					nop;
	int					ttd;
	int					tte;
	int					tts;
	int					notme;
}				t_arg;

typedef struct t	t_table;

typedef struct p
{
	int					pnbr;
	int					nop;
	int					ttd;
	int					tte;
	int					tts;
	int					timesincelasteat;
	int					timelasteaten;
	int					timeeaten;
	int					notme;
	pthread_mutex_t		*check;
	pthread_mutex_t		*l_f;
	pthread_mutex_t		*r_f;
	t_table				*table;
}				t_philo;

typedef struct t
{
	t_philo				**p;
	pthread_mutex_t		*print;
	pthread_mutex_t		**mutex;
	pthread_mutex_t		*startallowed;
	pthread_mutex_t		*checkallowed;
	long long			timeatstart;
	pthread_t			*thread;
	int					everyone_is_alive;
}				t_table;

long		ft_atoi(const char *nptr, int sign, int total, int i);
int			createandcheck(int x, t_table *t);
void		prnt_s(char *s, int philo, t_table *t);
long long	timems(t_table *t);
int			hardcoded_one(int ttd);
void		*philosophers(void *p);
void		*watchers(void *table);
long long	timems(t_table *t);
int			eat(t_philo *p, int x, int timeeating, long long time);
int			sleep_philo(t_philo *p);
void		think(t_philo *p, int start);
int			everyone_ate_enough(t_table *t);
int			check_death(int x, t_table *t);
int			unlocktwo(t_philo *p, int x);
int			locktwo(t_philo *p, int x);
long long	time_at_start(void);
int			verif_argc(t_arg *arg, int argc, char *argv[]);
int			free_all(int i, t_arg *arg, t_table *t, pthread_t *thread);
int			put_in_struct(int i, t_arg *arg, t_table *t);
int			anti_leak(t_arg *arg, t_table *t, pthread_t *th, const char **argv);
void		give_forks(int i, t_table *t, t_arg *arg);
int			free_x(int x, t_table *t, int y);
int			check(t_table *t);

#endif