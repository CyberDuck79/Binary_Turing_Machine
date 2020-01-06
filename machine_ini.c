/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machine_ini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 11:14:56 by fhenrion          #+#    #+#             */
/*   Updated: 2020/01/06 22:21:42 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "turing_machine.h"

static int			next_token(char **str, char c)
{
	while (**str && **str != c)
		(*str)++;
	if (!**str)
		return (0);
	(*str)++;
	return (1);
}

static t_direction	direction_conv(char **str)
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

static t_error		transitions_ini(char **str, size_t nb_states, t_state *states)
{
	t_trans	trans;

	while (next_token(str, '\n'))
	{
		trans.c_state = (atoi(*str) - 1);
		if (trans.c_state >= nb_states || !next_token(str, ':'))
			return (ERROR);
		trans.r_bit = binary_conv(str);
		if (trans.r_bit == invalid || trans.r_bit == end || !next_token(str, ':'))
			return (ERROR);
		if ((trans.w_bit = binary_conv(str)) == invalid || !next_token(str, ':'))
			return (ERROR);
		states[trans.c_state].w_bit[trans.r_bit] = trans.w_bit;
		if ((trans.dir = direction_conv(str)) == none || !next_token(str, ':'))
			return (ERROR);
		states[trans.c_state].move[trans.r_bit] = trans.dir;
		trans.n_state = (atoi(*str) - 1);
		if (trans.n_state >= nb_states)
			return (ERROR);
		states[trans.c_state].new_states[trans.r_bit] = states + trans.n_state;
	}
	return (COMPILED);
}

t_error			machine_ini(char **str, t_machine *machine)
{
	t_state			*initial_state;

	if (!machine)
		return(ERROR);
	if ((machine->states_nb = atoi(*str)) < 1)
		return (ERROR);
	if (!(initial_state = calloc(machine->states_nb, sizeof(t_state))))
		return (ERROR);
	if (transitions_ini(str, machine->states_nb, initial_state) == ERROR)
	{
		free(initial_state);
		return (ERROR);
	}
	machine->current_state = initial_state;
	machine->read_index = 1;
	return (COMPILED);
}