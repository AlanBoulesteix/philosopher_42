/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:13:11 by aboulest          #+#    #+#             */
/*   Updated: 2023/04/14 16:57:00 by aboulest         ###   ########.fr       */
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
	unsigned int		num;
	int					f1;
	int					f2;
	long long			last_meal;
	pthread_mutex_t		check_meal;
	struct s_table		*table;
}						t_philo;

typedef struct s_table
{
	unsigned int		nb_philo;
	unsigned int		die_t;
	unsigned int		eat_t;
	unsigned int		sleep_t;
	unsigned int		nb_eat_t;
	int					dead;
	bool				all_ate;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		mutex_check_dead;
	pthread_mutex_t		*forks;
	t_philo				*philo;
	long long			time_start;
}						t_table;

int					check_arg(char **argv);
t_table				*init_struct(char **argv);
int					philo(t_table *table);
pthread_mutex_t		*init_fork(t_table *table);
t_philo				*init_philo(t_table *table);

void				destroy_all_fork(pthread_mutex_t *forks, int i);
void				clean_exit(t_table *table);

unsigned int		ft_atoi(const char *str);
long long			get_time(void);
void				waiting(unsigned int wait);

void				printf_mutex(t_philo *philo, char *str);
void				sleeping(t_philo *philo);
int					eating_odd(t_philo *philo, t_table *table);
int					eating_even(t_philo *philo, t_table *table);
bool				check_dead(t_philo *philo);
long long			check_last_meal(t_philo *philo);
void				philo_death(t_table *table, unsigned int i);
#endif
