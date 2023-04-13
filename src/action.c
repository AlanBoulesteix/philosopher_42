/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:55:26 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/13 13:09:10 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	eating_even_side(t_philo *philo)
{
	
	pthread_mutex_lock(&philo->forks[philo->num - 1]);
	printf_mutex(philo, "has taken a fork\n"); 
	if (philo->num == philo->table->nb_philo)
		pthread_mutex_lock(&philo->forks[0]);
	else
		pthread_mutex_lock(&philo->forks[philo->num]);
	printf_mutex(philo, "has taken a fork\n"); 
	printf_mutex(philo, "is eating\n"); 
	waiting(philo->table->eat_t);
	philo->last_meal = get_time();
	if (philo->num == philo->table->nb_philo)
		pthread_mutex_unlock(&philo->forks[0]);
	else
		pthread_mutex_unlock(&philo->forks[philo->num]);
	pthread_mutex_unlock(&philo->forks[philo->num - 1]);
}

void	eating_odd_side(t_philo *philo)
{

	if (philo->num == philo->table->nb_philo)
		pthread_mutex_lock(&philo->forks[0]);
	else
		pthread_mutex_lock(&philo->forks[philo->num]);
	printf_mutex(philo, "has taken a fork\n"); 
	pthread_mutex_lock(&philo->forks[philo->num - 1]);
	printf_mutex(philo, "has taken a fork\n"); 
	printf_mutex(philo, "is eating\n"); 
	waiting(philo->table->eat_t);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->forks[philo->num - 1]);
	if (philo->num == philo->table->nb_philo)
		pthread_mutex_unlock(&philo->forks[0]);
	else
		pthread_mutex_unlock(&philo->forks[philo->num]);
}

void	sleeping(t_philo *philo)
{
	printf_mutex(philo, "is sleeping\n");
	waiting(philo->table->eat_t);
}
