/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turing_machine.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:27:28 by fhenrion          #+#    #+#             */
/*   Updated: 2019/12/16 00:45:44 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TURING_MACHINE_H
# define TURING_MACHINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef unsigned char	t_bytes;

typedef enum		e_error
{
	NO_ACTION,
	STOP,
	COMPILED,
	ERROR
}					t_error;

typedef enum		e_direction
{
	left,
	right,
	none
}					t_direction;

typedef enum		e_bit
{
	false = 0,
	true = 1,
	end = 2,
	invalid = -1
}					t_bit;

typedef struct		s_state
{
	t_bit			w_bit[2];
	t_direction		move[2];
	struct s_state	*new_states[2];
}					t_state;

typedef struct		s_machine
{
	size_t			states_nb;
	t_state			*current_state;
	t_bytes			read_index;
	t_bytes			tape;
}					t_machine;

t_error				machine_ini(char **str, t_machine *machine);

#endif
