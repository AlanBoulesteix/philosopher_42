/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:29:28 by aboulest          #+#    #+#             */
/*   Updated: 2023/03/29 12:03:32 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_mutex(t_philo *philo, char *str)
{
	struct timeval	tv;
	long			time;
	long			time_start;
	
	pthread_mutex_lock(&philo->table->system_call);
	gettimeofday(&tv, NULL);
	time_start = philo->table->tv.tv_sec * 1000000 + philo->table->tv.tv_usec;	
	time = tv.tv_sec * 1000000 + tv.tv_usec;
	printf("%ld ",time - time_start);
	printf("%d", philo->num);
	printf(" %s", str);
	pthread_mutex_unlock(&philo->table->system_call);
}
