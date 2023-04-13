/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:35:07 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/13 13:11:05 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_num(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
	}
	return (0);
}

int	check_arg(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (is_num(argv[i]))
			return (1);
	}
	return (0);
}

unsigned int	ft_atoi(const char *str)
{
	unsigned int	i;
	unsigned int	res;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res);
}

t_table	*init_struct(char **argv)
{
	t_table	*table;

	table = malloc(sizeof(*table));
	if (!table)
		return (NULL);
	table->time_start = get_time();	
	if (table->time_start == -1)
		return (free(table), NULL);
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
	table->philo = init_philo(table);
	if (!(table->philo))
		return (free(table), NULL);
	pthread_mutex_init(&table->system_call, NULL);
	pthread_mutex_init(&table->check_dead, NULL);
	return (table);
}
