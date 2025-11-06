/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:14:19 by eprottun          #+#    #+#             */
/*   Updated: 2025/11/06 14:28:05 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILOSOPHERS_H
# define FT_PHILOSOPHERS_H

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

# define YES 1
# define NO 0

typedef struct s_shared {
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t dead_access;
	pthread_mutex_t low_prio;
	pthread_mutex_t next;
	pthread_mutex_t last_meal_access;
	pthread_mutex_t output;
	int				*dead;
	int				total_philos;
	long long		start_time;
	long long		time_to_die;
	long long		eat_time;
	long long		sleep_time;
	int		meal_amount;
	struct	timeval tv;
}	t_shared;

typedef struct s_philosopher
{
	t_shared	*shared;
	int			id;
	long long	last_meal;
	int			prio;
	int			meal_count;
}	t_philosopher;

int			ft_atoi(const char *str);
void		ft_init_rules(t_shared *shared, int argc, char *argv[]);

void		*ft_philosopher(void *data);
long long 	ft_get_current_time();

void		ft_output(t_philosopher *me, char *msg, int death_call);
void		ft_death(t_philosopher *me);
void		ft_eat(t_philosopher *me);
void		ft_think(t_philosopher *me);
void		ft_sleep(t_philosopher *me);

#endif