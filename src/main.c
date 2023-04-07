/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:12:18 by aboulest          #+#    #+#             */
/*   Updated: 2023/03/23 16:12:14 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*A CREER FONCTION POUR PRINTF + MUTEXT PARCE QUE SINON CA CREER DES DATA RACE*/

int		prog_error(int code_err)
{
	if (code_err == 1)
		write(2, "wrong amount of arguments\n", 26);
	if (code_err == 2)
		write(2, "At least one argument is not numeric\n", 37);
	if (code_err == 3)
		write(2, "init struct failed\n", 20);
	return (code_err);
}	

int	main(int argc, char **argv)
{
	t_table	*table;
/*	
	(void)argc;
	printf("%d\n", printf("%s",argv[1]));
*/	if (argc != 5 && argc != 6)
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
	if (argv[5])
		printf("number of time to eat: %u\n", table->nb_eat_t);
*/	philo(table);
	free(table);
	return (0);
}
