/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprottun <eprottun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:13:19 by eprottun          #+#    #+#             */
/*   Updated: 2025/11/10 12:32:57 by eprottun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	unlock_forks(t_philosopher *me, int eat_call)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	
	if (me->id == 0)
		left_fork = &me->shared->forks[me->shared->total_philos - 1];
	else
		left_fork = &me->shared->forks[me->id - 1];
	right_fork = &me->shared->forks[me->id];
	if (eat_call == BOTH)
	{
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
	}
	else if	(eat_call == LEFT)
		pthread_mutex_unlock(left_fork);
	else if (eat_call == RIGHT)
		pthread_mutex_unlock(right_fork);
}

void	ft_output(t_philosopher *me, char *msg, int eat_call)
{
	long long print_time;
	
	usleep(0);
	pthread_mutex_lock(&me->shared->output);
	if (me->shared->death == 1)
	{
		unlock_forks(me, eat_call);
		pthread_exit(NULL);
	}
	print_time = ft_get_current_time() - me->shared->start_time;
	printf(msg, print_time, me->id);
	pthread_mutex_unlock(&me->shared->output);
}

void	ft_eat(t_philosopher *me)
{
	long long	start_time;

	ft_output(me, "%lld %d is eating\n", BOTH);
	pthread_mutex_lock(&me->meal_info);
	me->last_meal = ft_get_current_time();
	start_time = me->last_meal;
	me->meal_count++;
	pthread_mutex_unlock(&me->meal_info);
	while (ft_get_current_time() - start_time < me->shared->eat_time)
		usleep(2000);
}

void	ft_think(t_philosopher *me)
{
	long long	start_time;
	long long	think_time;
	
	ft_output(me, "%lld %d is thinking\n", NO);
	start_time = ft_get_current_time();
	think_time = me->shared->eat_time * 2 - me->shared->sleep_time;
	if (think_time < 0)
		return ;
	while (ft_get_current_time() - start_time < think_time)
		usleep(2000);
}

void	ft_sleep(t_philosopher *me)
{
	size_t	start_time;

	ft_output(me, "%lld %d is sleeping\n", NO);
	start_time = ft_get_current_time();
	while (ft_get_current_time() - start_time < me->shared->sleep_time)
		usleep(2000);
}
