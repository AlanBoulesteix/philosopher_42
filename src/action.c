/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:55:26 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/11 15:17:45 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating_even_side(t_philo *philo)
{
	struct timeval	tv;
	
	if (check_dead(philo))
		exit(1);
	pthread_mutex_lock(&philo->forks[philo->num - 1]);
	printf_mutex(philo, "has taken a fork\n"); 
	if (check_dead(philo))
		exit(1);
	if (philo->num == philo->table->nb_philo)
		pthread_mutex_lock(&philo->forks[0]);
	else
		pthread_mutex_lock(&philo->forks[philo->num]);
	printf_mutex(philo, "has taken a fork\n"); 
	if (check_dead(philo))
		exit(1);
	printf_mutex(philo, "is eating\n"); 
	if (check_dead(philo))
		exit(1);
	usleep(philo->table->eat_t * 100);
	gettimeofday(&tv, NULL);
	philo->second_time = tv.tv_sec * 1000000 + tv.tv_usec / 1000;
	if (philo->num == philo->table->nb_philo)
		pthread_mutex_unlock(&philo->forks[0]);
	else
		pthread_mutex_unlock(&philo->forks[philo->num]);
	pthread_mutex_unlock(&philo->forks[philo->num - 1]);
}

void	eating_odd_side(t_philo *philo)
{
	struct timeval	tv;


	if (check_dead(philo))
		exit(1);
	if (philo->num == philo->table->nb_philo)
		pthread_mutex_lock(&philo->forks[0]);
	else
		pthread_mutex_lock(&philo->forks[philo->num]);
	printf_mutex(philo, "has taken a fork\n"); 
	if (check_dead(philo))
		exit(1);
	pthread_mutex_lock(&philo->forks[philo->num - 1]);
	printf_mutex(philo, "has taken a fork\n"); 
	if (check_dead(philo))
		exit(1);
	printf_mutex(philo, "is eating\n"); 
	usleep(philo->table->eat_t * 100);
	gettimeofday(&tv, NULL);
	philo->second_time = tv.tv_sec * 1000000 + tv.tv_usec / 1000;
	pthread_mutex_unlock(&philo->forks[philo->num - 1]);
	if (philo->num == philo->table->nb_philo)
		pthread_mutex_unlock(&philo->forks[0]);
	else
		pthread_mutex_unlock(&philo->forks[philo->num]);
}

void	sleeping(t_philo *philo)
{
	printf_mutex(philo, "is sleeping\n");
	usleep(philo->table->sleep_t * 100);
}
