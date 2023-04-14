/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:55:26 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/14 16:48:09 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	printf_mutex(philo, "is sleeping\n");
	waiting(philo->table->eat_t);
}

void	philo_death(t_table *table, unsigned int i)
{
	pthread_mutex_lock(&table->mutex_check_dead);
	table->dead = 1;
	pthread_mutex_unlock(&table->mutex_check_dead);
	pthread_mutex_lock(&table->mutex_print);
	printf("%lld %d died\n", get_time() - table->time_start, i + 1);
	pthread_mutex_unlock(&table->mutex_print);
}

int	eating_even(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->forks[philo->f1]);
	if (check_dead(philo))
	{
		pthread_mutex_unlock(&table->forks[philo->f1]);
		return (0);
	}
	printf_mutex(philo, "has taken a fork\n");
	pthread_mutex_lock(&table->forks[philo->f2]);
	if (check_dead(philo))
	{
		pthread_mutex_unlock(&table->forks[philo->f2]);
		pthread_mutex_unlock(&table->forks[philo->f1]);
		return (0);
	}
	printf_mutex(philo, "has taken a fork\n");
	printf_mutex(philo, "is eating\n");
	waiting(philo->table->eat_t);
	pthread_mutex_lock(&philo->check_meal);
	philo->last_meal = get_time() - table->time_start;
	pthread_mutex_unlock(&philo->check_meal);
	pthread_mutex_unlock(&table->forks[philo->f2]);
	pthread_mutex_unlock(&table->forks[philo->f1]);
	return (1);
}

int	eating_odd(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->forks[philo->f2]);
	if (check_dead(philo))
	{
		pthread_mutex_unlock(&table->forks[philo->f2]);
		return (0);
	}
	printf_mutex(philo, "has taken a fork\n");
	pthread_mutex_lock(&table->forks[philo->f1]);
	if (check_dead(philo))
	{
		pthread_mutex_unlock(&table->forks[philo->f1]);
		pthread_mutex_unlock(&table->forks[philo->f2]);
		return (0);
	}
	printf_mutex(philo, "has taken a fork\n");
	printf_mutex(philo, "is eating\n");
	waiting(philo->table->eat_t);
	pthread_mutex_lock(&philo->check_meal);
	philo->last_meal = get_time() - table->time_start;
	pthread_mutex_unlock(&philo->check_meal);
	pthread_mutex_unlock(&table->forks[philo->f1]);
	pthread_mutex_unlock(&table->forks[philo->f2]);
	return (1);
}
