/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:12:26 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/13 13:38:26 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/*OK IL FAUT IMPLEMENTER LE FAIT QUE LE PHILO PEUT MOURIR ET CA CA MARCHE BOF
 * !*/



void	*thread_routine(void *data)
{
	t_philo	*philo;
	int count;

	count = 0;
	philo = (t_philo *)data;
	philo->last_meal = get_time();
	while (count != (int)philo->table->nb_eat_t && !check_dead(philo))
	{
		if (philo->num % 2 == 0)
		{
			usleep(500);
			eating_even_side(philo);
		}
		else
			eating_odd_side(philo);
		usleep(10);
		count++;
		if (count == (int)philo->table->nb_eat_t)
		{
			philo->table->all_ate = true;
			break;
		}
		sleeping(philo);
		usleep(10);
		printf_mutex(philo, "is thinking\n");
		usleep(10);
	}
	return (NULL);
}

int		philo(t_table *table)
{
	unsigned int i;

	i = -1;
	while (++i < table->nb_philo)
		if (pthread_create(&(table->philo[i].tid), NULL, thread_routine,\
					 &table->philo[i]) != 0)
			return (ERROR);
	i = -1;
	while (++i < table->nb_philo)
	{
		if (get_time() - table->philo[i].last_meal > table->die_t)
		{
			printf("philo [%d] est dead parce qu'il a pas graille depuis [%ld]\n", i + 1, get_time() - table->philo[i].last_meal);
			pthread_mutex_lock(&table->check_dead);
			table->dead = 1;
			pthread_mutex_unlock(&table->check_dead);
		}
		if ( i == table->nb_philo - 1 && table->all_ate == 0 && table->dead == 0)
			i = -1;
	}
	i = -1;
	while (++i < table->nb_philo)
		if (pthread_join(table->philo[i].tid, NULL) != 0)
			return (ERROR);
	printf("dead ?: %d\n", table->dead);
	return (0);
}
