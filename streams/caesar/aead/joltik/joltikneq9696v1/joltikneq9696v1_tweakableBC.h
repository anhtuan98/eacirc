namespace Joltikneq9696v1_raw {

/*
 * Joltik=/=-96-96 Reference C Implementation
 * 
 * Copyright 2014:
 *     Jeremy Jean <JJean@ntu.edu.sg>
 *     Ivica Nikolic <INikolic@ntu.edu.sg>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 * 
 */

#include <stdint.h>

void aesTweakEncrypt(uint32_t tweakey_size, 
	                 const uint8_t pt[8], 
                     const uint8_t key[], 
                     uint8_t ct[8]);

void aesTweakDecrypt(uint32_t tweakey_size, 
	                 const uint8_t ct[8],
                     const uint8_t key[],
                     uint8_t pt[8]);

} // namespace Joltikneq9696v1_raw
