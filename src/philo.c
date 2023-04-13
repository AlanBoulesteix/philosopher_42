/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:12:26 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/13 19:53:40 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *data)
{
	t_philo	*philo;
	t_table	*table;
	int count;

	count = 0;
	philo = (t_philo *)data;
	table = philo->table;
	philo->last_meal = get_time();
	while (1)
	{
		if (philo->num %2 == 0)
		{	
			pthread_mutex_lock(&table->forks[philo->f1]);
			printf_mutex(philo, "has taken a fork\n");
			if (table->dead)
			{
				pthread_mutex_unlock(&table->forks[philo->f1]);
				break;
			}
			//ICI CHECKER SI IL DOIT SORTIR
			pthread_mutex_lock(&table->forks[philo->f2]);
			printf_mutex(philo, "has taken a fork\n");
			if (table->dead)
			{
				pthread_mutex_unlock(&table->forks[philo->f1]);
				break;
			}
			//ICI CHECKER SI IL DOIT SORTIR
			printf_mutex(philo, "is eating\n");
			waiting(philo->table->eat_t);
			philo->last_meal = get_time();
			pthread_mutex_unlock(&table->forks[philo->f2]);
			pthread_mutex_unlock(&table->forks[philo->f1]);
		}
		else
		{
			pthread_mutex_lock(&table->forks[philo->f2]);
			printf_mutex(philo, "has taken a fork\n");
			if (table->dead)
			{
				pthread_mutex_unlock(&table->forks[philo->f1]);
				break;
			}
			//ICI CHECKER SI IL DOIT SORTIR
			pthread_mutex_lock(&table->forks[philo->f1]);
			printf_mutex(philo, "has taken a fork\n");
			if (table->dead)
			{
				pthread_mutex_unlock(&table->forks[philo->f1]);
				break;
			}
			//ICI CHECKER SI IL DOIT SORTIR
			printf_mutex(philo, "is eating\n");
			waiting(philo->table->eat_t);
			philo->last_meal = get_time();
			pthread_mutex_unlock(&table->forks[philo->f1]);
			pthread_mutex_unlock(&table->forks[philo->f2]);
		}
		if (count == (int)philo->table->nb_eat_t)
		{
			philo->table->all_ate = true;
			break;
		}
	}
	return (NULL);
}

int		philo(t_table *table)
{
	unsigned int i;

	i = -1;
	table->time_start = get_time();	
	if (table->time_start == -1)
		return(ERROR);
	while (++i < table->nb_philo)
		if (pthread_create(&(table->philo[i].tid), NULL, thread_routine,\
					&table->philo[i]) != 0)
			return (ERROR);
	i = -1;
	while (++i < table->nb_philo)
		if (pthread_join(table->philo[i].tid, NULL) != 0)
			return (ERROR);
	printf("dead ?: %d\n", table->dead);
	return (0);
}
