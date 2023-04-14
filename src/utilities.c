/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:35:07 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/14 17:53:33 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	long long			time;
	struct timeval		tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	waiting(unsigned int wait)
{
	long long	time;
	long long	target;

	time = get_time();
	target = wait;
	while (get_time() - time < target)
		usleep(10);
}
