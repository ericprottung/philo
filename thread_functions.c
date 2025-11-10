/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 09:39:30 by eprottun          #+#    #+#             */
/*   Updated: 2025/11/10 12:09:42 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*even_total_and_id(void *data)
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
		pthread_mutex_lock(right_fork);
		ft_output(me, "%lld %d has taken a fork\n", RIGHT);
		pthread_mutex_lock(left_fork);
		ft_output(me, "%lld %d has taken a fork\n", BOTH);
		ft_eat(me);
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
		ft_sleep(me);
		ft_output(me, "%lld %d is thinking\n", NO);
	}
	return (NULL);
}

void	*even_total_odd_id(void *data)
{
	t_philosopher	*me;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	me = (t_philosopher	*)data;
	left_fork = &me->shared->forks[me->id - 1];
	right_fork = &me->shared->forks[me->id];
	while (1)
	{
		ft_sleep(me);
		ft_output(me, "%lld %d is thinking\n", NO);
		pthread_mutex_lock(left_fork);
		ft_output(me, "%lld %d has taken a fork\n", LEFT);
		pthread_mutex_lock(right_fork);
		ft_output(me, "%lld %d has taken a fork\n", BOTH);
		ft_eat(me);
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
	}
	return (NULL);
}

void	*odd_total_even_id(void *data)
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
		pthread_mutex_lock(right_fork);
		ft_output(me, "%lld %d has taken a fork\n", RIGHT);
		pthread_mutex_lock(left_fork);
		ft_output(me, "%lld %d has taken a fork\n", BOTH);
		ft_eat(me);
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
		ft_sleep(me);
		ft_think(me);
	}
	return (NULL);
}

void	*odd_total_and_id(void *data)
{
	t_philosopher	*me;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	me = (t_philosopher	*)data;
	left_fork = &me->shared->forks[me->id - 1];
	right_fork = &me->shared->forks[me->id];
	while (1)
	{
		ft_think(me);
		pthread_mutex_lock(left_fork);
		ft_output(me, "%lld %d has taken a fork\n", LEFT);
		pthread_mutex_lock(right_fork);
		ft_output(me, "%lld %d has taken a fork\n", BOTH);
		ft_eat(me);
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
		ft_sleep(me);
	}
	return (NULL);
}

void	*last_id(void *data)
{
	t_philosopher	*me;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	me = (t_philosopher	*)data;
	left_fork = &me->shared->forks[me->id - 1];
	right_fork = &me->shared->forks[me->id];
	while (1)
	{
		ft_sleep(me);
		ft_think(me);
		pthread_mutex_lock(left_fork);
		ft_output(me, "%lld %d has taken a fork\n", LEFT);
		pthread_mutex_lock(right_fork);
		ft_output(me, "%lld %d has taken a fork\n", BOTH);
		ft_eat(me);
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
	}
	return (NULL);
}

