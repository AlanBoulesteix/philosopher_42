/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:55:26 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/24 10:00:21 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinking(t_table *table, t_philo *philo, int flag)
{
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
	printf_mutex(philo, "is thinking");
	if (get_time() - table->time_start - philo->t_meal >= table->die_t)
	{
			pthread_mutex_lock(&table->mutex_check_dead);	
			table->dead = true;
			printf_mutex(philo, "died");
			pthread_mutex_unlock(&table->mutex_check_dead);	
		return (1);
	}
	if (flag >= 1)
	{
		if ((table->nb_philo % 2 == 0) || table->die_t >= 2 * \
				table->eat_t + table->sleep_t)
		{
			if (waiting(table, philo, table->eat_t - table->sleep_t + 1) != 0)
				return (1);
		}
		else
			if (waiting(table, philo, table->die_t) != 0)
				return (1);
	}
	return(0);
}

int	sleeping(t_table *table, t_philo *philo)
{
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
	printf_mutex(philo, "is sleeping");
	waiting(table, philo, table->sleep_t);
	return (0);
}

int	eating_even(t_table *table, t_philo *philo)
{
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
	pthread_mutex_lock(&table->forks[philo->f2]);
	if (check_dead(table) == 1)
	{
		pthread_mutex_unlock(&table->forks[philo->f2]);
		return (1);
	}
	if (get_time() - table->time_start - philo->t_meal >= table->die_t)
	{
		pthread_mutex_lock(&table->mutex_check_dead);	
		table->dead = true;
		printf_mutex(philo, "died");
		pthread_mutex_unlock(&table->mutex_check_dead);	
		pthread_mutex_unlock(&table->forks[philo->f2]);
		return (1);
	}
	printf_mutex(philo, "has taken a fork");
	pthread_mutex_lock(&table->forks[philo->f1]);
	if (check_dead(table) == 1)
	{
		pthread_mutex_unlock(&table->forks[philo->f1]);
		pthread_mutex_unlock(&table->forks[philo->f2]);
		return (1);
	}
	if (get_time() - table->time_start - philo->t_meal >= table->die_t)
	{
		pthread_mutex_lock(&table->mutex_check_dead);	
		table->dead = true;
		printf_mutex(philo, "died");
		pthread_mutex_unlock(&table->mutex_check_dead);	
		pthread_mutex_unlock(&table->forks[philo->f1]);
		pthread_mutex_unlock(&table->forks[philo->f2]);
		return (1);
	}
	printf_mutex(philo, "has taken a fork");
	printf_mutex(philo, "is eating");
	philo->full++;
	philo->t_meal = get_time() - table->time_start;
	if (waiting(table, philo, table->eat_t) == 1)
	{
		pthread_mutex_unlock(&table->forks[philo->f1]);
		pthread_mutex_unlock(&table->forks[philo->f2]);
		return (1);
	};
	pthread_mutex_unlock(&table->forks[philo->f1]);
	pthread_mutex_unlock(&table->forks[philo->f2]);
	return (0);
}

int	eating_odd(t_table *table, t_philo *philo)
{
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
	pthread_mutex_lock(&table->forks[philo->f1]);
	if (check_dead(table) == 1)
	{
		pthread_mutex_unlock(&table->forks[philo->f1]);
		return (1);
	}
	if (get_time() - table->time_start - philo->t_meal >= table->die_t)
	{
		pthread_mutex_lock(&table->mutex_check_dead);	
		table->dead = true;
		printf_mutex(philo, "died");
		pthread_mutex_unlock(&table->mutex_check_dead);	
		pthread_mutex_unlock(&table->forks[philo->f1]);
		return (1);
	}
	printf_mutex(philo, "has taken a fork");
	pthread_mutex_lock(&table->forks[philo->f2]);
	if (check_dead(table) == 1)
	{
		pthread_mutex_unlock(&table->forks[philo->f2]);
		pthread_mutex_unlock(&table->forks[philo->f1]);
		return (1);
	}
	if (get_time() - table->time_start - philo->t_meal >= table->die_t)
	{
		pthread_mutex_lock(&table->mutex_check_dead);	
		table->dead = true;
		printf_mutex(philo, "died");
		pthread_mutex_unlock(&table->mutex_check_dead);	
		pthread_mutex_unlock(&table->forks[philo->f2]);
		pthread_mutex_unlock(&table->forks[philo->f1]);
		return (1);
	}
	printf_mutex(philo, "has taken a fork");
	printf_mutex(philo, "is eating");
	philo->full ++;
	philo->t_meal = get_time() - table->time_start;
	if (waiting(table, philo, table->eat_t) == 1)
	{
		pthread_mutex_unlock(&table->forks[philo->f2]);
		pthread_mutex_unlock(&table->forks[philo->f1]);
		return (1);
	};
	pthread_mutex_unlock(&table->forks[philo->f2]);
	pthread_mutex_unlock(&table->forks[philo->f1]);
	return (0);
}

int	eating(t_table *table, t_philo *philo)
{
	if (table->nb_philo == 1)
	{
		pthread_mutex_lock(&table->forks[philo->f2]);
		printf_mutex(philo, "has taken a fork");
		while (get_time() - table->time_start - philo->t_meal < table->die_t)
			usleep(10);
		pthread_mutex_unlock(&table->forks[philo->f2]);
		return (0);
	}
	if (philo->num % 2 == 0)
	{
		if (eating_even(table, philo) == 1)
			return (1);
	}
	else
	{
		if (eating_odd(table, philo) == 1)
			return (1);
	}
	return (0);
}
