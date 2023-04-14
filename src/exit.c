/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:59:39 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/14 12:09:43 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all_fork(pthread_mutex_t *forks, int max)
{
	int	i;

	i = -1;
	while (++i < max)
		pthread_mutex_destroy(&forks[i]);
	free(forks);
}

void	clean_exit(t_table *table)
{
	unsigned int	i;

	i = -1;
	while (++i < table->nb_philo)
		pthread_mutex_destroy(&table->philo[i].check_meal);
	if (table->forks)
		destroy_all_fork(table->forks, table->nb_philo);
	if (table->philo)
		free(table->philo);
	if (table)
		free(table);
}
