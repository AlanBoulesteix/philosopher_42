/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:29:28 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/14 14:29:14 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_mutex(t_philo *philo, char *str)
{
	long long			time;
	long long			time_start;

	pthread_mutex_lock(&philo->table->mutex_print);
	time_start = philo->table->time_start;
	time = get_time();
	if (!check_dead(philo))
	{
		printf("%lld ", time - time_start);
		printf("%d", philo->num);
		printf(" %s", str);
	}
	pthread_mutex_unlock(&philo->table->mutex_print);
}

bool	check_dead(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->table->mutex_check_dead);
	dead = philo->table->dead;
	pthread_mutex_unlock(&philo->table->mutex_check_dead);
	return (dead == 1);
}

long long	check_last_meal(t_philo *philo)
{
	long long	val;

	pthread_mutex_lock(&philo->check_meal);
	val = philo->last_meal;
	pthread_mutex_unlock(&philo->check_meal);
	return (val);
}
