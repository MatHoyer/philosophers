/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 10:58:27 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/26 21:49:42 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_not_enought_arg_error(int ac)
{
	if (ac < 5)
	{
		printf("\033[31mError : ./philo needs at least 5 arguments.\033[0m\n");
		printf("\033[32mLike:\033[0m");
		printf(" ./philo number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep\n");
		printf("\033[32mAnd optional:\033[0m");
		printf(" number_of_times_each_philosopher_must_eat\n");
	}
	else
		printf("\033[31mError : too much arguments (%d).\033[0m\n", ac);
	return (1);
}

void *fonctionDuThread(void *arg) {
    t_philo *philo = (t_philo *) arg;
	int	i = 0;

	while (!philo->simu->stop)
	{
		print_state(philo);
		i++;
		if (i % 100000000 == 0)
		{
			if (philo->state != STATE_SLEEPING)
				philo->state++;
			else
				philo->state = 2;
			if (philo->num == 2 && i == 1000000000)
				philo->state = STATE_DIED;
		}
	}
    return NULL;
}

void	test_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (++i <= philo[0].simu->number_of_philosophers)
	{
		if (pthread_create(&philo[i].thread, NULL, fonctionDuThread, &philo[i]) != 0)
			exit(1);
    }
	i = 0;
	while (++i <= philo[0].simu->number_of_philosophers)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			exit(1);
	}
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_simu	simu_main;

	if (ac < 5 || ac > 6)
		exit(print_not_enought_arg_error(ac));
	philo = NULL;
	philo = init(philo, &simu_main, ac, av);
	test_thread(philo);
	return (0);
}
