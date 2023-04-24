/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:22:50 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/24 13:39:51 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	long long			time;
	struct timeval		tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

int	waiting(t_table *table, t_philo *philo, unsigned int wait)
{
	long long	time;
	long long	target;

	time = get_time();
	target = wait;
	while (get_time() - time < target)
	{
		if (check_dead(table) == 1 || philo_death(table, philo) == 1)
				return (1);
/*
		if (get_time() - table->time_start - philo->t_meal >= table->die_t)
		{
				pthread_mutex_lock(&table->mutex_check_dead);	
				table->dead = true;
				printf_mutex(philo, "died");
				pthread_mutex_unlock(&table->mutex_check_dead);	
			return (1);
		}
*/		usleep(1);
		if (check_dead(table) == 1)
				return (1);
		if (get_time() - table->time_start - philo->t_meal >= table->die_t)
		{
				pthread_mutex_lock(&table->mutex_check_dead);	
				table->dead = true;
				printf_mutex(philo, "died");
				pthread_mutex_unlock(&table->mutex_check_dead);	
			return (1);
		}
	}
	return (0);
}

int	all_ate(t_table *table)
{
	unsigned int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		if (table->philo[i].full >= table->nb_eat_t)
			return (1);
	}
	return (0);
}
