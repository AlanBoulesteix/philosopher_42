/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:12:26 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/11 15:25:14 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *data)
{
	t_philo			*philo;
	unsigned int	count;
	struct timeval	tv;
	int				dead;

	count = 0;
	philo = (t_philo *)data;
	gettimeofday(&tv, NULL);
	philo->first_time = tv.tv_sec * 1000000 + tv.tv_usec / 1000;
	while (count != philo->table->nb_eat_t && !check_dead(philo))
	{
		if (philo->num % 2 == 0)
			eating_even_side(philo);
		else
			eating_odd_side(philo);
		pthread_mutex_lock(&philo->table->check_dead);
		dead = philo->table->dead;
		pthread_mutex_unlock(&philo->table->check_dead);
		if (dead == 1)
			return (NULL);
		count++;
		sleeping(philo);
		pthread_mutex_lock(&philo->table->check_dead);
		dead = philo->table->dead;
		pthread_mutex_unlock(&philo->table->check_dead);
		if (dead == 1)
			return (NULL);
		printf_mutex(philo, "is thinking\n");
	}
	return (NULL);
}

void	philo(t_table *table)
{
	t_philo				*lst_philo;
	t_philo				*temp;
	long				time;
	int					flag;

	lst_philo = init_lst(table);
	temp = lst_philo;
	while (lst_philo)
	{
		pthread_create(&(lst_philo->tid), NULL, thread_routine, lst_philo);
		lst_philo = lst_philo->next;
	}
	lst_philo = temp;
	flag = 0;
	while (lst_philo->table->dead != 1)
	{
		while (lst_philo)
		{
			time =lst_philo->second_time - lst_philo->first_time; 
			if (time > lst_philo->table->die_t)
			{
				printf_mutex(lst_philo, "died\n");
				pthread_mutex_lock(&lst_philo->table->check_dead);
				lst_philo->table->dead = 1;
				pthread_mutex_unlock(&lst_philo->table->check_dead);
				flag = 1;
				break;
			}
			lst_philo =lst_philo->next;
		}
		if (flag == 1)
			break;
		lst_philo = temp;
	}
	while (lst_philo)
	{
		pthread_join(lst_philo->tid, NULL);
		lst_philo = lst_philo->next;
	}
	free(temp->forks);
	lst_free(temp);
}
