/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:13:11 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/13 13:10:47 by aboulest         ###   ########.fr       */
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

# define ERROR 1

typedef struct s_philo
{
	pthread_t			tid;
	pthread_mutex_t		*forks;
	unsigned int		num;
	long				last_meal;
	bool				dead;
	struct s_table		*table;
}						t_philo;

typedef struct s_table 
{
	unsigned int	nb_philo;
	unsigned int	die_t;
	unsigned int	eat_t;
	unsigned int	sleep_t;
	unsigned int	nb_eat_t;
	t_philo 		*philo;
	int				dead;
	bool			all_ate;
	pthread_mutex_t	system_call;
	pthread_mutex_t	check_dead;
	long			time_start;
}				t_table;


int					check_arg(char **argv);
t_table 			*init_struct(char **argv);
int					philo(t_table *table);
pthread_mutex_t		*init_fork(t_table *table);
t_philo				*init_philo(t_table *table);

/*DESTROY ALL MUTEX*/
void	destroy_all_fork(pthread_mutex_t *forks, int i);
void	garbadge_collector(t_table *table);


long	get_time(void);
void	waiting(unsigned int wait);

void	printf_mutex(t_philo *philo, char *str);
void	eating_even_side(t_philo *philo);
void	eating_odd_side(t_philo *philo);
void	sleeping(t_philo *philo);
bool	check_dead(t_philo *philo);
#endif
