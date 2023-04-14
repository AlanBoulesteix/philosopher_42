/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:18:22 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/14 12:09:03 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_fork(t_table *table)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!forks)
		return (NULL);
	i = -1;
	while (++i < table->nb_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (destroy_all_fork(forks, i), NULL);
	}
	return (forks);
}

t_philo	*init_philo(t_table *table)
{
	t_philo			*philo;
	unsigned int	i;

	philo = malloc(sizeof(*philo) * table->nb_philo);
	if (!philo)
		return (NULL);
	i = -1;
	while (++i < table->nb_philo)
	{
		philo[i].f1 = i;
		if (i == table->nb_philo - 1)
			philo[i].f2 = 0;
		else
			philo[i].f2 = i + 1;
		philo[i].num = i + 1;
		philo[i].dead = false;
		philo[i].last_meal = -1;
		philo[i].table = table;
		pthread_mutex_init(&philo[i].check_meal, NULL);
	}
	return (philo);
}

void	init_struct_split(t_table *table, char **argv)
{
	table->nb_philo = ft_atoi(argv[1]);
	table->die_t = ft_atoi(argv[2]);
	table->eat_t = ft_atoi(argv[3]);
	table->sleep_t = ft_atoi(argv[4]);
	if (argv[5])
		table->nb_eat_t = ft_atoi(argv[5]);
	else
		table->nb_eat_t = -1;
	table->dead = false;
	table->all_ate = false;
}

t_table	*init_struct(char **argv)
{
	t_table	*table;

	table = malloc(sizeof(*table));
	if (!table)
		return (NULL);
	init_struct_split(table, argv);
	table->forks = init_fork(table);
	if (!(table->forks))
		return (free(table), NULL);
	table->philo = init_philo(table);
	if (!(table->philo))
		return (free(table->forks), free(table), NULL);
	pthread_mutex_init(&table->mutex_print, NULL);
	pthread_mutex_init(&table->mutex_check_dead, NULL);
	return (table);
}
