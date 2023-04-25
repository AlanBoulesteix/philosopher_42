/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:56:32 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/25 16:16:14 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_odd_norm(t_table *table, t_philo *philo)
{
	if (check_dead(table) == 1)
		return (1);
	pthread_mutex_lock(&table->forks[philo->f2]);
	if (get_time() - table->time_start - philo->t_meal >= table->die_t)
	{
		pthread_mutex_unlock(&table->forks[philo->f2]);
		return (philo_death(table, philo));
	}
	printf_mutex(philo, "has taken a fork");
	pthread_mutex_lock(&table->forks[philo->f1]);
	if (check_dead(table) == 1)
	{
		pthread_mutex_unlock(&table->forks[philo->f1]);
		pthread_mutex_unlock(&table->forks[philo->f2]);
		return (1);
	}
	return (0);
}

int	eating_odd(t_table *table, t_philo *philo)
{
	if (eat_odd_norm(table, philo) == 1)
		return (1);
	if (get_time() - table->time_start - philo->t_meal >= table->die_t)
	{
		pthread_mutex_unlock(&table->forks[philo->f1]);
		pthread_mutex_unlock(&table->forks[philo->f2]);
		return (philo_death(table, philo));
	}
	printf_mutex(philo, "has taken a fork");
	printf_mutex(philo, "is eating");
	philo->full ++;
	fiful_belly(table, philo);
	philo->t_meal = get_time() - table->time_start;
	waiting(table, philo, table->eat_t);
	pthread_mutex_unlock(&table->forks[philo->f1]);
	pthread_mutex_unlock(&table->forks[philo->f2]);
	return (0);
}

int	eat_even_norm(t_table *table, t_philo *philo)
{
	if (check_dead(table) == 1)
		return (1);
	pthread_mutex_lock(&table->forks[philo->f1]);
	if (get_time() - table->time_start - philo->t_meal >= table->die_t)
	{
		pthread_mutex_unlock(&table->forks[philo->f2]);
		return (philo_death(table, philo));
	}
	printf_mutex(philo, "has taken a fork");
	pthread_mutex_lock(&table->forks[philo->f2]);
	if (check_dead(table) == 1)
	{
		pthread_mutex_unlock(&table->forks[philo->f2]);
		pthread_mutex_unlock(&table->forks[philo->f1]);
		return (1);
	}
	return (0);
}

int	eating_even(t_table *table, t_philo *philo)
{
	if (eat_even_norm(table, philo) == 1)
		return (1);
	if (get_time() - table->time_start - philo->t_meal >= table->die_t)
	{
		pthread_mutex_unlock(&table->forks[philo->f2]);
		pthread_mutex_unlock(&table->forks[philo->f1]);
		return (philo_death(table, philo));
	}
	printf_mutex(philo, "has taken a fork");
	printf_mutex(philo, "is eating");
	philo->full++;
	fiful_belly(table, philo);
	philo->t_meal = get_time() - table->time_start;
	waiting(table, philo, table->eat_t);
	pthread_mutex_unlock(&table->forks[philo->f2]);
	pthread_mutex_unlock(&table->forks[philo->f1]);
	return (0);
}
