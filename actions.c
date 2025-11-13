/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:13:19 by eprottun          #+#    #+#             */
/*   Updated: 2025/11/13 16:25:32 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	unlock_forks(t_philosopher *me, int eat_call)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	if (me->id == 0)
		left_fork = &me->shared->forks[me->shared->total_philos - 1].key;
	else
		left_fork = &me->shared->forks[me->id - 1].key;
	right_fork = &me->shared->forks[me->id].key;
	if (eat_call == BOTH)
	{
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
	}
	else if (eat_call == LEFT)
		pthread_mutex_unlock(left_fork);
	else if (eat_call == RIGHT)
		pthread_mutex_unlock(right_fork);
}

int	output(t_philosopher *me, char *msg, int eat_call)
{
	long long	print_time;

	pthread_mutex_lock(&me->shared->print);
	if (me->shared->death == 1)
	{
		pthread_mutex_unlock(&me->shared->print);
		if (eat_call)
			unlock_forks(me, eat_call);
		return (1);
	}
	print_time = get_time() - me->shared->start_time;
	printf(msg, print_time, me->id);
	pthread_mutex_unlock(&me->shared->print);
	return (0);
}

void	eat(t_philosopher *me)
{
	long long	start_time;

	if (output(me, "%lld %d is eating\n", BOTH))
		return ;
	pthread_mutex_lock(&me->meal_info);
	me->last_meal = get_time();
	start_time = me->last_meal;
	pthread_mutex_unlock(&me->meal_info);
	efficient_sleep(me->shared->eat_time);
	pthread_mutex_lock(&me->meal_info);
	me->meal_count++;
	pthread_mutex_unlock(&me->meal_info);
}

void	think(t_philosopher *me, long long think_time)
{
	long long	start_time;

	if (output(me, "%lld %d is thinking\n", NO))
		return ;
	if (think_time < 0)
		return ;
	start_time = get_time();
	efficient_sleep(think_time);
}

void	good_night(t_philosopher *me)
{
	size_t	start_time;

	if (output(me, "%lld %d is sleeping\n", NO))
		return ;
	start_time = get_time();
	efficient_sleep(me->shared->sleep_time);
}
