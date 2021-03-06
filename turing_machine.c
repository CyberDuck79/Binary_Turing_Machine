/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turing_machine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenrion <fhenrion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 19:27:19 by fhenrion          #+#    #+#             */
/*   Updated: 2020/01/06 22:13:33 by fhenrion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "turing_machine.h"

static void		print_tape(t_bytes tape)
{
	size_t		index = 0;

	while (index < 8)
		printf("%d", !!((tape << index++) & 0x80));
	printf("\n");
}

t_error			execute(t_machine *this)
{
	t_bit		r_bit;
	t_state		*state;

	while (1)
	{
		state = this->current_state;
		r_bit = (this->tape & this->read_index ? 1 : 0);
		if (state->w_bit[r_bit] == 1)
			this->tape |= this->read_index;
		else if (state->w_bit[r_bit] == 0)
			this->tape &= ~this->read_index;
		else if (state->w_bit[r_bit] == end)
			break;
		if (!state->move[r_bit])
			this->read_index <<= 1;
		else
			this->read_index >>= 1;
		if (!this->read_index)
			return (ERROR);
		if (!(this->current_state = state->new_states[r_bit]))
			return (NO_ACTION);
		print_tape(this->tape);
	}
	return (STOP);
}

static char		*read_file(int fd, size_t offset)
{
	char		buf[BUFFER_SIZE];
	char		*new;
	size_t		count;

	if (read(fd, buf, 0) < 0)
		return (NULL);
	if (!(count = read(fd, buf, BUFFER_SIZE)))
		return (new = malloc(offset));
	new = read_file(fd, offset + count);
	strncpy(new + offset, buf, BUFFER_SIZE);
	return (new);
}

static int		check_tape(char *str)
{
	int			conv;

	if(!strlen(str))
		return (0);
	conv = atoi(str);
	if (conv < 0 || conv > 255)
		return (0);
	return (1);
}

int				main(int ac, char **av)
{
	int			fd;
	char		*input;
	t_machine	machine;
	t_state		*ini;

	if (ac != 3)
	{
		write(1, "no file\n", 8);
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (!(input = read_file(fd, 0)) || !check_tape(av[2])
	|| machine_ini(&input, &machine) == ERROR)
	{
		write(1, "input error\n", 12);
		return (0);
	}
	ini = machine.current_state;
	print_tape((machine.tape = (t_bytes)atoi(av[2])));
	if (!(execute(&machine)))
		write(1, "machine error\n", 15);
	free(ini);
	//system("leaks a.out");
	return (0);
}
