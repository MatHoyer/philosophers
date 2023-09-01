/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:43:39 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/01 10:07:00 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo, t_simu *simu_main, int i)
{
	philo->num = i;
	philo->last_eat = 0;
	if (philo->num == 0)
	{
		philo->state = STATE_VIDE;
		philo->mem_state = STATE_VIDE;
		philo->his_fork.is_up = false;
		philo->simu = simu_main;
		return ;
	}
	philo->state = STATE_THINKING;
	philo->mem_state = STATE_THINKING;
	philo->his_fork.is_up = true;
	philo->simu = simu_main;
}

void	init_simu(t_simu *simu, int ac, char **av)
{
	gettimeofday(&simu->time_start, NULL);
	simu->stop = false;
	simu->number_of_philosophers = ft_atoi(av[1]);
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

t_philo	*init(t_philo *philo, t_simu *simu_main, int ac, char **av)
{
	int	i;

	i = -1;
	init_simu(simu_main, ac, av);
	philo = malloc(sizeof(t_philo) * (simu_main->number_of_philosophers + 1));
	if (!philo)
		exit(printf("Error : Mauvaise allocation des philosophes.\n"));
	while (++i <= simu_main->number_of_philosophers)
	{
		init_philo(&philo[i], simu_main, i);
		if (i != 1)
			philo[i].neighbour_fork = &philo[i - 1].his_fork;
		if (i == simu_main->number_of_philosophers && i != 1)
			philo[1].neighbour_fork = &philo[i].his_fork;
		else if (i == 1)
			philo[1].neighbour_fork = &philo[0].his_fork;
	}
	return (philo);
}
