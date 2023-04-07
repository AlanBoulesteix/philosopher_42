/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:12:26 by aboulest          #+#    #+#             */
/*   Updated: 2023/03/30 10:47:39 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *data)
{
	t_philo			*philo;
	unsigned int	count;
	struct timeval	tv;
	//long			first_time;

	count = 0;
	philo = (t_philo *)data;
	gettimeofday(&tv, NULL);
	philo->first_time = tv.tv_sec + tv.tv_usec / 1000;
	while (1)
	{
		if (philo->num % 2 == 0)
			eating_even_side(philo);
		else
			eating_odd_side(philo);
		count++;
		if (count == philo->table->nb_eat_t)
			return (NULL);
		gettimeofday(&tv, NULL);
	/*	philo->second_time = tv.tv_sec * 1000000 + tv.tv_usec / 1000;
		if (philo->second_time - philo->first_time > philo->table->die_t)
		{
			printf_mutex(philo, "died\n");
			return (NULL);
		}
		else
			philo->first_time = philo->second_time;
*/	}
	return (NULL);
}

void	philo(t_table *table)
{
	t_philo				*lst_philo;
	t_philo				*temp;

	lst_philo = init_lst(table);
	temp = lst_philo;
	while (lst_philo)
	{
		pthread_create(&(lst_philo->tid), NULL, thread_routine, lst_philo);
		lst_philo = lst_philo->next;
	}
	lst_philo = temp;
	while (lst_philo)
	{
		pthread_join(lst_philo->tid, NULL);
		lst_philo = lst_philo->next;
	}
	free(temp->forks);
	lst_free(temp);
}
