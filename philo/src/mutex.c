/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:29:28 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/25 16:17:16 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_mutex(t_philo *philo, char *str)
{
	int	stamp;

	pthread_mutex_lock(&philo->table->mutex_print);
	if (!check_dead(philo->table))
	{
		stamp = get_time() - philo->table->time_start;
		printf("%d %d %s\n", stamp, philo->num, str);
	}
	pthread_mutex_unlock(&philo->table->mutex_print);
}

int	check_dead(t_table *table)
{
	int	check;

	pthread_mutex_lock(&table->mutex_check_dead);
	check = table->dead;
	pthread_mutex_unlock(&table->mutex_check_dead);
	return (check);
}

int	philo_death(t_table *table, t_philo *philo)
{
	int	stamp;

	if (check_dead(table))
		return (1);
	pthread_mutex_lock(&table->mutex_check_dead);
	if (table->dead == true)
	{
		pthread_mutex_unlock(&table->mutex_check_dead);
		return (1);
	}
	table->dead = true;
	pthread_mutex_unlock(&table->mutex_check_dead);
	pthread_mutex_lock(&table->mutex_print);
	stamp = get_time() - philo->table->time_start;
	printf("%d %d %s\n", stamp, philo->num, "died");
	pthread_mutex_unlock(&table->mutex_print);
	return (1);
}

void	fiful_belly(t_table *table, t_philo *philo)
{
	if (philo->full == table->nb_eat_t)
	{
		pthread_mutex_lock(&table->mutex_all_ate);
		table->all_ate ++;
		pthread_mutex_unlock(&table->mutex_all_ate);
	}
}
