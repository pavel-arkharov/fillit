/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpolonen <tpolonen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 14:55:13 by tpolonen          #+#    #+#             */
/*   Updated: 2022/01/07 19:32:10 by tpolonen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static unsigned short	g_popcount_table[65536];

/*
 * Usage:
 * Sets a specific bit to 1. Bits are counted starting from the leftmost
 * position (most significant bit) and zero-indexed, so setting the
 * bit 0 from number 0b000000 would turn it into 0b1000000.
 *
 * Returns:
 * Number with the specific bit set to 1.
 */
int	set_bit(int bit, unsigned int number)
{
	return (number | (1 << ((sizeof(unsigned int) * 8) - 1 - bit)));
}

/*
 * Usage:
 * Clears a specific bit to 0. Bits are counted starting from the leftmost
 * position: clearing the bit 1 from number 0b1111 would turn it into 0b1011.
 *
 * Returns:
 * Number with the specific bit cleared to 0.
 */
int	clear_bit(int bit, unsigned int number)
{
	return (number & ~(1 << ((sizeof(unsigned int) * 8) - 1 - bit)));
}

/*
 * Usage:
 * Checks the specific bit in the number. Bits are counted from the leftmost
 * position: bit 3 in number 0b11101 is 0.
 *
 * Returns:
 * 1 if bit is set, 0 if it's cleared.
 */
int	check_bit(int bit, unsigned int number)
{
	return ((number & (1 << ((sizeof(unsigned int) * 8) - 1 - bit))) != 0);
}

/* 
 * Usage:
 * Returns amount of set bits in the left side of int -
 * this is the only bits we care about since all our blocks are aligned
 * to the left side of numbers and max size of field is 11.
 */
unsigned short	popcountl(unsigned int number)
{
	return (g_popcount_table[number >> 16]);
}

void	fill_popcount_table(void)
{
	unsigned int	i;
	unsigned int	number;
	unsigned short	count;

	i = 0;
	while (i < 65536)
	{
		count = 0;
		number = i;
		while (number != 0)
		{
			count++;
			number &= number - 1;
		}
		g_popcount_table[i] = count;
		i++;
	}
}
