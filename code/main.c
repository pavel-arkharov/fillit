/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:44:50 by parkharo          #+#    #+#             */
/*   Updated: 2022/01/11 18:16:05 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
/*
 * Usage:
 * Helper function that prints the provided message and returns the value.
 * Useful for printing error messages, for example.
 *
 * Returns:
 * Value that was provided, unchanged.
 */

static int	die(char *msg, int value)
{
	ft_putendl(msg);
	return (value);
}

/*
 * Usage:
 * Reads the filepath provided by *path, puts the bytes in the *buf
 * and counts the amount of blocks that could be contained in the file.
 *
 * Returns:
 * Amount of blocks if the file contains expected amount of bytes,
 * -1 if there was any kind of error.
 */
static int	read_file(char *path, char *buf)
{
	int		fd;
	int		bytes;
	int		count;

	fd = open(path, O_RDONLY);
	bytes = (int)read(fd, buf, 600);
	close(fd);
	if (bytes <= 0)
		return (-1);
	count = (bytes / 21) + 1;
	if (count < 1 || count > 26)
		return (-1);
	return (count);
}

int	main(int ac, char **av)
{
	t_block	**input;
	t_field	*field;
	int		size;
	int		count;
	char	buf[600];

	if (ac != 2)
		return (die("Usage: fillit input file", -1));
	fill_popcount_table();
	count = read_file(av[1], buf);
	if (count == -1 || validate_input(buf, count, &input) == -1)
		return (die("error", -1));
	size = get_square_size(count);
	field = init_field(size);
	while (!(solve_fillit(field, input, count, 0)))
	{
		free_field(&field);
		field = init_field(++size);
	}
	free_field(&field);
	print_result(size, input, count);
	delete_block_arr(input, count);
	return (1);
}
