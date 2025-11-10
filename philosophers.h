/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:14:19 by eprottun          #+#    #+#             */
/*   Updated: 2025/11/08 14:02:49 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef philosophers_H
# define philosophers_H

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

# define YES 1
# define NO 0
# define DEATH 2
# define RIGHT 3
# define LEFT 4
# define BOTH 5

typedef struct s_shared {
	pthread_t		threads[1000];
	pthread_mutex_t	forks[1000];
	pthread_mutex_t output;
	int				death;
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
	pthread_mutex_t meal_info;
	int			prio;
	long long	last_meal;
	int			meal_count;
}	t_philosopher;

int			ft_atoi(const char *str);
void		init_rules(t_shared *shared, int argc, char *argv[]);

void		*even_total_and_id(void *data);
void		*even_total_odd_id(void *data);
void		*odd_total_even_id(void *data);
void		*odd_total_and_id(void *data);
void		*last_id(void *data);
long long 	ft_get_current_time();

void		ft_output(t_philosopher *me, char *msg, int death_call);
void		ft_end(t_philosopher *me, int reason);
void		ft_eat(t_philosopher *me);
void		ft_think(t_philosopher *me);
void		ft_sleep(t_philosopher *me);

void		stopwatch(t_shared *shared, t_philosopher *philo);

#endif