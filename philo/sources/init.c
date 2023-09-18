/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:43:39 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/18 12:01:43 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo, t_simu simu_main, t_perm *perm_main, int i)
{
	philo->num = i;
	philo->nb_eat = 0;
	philo->last_eat = 0;
	philo->start_eat = 0;
	pthread_mutex_init(&philo->his_fork, NULL);
	if (philo->num == 0)
	{
		philo->state = STATE_VIDE;
		philo->mem_state = STATE_VIDE;
		philo->simu = simu_main;
		philo->perm = perm_main;
		return ;
	}
	philo->state = STATE_THINKING;
	philo->mem_state = STATE_VIDE;
	philo->state_bf_die = STATE_VIDE;
	philo->simu = simu_main;
	philo->perm = perm_main;
}

void	init_perm(t_perm *perm)
{
	struct timeval	curent;

	gettimeofday(&curent, NULL);
	perm->time_start = (curent.tv_sec * 1000) + (curent.tv_usec / 1000);
	perm->stop = false;
	perm->done_eating = 0;
	pthread_mutex_init(&perm->mutex_access, NULL);
	pthread_mutex_init(&perm->mutex_print, NULL);
	pthread_mutex_init(&perm->mutex_time, NULL);
}

int	init_simu(t_simu *simu, int ac, char **av)
{
	simu->number_of_philosophers = ft_atoi(av[1]);
	simu->end_if = -1;
	if (simu->number_of_philosophers <= 0)
		return (printf("Error : Bad number of philo (%s).\n", av[1]));
	simu->time_to_eat = ft_atoi(av[3]);
	if (simu->time_to_eat <= 0)
		return (printf("Error : Bad time to eat (%s).\n", av[3]));
	simu->time_to_die = ft_atoi(av[2]);
	if (simu->time_to_die <= 0 || simu->time_to_die < simu->time_to_eat)
		return (printf("Error : Bad time to life (%s).\n", av[2]));
	simu->time_to_sleep = ft_atoi(av[4]);
	if (simu->time_to_sleep <= 0)
		return (printf("Error : Bad time to sleep (%s).\n", av[4]));
	if (ac == 6)
	{
		simu->end_if = ft_atoi(av[5]);
		if (simu->end_if <= 0)
			return (printf("Error : Bad number of lunch (%s).\n", av[5]));
	}
	return (0);
}

t_philo	*init(t_philo *philo, t_perm *perm_main, int ac, char **av)
{
	t_simu	simu_main;
	int		i;

	i = -1;
	init_perm(perm_main);
	if (init_simu(&simu_main, ac, av) != 0)
		return (NULL);
	if (simu_main.number_of_philosophers == 1)
	{
		printf("%ld 1 is thinking\n", get_pgrm_time(perm_main->time_start));
		printf("%ld 1 has taken a fork\n", get_pgrm_time(perm_main->time_start));
		printf("%ld 1 has taken a fork\n", get_pgrm_time(perm_main->time_start));
		printf("%ld 1 is eating\n", get_pgrm_time(perm_main->time_start));
		usleep(simu_main.time_to_die * 1000);
		printf("%ld 1 died\n", get_pgrm_time(perm_main->time_start));
		return(NULL);
	}
	philo = malloc(sizeof(t_philo) * (simu_main.number_of_philosophers + 1));
	if (!philo)
		return (printf("Error : Bad alloc.\n"), NULL);
	while (++i <= simu_main.number_of_philosophers)
		init_philo(&philo[i], simu_main, perm_main, i);
	i = 0;
	while (++i <= simu_main.number_of_philosophers)
	{
		if (i == simu_main.number_of_philosophers)
			philo[i].neighbour_fork = &philo[1].his_fork;
		else
			philo[i].neighbour_fork = &philo[i + 1].his_fork;
	}
	return (philo);
}
