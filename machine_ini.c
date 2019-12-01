/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machine_ini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 11:14:56 by fhenrion          #+#    #+#             */
/*   Updated: 2019/12/01 11:21:19 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "turing_machine.h"

static int			next_token(char **str, char c)
{
	while (**str && **str != c)
		*str += 1;
	if (!**str)
		return (0);
	*str += 1;
	return (1);
}

static t_direction	dir_conv(char **str)
{
	if (**str == '0')
		return (left);
	if (**str == '1')
		return (right);
	return (none);
}

static t_bit		binary_conv(char **str)
{
	if (**str == '0')
		return (false);
	if (**str == '1')
		return (true);
	if (**str == 'e')
		return (end);
	return (invalid);
}

static t_error		trans_ini(char **str, size_t nb_states, t_state *states)
{
	size_t			c_state;
	t_bit			r_bit;
	t_bit			w_bit;
	t_direction		dir;
	size_t			n_state;

	if (!next_token(str, '\n'))
		return (COMPILED);
	c_state = (atoi(*str) - 1);
	if (c_state < 0 || c_state >= nb_states || !next_token(str, ':'))
		return (ERROR);
	r_bit = binary_conv(str);
	if (r_bit == invalid || r_bit == end || !next_token(str, ':'))
		return (ERROR);
	if ((w_bit = binary_conv(str)) == invalid || !next_token(str, ':'))
		return (ERROR);
	states[c_state].w_bit[r_bit] = w_bit;
	if ((dir = dir_conv(str)) == none || !next_token(str, ':'))
		return (ERROR);
	states[c_state].move[r_bit] = dir;
	n_state = (atoi(*str) - 1);
	if (n_state < 0 || n_state >= nb_states)
		return (ERROR);
	states[c_state].new_states[r_bit] = states + n_state;
	return (trans_ini(str, nb_states, states));
}

t_machine			*machine_ini(char **str)
{
	t_machine		*machine = malloc(sizeof(t_machine));
	t_state			*initial_state;

	if (!machine)
		return(NULL);
	if ((machine->states_nb = atoi(*str)) < 1)
	{
		free(machine);
		return (NULL);
	}
	if (!(initial_state = calloc(machine->states_nb, sizeof(t_state))))
	{
		free(machine);
		return (NULL);
	}
	if (trans_ini(str, machine->states_nb, initial_state) == ERROR)
	{
		free(initial_state);
		free(machine);
		return (NULL);
	}
	machine->current_state = initial_state;
	machine->read_index = 128;
	machine->execute = execute;
	return (machine);
}