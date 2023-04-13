/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:18:22 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/12 14:17:13 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_fork(t_table *table)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t)*table->nb_philo);
	if (!forks)
		return (NULL);
	i = -1;
	while (++i < table->nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
				return(destroy_all_fork(forks, i), NULL);
	}
	return (forks);
}

t_philo	*init_philo(t_table *table)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = init_fork(table);
	if (!forks)
		return (NULL);
	philo = malloc(sizeof(*philo) * table->nb_philo);
	if (!philo)
		return (free(forks),NULL);
	i = -1;
	while (++i < table->nb_philo)
	{
		philo[i].forks = forks;
		philo[i].num = i + 1;
		philo[i].dead = false;
		philo[i].last_meal = -1;
		philo[i].table = table;
	}
	return(philo);
}
