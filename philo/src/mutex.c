/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:29:28 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/24 13:37:57 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_mutex(t_philo *philo, char *str)
{
	int	stamp;

	pthread_mutex_lock(&philo->table->mutex_print);
	stamp = get_time() - philo->table->time_start;
	printf("%d %d %s\n", stamp, philo->num, str);
	pthread_mutex_unlock(&philo->table->mutex_print);
}

int	check_dead(t_table *table)
{
	int	check;

	pthread_mutex_lock(&table->mutex_check_dead);
	check = (table->dead == true);
	pthread_mutex_unlock(&table->mutex_check_dead);
	return (check);
}

int	philo_death(t_table *table, t_philo *philo)
{
		if (get_time() - table->time_start - philo->t_meal >= table->die_t)
		{
				pthread_mutex_lock(&table->mutex_check_dead);	
				table->dead = true;
				printf_mutex(philo, "died");
				pthread_mutex_unlock(&table->mutex_check_dead);	
			return (1);
		}
		else
			return (0);
}
