/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:12:26 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/25 09:55:57 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	action(t_table *table, t_philo *philo, int *flag)
{
	if (eating(table, philo) == 1)
		return (1);
	if (check_dead(table) == 1)
		return (1);
	if (all_ate(table) == 1)
		return (1);
	if (sleeping(table, philo) == 1)
		return (1);
	if (check_dead(table) == 1)
		return (1);
	if (thinking(table, philo, *flag) == 1)
		return (1);
	if (check_dead(table) == 1)
		return (1);
	return (0);
}

void	*thread_routine(void *data)
{
	t_philo	*philo;
	t_table	*table;
	int		flag;

	philo = (t_philo *)data;
	flag = 1;
	table = philo->table;
	philo->t_meal = get_time() - table->time_start;
	if (philo->num % 2 == 0)
	{
		printf_mutex(philo, "is thinking");
		waiting(table, philo, table->eat_t);
	}
	while (check_dead(table) != 1 && all_ate(table) != 1)
	{
		if (action(table, philo, &flag) == 1)
			return (NULL);
	}
	return (NULL);
}

int	philo(t_table *table)
{
	unsigned int	i;

	i = -1;
	table->time_start = get_time();
	while (++i < table->nb_philo)
	{
		if (pthread_create(&table->philo[i].tid, NULL, \
					thread_routine, &table->philo[i]) != 0)
			return (1);
	}
	i = -1;
	while (++i < table->nb_philo)
		if (pthread_join(table->philo[i].tid, NULL) != 0)
			return (1);
	return (0);
}
