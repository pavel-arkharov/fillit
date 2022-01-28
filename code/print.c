/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:45:37 by parkharo          #+#    #+#             */
/*   Updated: 2022/01/07 08:20:06 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static char	**init_map(int size);
static void	free_map(char **map, int size);
static void	put_block(char **map, t_block *block, char letter);

/*
* Usage:
*
* Main printing function, init a map, fill it with the letters,
* corresponding to block positions, print out, free.
*/
void	print_result(int size, t_block **arr, int count)
{
	char	**map;
	int		i;

	i = 0;
	map = init_map(size);
	while (i < count)
	{
		put_block(map, arr[i], (char)('A' + i));
		i++;
	}
	i = 0;
	while (i < size)
		ft_putstr(map[i++]);
	free_map(map, size);
}

/*
 * Usage:
 *
 * Inserts block as letters inside created char** map array.
 */
static void	put_block(char **map, t_block *block, char letter)
{
	int	row;
	int	bit;

	row = 0;
	while (row < block->height)
	{
		bit = 0;
		while (bit < block->width)
		{
			if (check_bit(bit, block->bitmap[row]))
				map[block->y + row][block->x + bit] = letter;
			++bit;
		}
		++row;
	}
}

/*
* Usage:
*
* Allocates dynamic memory for ** map array and each line of it.
* Initializes all lines to dots (empty spots), ends with newlines.
* So 3x3 field would look like: 
* ...\n\0
* ...\n\0
* ...\n\0
*/
static char	**init_map(int size)
{
	char	**map;
	int		i;

	map = (char **)malloc(sizeof(char *) * size);
	i = -1;
	while (++i < size)
	{
		map[i] = ft_strnew(size + 1);
		ft_memset(map[i], '.', size);
		map[i][size] = '\n';
	}
	return (map);
}

/*
* Usage:
*
* Frees previously allocated ** map array and each of its lines. 
*/
static void	free_map(char **map, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(map[i++]);
	free(map);
}
