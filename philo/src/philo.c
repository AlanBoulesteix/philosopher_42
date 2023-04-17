/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:12:26 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/17 12:43:52 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	eating(t_philo *philo, t_table *table)
{
	if (table->nb_philo == 1)
	{
		pthread_mutex_lock(&table->forks[philo->f2]);
		printf_mutex(philo, "has taken a fork\n");
		while (!check_dead(philo))
			usleep(10);
		pthread_mutex_unlock(&table->forks[philo->f2]);
		return (0);
	}
	if (philo->num % 2 == 0)
	{
		usleep(500);
		if (eating_even(philo, table) == 0)
			return (0);
	}
	else
	{
		if (eating_odd(philo, table) == 0)
			return (0);
	}
	return (1);
}

void	thinking(t_table *table, t_philo *philo)
{
	usleep(10);
	printf_mutex(philo, "is thinking\n");
	if ((table->nb_philo % 2 == 0) || table->die_t >= 2 * \
			table->eat_t + table->sleep_t)
		waiting(table->eat_t - table->sleep_t + 1);
	else
		waiting(table->die_t);
	usleep(10);
}

void	*thread_routine(void *data)
{
	t_philo	*philo;
	t_table	*table;
	int		count;

	count = 0;
	philo = (t_philo *)data;
	table = philo->table;
	pthread_mutex_lock(&philo->check_meal);
	philo->last_meal = -table->time_start + get_time();
	pthread_mutex_unlock(&philo->check_meal);
	while (1)
	{
		if (eating(philo, table) == 0)
			break ;
		count++;
		if (count == (int)philo->table->nb_eat_t)
		{
			philo->table->all_ate = true;
			break ;
		}
		usleep(10);
		sleeping(philo);
		thinking(table, philo);
	}
	return (NULL);
}

void	death_supervisor(t_table *table)
{
	long long		time;
	unsigned int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		time = get_time() - table->time_start;
		if (time - check_last_meal(&table->philo[i]) >= table->die_t)
		{
			philo_death(table, i);
			break ;
		}
		if (i == table->nb_philo - 1 && !table->all_ate)
			i = -1;
		usleep(100);
	}
}

int	philo(t_table *table)
{
	unsigned int	i;

	i = -1;
	table->time_start = get_time();
	if (table->time_start == -1)
		return (ERROR);
	while (++i < table->nb_philo)
		if (pthread_create(&(table->philo[i].tid), NULL, thread_routine, \
					&table->philo[i]) != 0)
			return (ERROR);
	death_supervisor(table);
	i = -1;
	while (++i < table->nb_philo)
		if (pthread_join(table->philo[i].tid, NULL) != 0)
			return (ERROR);
	return (0);
}
