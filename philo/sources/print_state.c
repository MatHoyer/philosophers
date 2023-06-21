/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:29:35 by mhoyer            #+#    #+#             */
/*   Updated: 2023/06/21 12:23:33 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	cmp_state(char *state, char *test_state)
{
	int	i;
	
	i = 0;
	while (state[i] == test_state[i])
	{
		if (state[i] == '\0')
			return (1);
	}
	return (0);
}

int	check_state(t_philo philo)
{
	if (cmp_state(philo.state, philo.mem_state))
	{
		philo.mem_state = philo.state;
		return (1);
	}
	return (0);
}

void	ft_print_state(t_philo philo)
{
	if (cmp_state(philo.state, "died"))
		printf("%d %d died\n", philo.last_eat, philo.num);
	else if (cmp_state(philo.state, "thinking"))
		printf("%d %d is thinking\n", 1, philo.num);
	else if (cmp_state(philo.state, "fork"))
		printf("%d %d has taken a fork\n", 1, philo.num);
	else if (cmp_state(philo.state, "eating"))
		printf("%d %d is eating\n", 1, philo.num);
	else if (cmp_state(philo.state, "sleeping"))
		printf("%d %d is sleeping\n", 1, philo.num);
}

void	print_state(t_simu simu)
{
	int	i;

	i = 0;
	while (++i <= simu.number_of_philosophers)
	{
		if (check_state(simu.philo[i]))
			ft_print_state(simu.philo[i]);
	}
}