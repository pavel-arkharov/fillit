/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 14:53:08 by tpolonen          #+#    #+#             */
/*   Updated: 2022/01/11 18:38:42 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_block	*match_block(t_block *block, t_block **arr, int index)
{
	int	current;
	int	i;

	current = index;
	while (--current >= 0)
	{
		i = 0;
		while (block->bitmap[i] == arr[current]->bitmap[i] && i < 4)
			i++;
		if (i == 4)
			return (arr[current]);
	}
	return (block);
}

/*
 * Usage:
 * Moves the bitmap contained in *block by the offset vector.
 */
static void	move_block(t_block *block, t_point offset)
{	
	int	i;

	i = 0;
	while (offset.y != 0 && offset.y + i < 4)
	{
		block->bitmap[i] = block->bitmap[offset.y + i];
		block->bitmap[offset.y + i++] = 0;
	}
	i = -1;
	while (offset.x != 0 && ++i < 4)
		block->bitmap[i] = block->bitmap[i] << offset.x;
}

/*
 * Usage:
 * Calculates the empty rows and columns in block's bitmap and move
 * it to the most top-left position possible.
 * 
 * Returns:
 * -1 if the block was empty, 1 if bitmap was moved successfully.
 */
int	realign_block(t_block *block)
{
	t_point	offset;
	int		i;
	int		j;

	offset.y = 0;
	while (block->bitmap[offset.y] == 0 && offset.y < 4)
		offset.y++;
	if (offset.y == 4)
		return (-1);
	offset.x = -1;
	j = 0;
	while (offset.x == -1 && j < 4)
	{
		i = offset.y - 1;
		while (++i < 4 && offset.x == -1)
			if (check_bit(j, block->bitmap[i]) == 1)
				offset.x = j;
		j++;
	}
	move_block(block, offset);
	return (1);
}

/*
 * Usage:
 * Frees any allocated memory inside the t_block struct in the address
 * provided by the **block parameter, then frees the struct itself and
 * sets the address to NULL.
 *
 * Returns:
 * Always -1.
 */
int	delete_block(t_block **block)
{
	free(*block);
	*block = NULL;
	return (-1);
}

/*
 * Usage:
 * Frees all the items contained in the array **arr and the array itself.
 *
 * Returns:
 * Always -1.
 */
int	delete_block_arr(t_block **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
		delete_block(&(arr[i++]));
	free(arr);
	return (-1);
}
