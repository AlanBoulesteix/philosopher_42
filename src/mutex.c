/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:29:28 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/13 11:22:50 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_mutex(t_philo *philo, char *str)
{
	long			time;
	long			time_start;

	pthread_mutex_lock(&philo->table->system_call);
	time_start = philo->table->time_start;
	time = get_time();
	printf("%ld ",time - time_start);
	printf("%d", philo->num);
	printf(" %s", str);
	pthread_mutex_unlock(&philo->table->system_call);
}

bool	check_dead(t_philo *philo)
{
	int	dead;
	pthread_mutex_lock(&philo->table->check_dead);
	dead = philo->table->dead;
	pthread_mutex_unlock(&philo->table->check_dead);
	return (dead == 1);
}
