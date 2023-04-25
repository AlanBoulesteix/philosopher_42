/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:22:50 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/25 12:42:32 by aboulest         ###   ########.fr       */
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

int	waiting(t_table *table, t_philo *philo, int wait)
{
	long long	time;
	long long	target;

	time = get_time();
	target = wait;
	while (get_time() - time < target)
	{
		usleep(1000);
		if (check_dead(table) == 1)
			return (1);
		if (get_time() - table->time_start - philo->t_meal >= table->die_t)
			return (philo_death(table, philo));
	}
	return (0);
}

int	all_ate(t_table *table)
{
	unsigned int	i;
	bool			check;

	i = -1;
	check = 0;
	pthread_mutex_lock(&table->mutex_all_ate);
	if (table->all_ate == table->nb_philo)
		check = 1;
	pthread_mutex_unlock(&table->mutex_all_ate);
	return (check);
}
