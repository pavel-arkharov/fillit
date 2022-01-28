/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 13:28:37 by tpolonen          #+#    #+#             */
/*   Updated: 2022/01/11 18:46:36 by parkharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* Usage:
 * 
 * Compares field bitmap with bitmap of a block shifted by x bytes to the right.
 * Return (1) if there are no collisions, and (-1) if there is any.
 * 
 */
static inline int	check_fit(t_field *field, t_block *block, int x, int y)
{
	int	i;

	i = 1;
	while (i < block->height)
	{
		if (field->bitmap[y + i] & block->bitmap[i] >> x)
			return (-1);
		++i;
	}
	return (1);
}

/* Usage:
 * 
 * Updates the field bitmap, toggling input bitmap on or off 
 * on the coordinates corresponding to paramaters x and y.
 */
static inline void	toggle_block(t_field *field, t_block *block, int x, int y)
{
	int	i;

	i = 0;
	while (i < block->height)
	{
		field->bitmap[y + i] ^= block->bitmap[i] >> x;
		++i;
	}
}

/*
 * Usage:
 * Recursively places each of the input in the **input array to field pointed
 * by *f, always starting from the most top-left position available. 
 * count is the amount of input in the array, i is the current
 * index that is being placed. Final location is saved inside block's
 * point-struct.
 *
 * Returns:
 * Count if the input could be filled in this field, 0 if the field is too small.
 */
int	solve_fillit(t_field *f, t_block **input, int count, int i)
{
	if (i == count)
		return (count);
	input[i]->y = input[i]->previous->y - 1;
	while (++input[i]->y <= f->size - input[i]->height)
	{
		if (popcountl(f->bitmap[input[i]->y])
			+ popcountl(input[i]->bitmap[0]) > 16)
			continue ;
		input[i]->x = -1;
		while (++input[i]->x <= f->size - input[i]->width)
		{
			if (!(f->bitmap[input[i]->y] & (input[i]->bitmap[0] >> input[i]->x))
				&& check_fit(f, input[i], input[i]->x, input[i]->y) > 0)
			{
				toggle_block(f, input[i], input[i]->x, input[i]->y);
				if (solve_fillit(f, input, count, i + 1) == count)
					return (count);
				else
					toggle_block(f, input[i], input[i]->x, input[i]->y);
			}
		}
	}
	input[i]->x = 0;
	input[i]->y = 0;
	return (i);
}
