/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:13:11 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/11 15:14:15 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h> 

typedef struct s_table 
{
	unsigned int	nb_philo;
	unsigned int	die_t;
	unsigned int	eat_t;
	unsigned int	sleep_t;
	unsigned int	nb_eat_t;
	int				dead;
	pthread_mutex_t	system_call;
	pthread_mutex_t	check_dead;
	struct timeval	tv;
}				t_table;

typedef struct s_philo
{
	pthread_t			tid;
	unsigned int		num;
	struct s_philo		*next;
	t_table				*table;
	pthread_mutex_t		*forks;
	long				first_time;
	long				second_time;
}						t_philo;

t_philo		*init_node(int num, t_table *table, pthread_mutex_t *forks);
t_philo		*init_lst(t_table *table);
void		lst_add_back(t_philo **lst, t_philo *nw);
void		lst_free(t_philo *lst);

int			check_arg(char **argv);
t_table 	*init_struct(char **argv);
void		philo(t_table *table);
pthread_mutex_t	*init_fork(t_table *table);

void	printf_mutex(t_philo *philo, char *str);
void	eating_even_side(t_philo *philo);
void	eating_odd_side(t_philo *philo);
void	sleeping(t_philo *philo);
bool	check_dead(t_philo *philo);
#endif
