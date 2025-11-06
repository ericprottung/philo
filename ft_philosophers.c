/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:15:45 by eprottun          #+#    #+#             */
/*   Updated: 2025/11/06 16:12:31 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philosophers.h"

void	priority_bool(t_philosopher *me)
{
	if (!me->meal_count)
		me->prio = YES;
	else if (me->shared->total_philos % 2 != 0
		&& (ft_get_current_time() - me->last_meal) * 1.5 > me->shared->time_to_die)
		me->prio = YES;
	else
		me->prio = YES;
	printf("id: %d, my prio: %d, time: %lld\n", me->id, me->prio, (ft_get_current_time() - me->last_meal) * 2);
	fflush(stdout);
}

void	*ft_philosopher(void *data)
{
	t_philosopher	*me;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	me = (t_philosopher	*)data;
	if (me->id == 0)
		left_fork = &me->shared->forks[me->shared->total_philos - 1];
	else
		left_fork = &me->shared->forks[me->id - 1];
	right_fork = &me->shared->forks[me->id];
	while (1)
	{
		if (me->id % 2 == 0)
		{
			pthread_mutex_lock(right_fork);
			ft_output(me, "%lld %d has taken a fork\n", NO);
			pthread_mutex_lock(left_fork);
			ft_output(me, "%lld %d has taken a fork\n", NO);
		}
		else
		{
			pthread_mutex_lock(left_fork);
			ft_output(me, "%lld %d has taken a fork\n", NO);
			pthread_mutex_lock(right_fork);
			ft_output(me, "%lld %d has taken a fork\n", NO);
		}
		ft_eat(me);
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
		ft_sleep(me);
		ft_think(me);
	}
	return (NULL);
}

long long 	ft_get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_death(t_philosopher *me)
{
	size_t	iter;
	
	ft_output(me, "%lld %d died\n", YES);
	pthread_mutex_lock(&me->shared->dead_access);
	me->shared->dead[me->id] = 1;
	pthread_mutex_unlock(&me->shared->dead_access);
}

void	ft_stopwatch(t_shared *shared, t_philosopher *philo)
{
	size_t			iter;
	
	while (1)
	{
		iter = 0;
		while (iter < shared->total_philos)
		{
			pthread_mutex_lock(&shared->last_meal_access);
			if (ft_get_current_time() - philo[iter].last_meal > shared->time_to_die)
			{
				ft_death(&philo[iter]);
				pthread_mutex_unlock(&shared->last_meal_access);
				return ;
			}
			pthread_mutex_unlock(&shared->last_meal_access);
			iter++;
		}
		usleep(1000);
	}
}

int	main(int argc, char *argv[])
{
	size_t			iter;
	t_shared		*shared;
	t_philosopher	*philo;

	iter = 0;
	shared = malloc(sizeof(t_shared));
	ft_init_rules(shared, argc, argv);
	philo = malloc(shared->total_philos * sizeof(t_philosopher));
	shared->dead = malloc(shared->total_philos * sizeof(int));
	shared->forks = malloc(shared->total_philos * sizeof(pthread_mutex_t));
	shared->threads = malloc(shared->total_philos * sizeof(pthread_t));
	while (iter < shared->total_philos)
	{
		pthread_mutex_init(&shared->forks[iter], NULL);
		shared->dead[iter] = 0;
		iter++;
	}
	pthread_mutex_init(&shared->dead_access, NULL);
	pthread_mutex_init(&shared->output, NULL);
	pthread_mutex_init(&shared->last_meal_access, NULL);
	shared->start_time = ft_get_current_time();
	iter = 0;
	while(iter < shared->total_philos)
	{
		philo[iter].shared = shared;
		philo[iter].id = iter;
		pthread_mutex_lock(&shared->last_meal_access);
		philo[iter].last_meal = ft_get_current_time();
		philo[iter].meal_count = 0;
		pthread_mutex_unlock(&shared->last_meal_access);
		pthread_create(&shared->threads[iter], NULL, ft_philosopher, &philo[iter]);
		iter++;
	}
	iter = 0;
	ft_stopwatch(shared, philo);
	while (iter < shared->total_philos)
	{
		pthread_join(shared->threads[iter], NULL);
		iter++;
	}
	pthread_mutex_destroy(&shared->dead_access);
	pthread_mutex_destroy(&shared->output);
	pthread_mutex_destroy(&shared->last_meal_access);
	return (0);
}