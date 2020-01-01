/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machine_ini.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 11:14:56 by fhenrion          #+#    #+#             */
/*   Updated: 2020/01/01 11:47:51 by fhenrion         ###   ########.fr       */
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
	t_trans	t;

	while (next_token(str, '\n'))
	{
		t.c_state = (atoi(*str) - 1);
		if (t.c_state >= nb_states || !next_token(str, ':'))
			return (ERROR);
		t.r_bit = binary_conv(str);
		if (t.r_bit == invalid || t.r_bit == end || !next_token(str, ':'))
			return (ERROR);
		if ((t.w_bit = binary_conv(str)) == invalid || !next_token(str, ':'))
			return (ERROR);
		states[t.c_state].w_bit[t.r_bit] = t.w_bit;
		if ((t.dir = dir_conv(str)) == none || !next_token(str, ':'))
			return (ERROR);
		states[t.c_state].move[t.r_bit] = t.dir;
		t.n_state = (atoi(*str) - 1);
		if (t.n_state >= nb_states)
			return (ERROR);
		states[t.c_state].new_states[t.r_bit] = states + t.n_state;
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
	if (trans_ini(str, machine->states_nb, initial_state) == ERROR)
	{
		free(initial_state);
		return (ERROR);
	}
	machine->current_state = initial_state;
	machine->read_index = 1;
	return (COMPILED);
}