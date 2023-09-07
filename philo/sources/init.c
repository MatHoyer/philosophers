/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:43:39 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/07 11:36:53 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo, t_simu simu_main, t_perm *perm_main, int i)
{
	philo->num = i;
	philo->nb_eat = 0;
	philo->last_eat = 0;
	philo->start_eat = 0;
	pthread_mutex_init(&philo->his_fork.mutex, NULL);
	if (philo->num == 0)
	{
		philo->state = STATE_VIDE;
		philo->mem_state = STATE_VIDE;
		philo->simu = simu_main;
		philo->perm = perm_main;
		return ;
	}
	philo->state = STATE_THINKING;
	philo->mem_state = STATE_THINKING;
	philo->simu = simu_main;
	philo->perm = perm_main;
}

void	init_perm(t_perm *perm)
{
	perm->stop = false;
	pthread_mutex_init(&perm->mutex_access, NULL);
	pthread_mutex_init(&perm->mutex_print, NULL);

}

void	init_simu(t_simu *simu, int ac, char **av)
{
	gettimeofday(&simu->time_start, NULL);
	simu->number_of_philosophers = ft_atoi(av[1]);
	simu->end_if = -1;
	if (simu->number_of_philosophers <= 0)
		exit(printf("Error : Nombre de philosophes invalide (%s).\n", av[1]));
	simu->time_to_die = ft_atoi(av[2]);
	if (simu->time_to_die <= 0)
		exit(printf("Error : Temps de vie invalide (%s).\n", av[2]));
	simu->time_to_eat = ft_atoi(av[3]);
	if (simu->time_to_eat <= 0)
		exit(printf("Error : Temps pour manger invalide (%s).\n", av[3]));
	simu->time_to_sleep = ft_atoi(av[4]);
	if (simu->time_to_sleep <= 0)
		exit(printf("Error : Temps pour dormir invalide (%s).\n", av[4]));
	if (ac == 6)
	{
		simu->end_if = ft_atoi(av[5]);
		if (simu->end_if <= 0)
			exit(printf("Error : Nombre de repas invalide (%s).\n", av[5]));
	}
}

t_philo	*init(t_philo *philo, t_perm *perm_main, int ac, char **av)
{
	t_simu	simu_main;
	int		i;

	i = -1;
	init_perm(perm_main);
	init_simu(&simu_main, ac, av);
	philo = malloc(sizeof(t_philo) * (simu_main.number_of_philosophers + 1));
	if (!philo)
		exit(printf("Error : Mauvaise allocation des philosophes.\n"));
	while (++i <= simu_main.number_of_philosophers)
	{
		init_philo(&philo[i], simu_main, perm_main, i);
		if (i != 1)
			philo[i].neighbour_fork = &philo[i - 1].his_fork;
		if (i == simu_main.number_of_philosophers && i != 1)
			philo[1].neighbour_fork = &philo[i].his_fork;
		else if (i == 1)
			philo[1].neighbour_fork = &philo[0].his_fork;
	}
	return (philo);
}
