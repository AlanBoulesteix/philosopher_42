/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboulest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:10:46 by aboulest          #+#    #+#             */
/*   Updated: 2023/03/30 10:50:52 by aboulest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_lst(t_table *table)
{
	unsigned int		i;
	t_philo				*lst_philo;
	pthread_mutex_t		*forks;

	i = 1;
	forks = init_fork(table);
	if (!forks)
		return (NULL);
	lst_philo = init_node(1 ,table, forks);
	if (!lst_philo)
		return (NULL);
	while (++i <= table->nb_philo)
	{
		lst_add_back(&lst_philo, init_node(i, table, forks));
		//!!!!! A PROTEGER !!!!!!
	}
	return (lst_philo);
}

t_philo	*init_node(int num, t_table *table, pthread_mutex_t *forks)
{
	t_philo	*philo;

	philo = malloc (sizeof(*philo));
	if (!philo)
		return (NULL);
	philo->num = num;
	philo->next = NULL;
	philo->table = table;
	philo->forks = forks;
	philo->first_time = 0;
	philo->second_time = 0;
	return (philo);	
}

t_philo	*ft_lstlast(t_philo *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lst_add_back(t_philo **lst, t_philo *new)
{
	if ((*lst))
		(ft_lstlast(*lst))->next = new;
	else
		*lst = new;
}

void	lst_free(t_philo *lst)
{
	t_philo	*temp;

	while (lst)
	{
		temp = lst->next;
		free(lst);
		lst = temp;
	}
}
