/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:12:18 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/12 10:32:43 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		prog_error(int code_err)
{
	if (code_err == 1)
		write(2, "wrong amount of arguments\n", 26);
	if (code_err == 2)
		write(2, "At least one argument is not numeric\n", 37);
	if (code_err == 3)
		write(2, "init struct table failed\n", 25);
	if (code_err == 4)
		write(2, "init struct philo failed\n", 25);
	return (code_err);
}	

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc != 5 && argc != 6)
		return(prog_error(1));
	if (check_arg(argv))
		return(prog_error(2));
	table = init_struct(argv);
	if (!table)
		return(prog_error(3));
/*	printf("nb philo: %u\n", table->nb_philo);
	printf("time_to_die: %u\n", table->die_t);
	printf("time_to_eat: %u\n", table->eat_t);
	printf("time_to_sleep: %u\n", table->sleep_t);
	printf("number of time to eat: %i\n", table->nb_eat_t);*/
	if(philo(table) == ERROR)
		return(garbadge_collector(table), prog_error(4));
	garbadge_collector(table);
	return (0);
}
