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

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define YES 1
# define NO 0
# define DEATH 2
# define RIGHT 3
# define LEFT 4
# define BOTH 5
# define DINNER_DONE 6

typedef struct s_fork
{
	pthread_mutex_t	key;
	char padding[24];
}	t_fork;

typedef struct s_data
{
	pthread_t		threads[250];
	t_fork			forks[250];
	pthread_mutex_t	print;
	int				death;
	int				total_philos;
	long long		start_time;
	long long		time_to_die;
	long long		eat_time;
	long long		sleep_time;
	int				meal_amount;
	struct timeval	tv;
}	t_data;

typedef struct s_philosopher
{
	t_data			*shared;
	int				id;
	pthread_mutex_t	meal_info;
	int				prio;
	long long		last_meal;
	int				meal_count;
	char            padding[64];
}	t_philosopher;

int			ft_atoi(const char *str);
void		init_rules(t_data *shared, int argc, char *argv[]);

void		*even_total_and_id(void *data);
void		*even_total_odd_id(void *data);
void		*odd_total_even_id(void *data);
void		*odd_total_and_id(void *data);
void		*last_id(void *data);
long long	get_time(void);
void 		efficient_sleep(long long duration);

int			output(t_philosopher *me, char *msg, int eat_call);
void		end(t_philosopher *me, int reason);
void		eat(t_philosopher *me);
void	think(t_philosopher *me, long long think_time);
void		good_night(t_philosopher *me);

void		stopwatch(t_data *shared, t_philosopher *philo);

#endif
