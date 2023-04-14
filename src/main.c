/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:12:18 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/14 12:12:42 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	prog_error(int code_err)
{
	if (code_err == 1)
		write(2, "wrong amount of arguments\n", 26);
	if (code_err == 2)
		write(2, "At least one argument is not numeric\n", 37);
	if (code_err == 3)
		write(2, "init struct failed\n", 20);
	if (code_err == 4)
		write(2, "something went wrong in fonction philo\n", 38);
	return (code_err);
}	

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc != 5 && argc != 6)
		return (prog_error(1));
	if (check_arg(argv))
		return (prog_error(2));
	table = init_struct(argv);
	if (!table)
		return (prog_error(3));
	if (philo(table) == ERROR)
		return (clean_exit(table), prog_error(4));
	clean_exit(table);
	return (0);
}