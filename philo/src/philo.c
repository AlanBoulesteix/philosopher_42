/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:12:26 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/24 09:54:45 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *data)
{
	t_philo	*philo;
	t_table	*table;
	int		flag;

	philo = (t_philo *)data;
	flag = 0;
	table = philo->table;
	philo->t_meal = get_time() - table->time_start;
	while (check_dead(table) != 1 && all_ate(table) == 0)
	{
		if (check_dead(table) == 0 && get_time() - table->time_start - philo->t_meal >= table->die_t)
		{
			pthread_mutex_lock(&table->mutex_check_dead);	
			table->dead = true;
			printf_mutex(philo, "died");
			pthread_mutex_unlock(&table->mutex_check_dead);	
			return (NULL);
		}
		if (thinking(table, philo, flag) == 1)
			return (NULL);
		flag = 1;
		if (get_time() - table->time_start - philo->t_meal >= table->die_t)
		{
			pthread_mutex_lock(&table->mutex_check_dead);	
			table->dead = true;
			printf_mutex(philo, "died");
			pthread_mutex_unlock(&table->mutex_check_dead);	
		}
		if (eating(table, philo) == 1)
			return (NULL);
		if (check_dead(table) == 0 && get_time() - table->time_start - philo->t_meal >= table->die_t)
		{
			pthread_mutex_lock(&table->mutex_check_dead);	
			table->dead = true;
			printf_mutex(philo, "died");
			pthread_mutex_unlock(&table->mutex_check_dead);	
			return (NULL);
		}
		if (all_ate(table) != 0)
			return (NULL);
		if (sleeping(table, philo) == 1)
			return (NULL);
		if (check_dead(table) == 0 && get_time() - table->time_start - philo->t_meal >= table->die_t)
		{
			pthread_mutex_lock(&table->mutex_check_dead);	
			table->dead = true;
			printf_mutex(philo, "died");
			pthread_mutex_unlock(&table->mutex_check_dead);	
			return (NULL);
		}
	}
	return (NULL);
}

int	philo(t_table *table)
{
	unsigned int	i;

	i = -1;

	table->time_start = get_time();
	while (++i < table->nb_philo)
		pthread_create(&table->philo[i].tid, NULL, thread_routine, &table->philo[i]);
	i = -1;
	while (++i < table->nb_philo)
		pthread_join(table->philo[i].tid, NULL);
	return (0);
}
