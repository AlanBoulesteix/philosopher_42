/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:55:26 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/13 19:18:19 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	sleeping(t_philo *philo)
{
	printf_mutex(philo, "is sleeping\n");
	waiting(philo->table->eat_t);
}
