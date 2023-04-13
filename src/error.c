/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:59:39 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/12 10:10:05 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all_fork(pthread_mutex_t *forks, int max)
{
	int i;
	i = -1;
	if (!forks)
		return ;
	while (++i < max)
		pthread_mutex_destroy(&forks[i]);
	free(forks);
}

void	garbadge_collector(t_table *table)
{
	if (table->philo->forks)
		destroy_all_fork(table->philo->forks, table->nb_philo);
	if (table->philo)
		free(table->philo);
	if (table)
	{
		pthread_mutex_destroy(&table->system_call);
		pthread_mutex_destroy(&table->check_dead);
		free(table);
	}

}