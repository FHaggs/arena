/*
 * arena.h - Header for Simple Arena Allocator Library
 *
 * Copyright (C) 2025 Pedro Fam Haggstram <pedrofamh@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef ARENA_H
#define ARENA_H

#include <stddef.h> // For size_t

// Region structure to represent the memory arena
typedef struct {
    size_t count;    // Current usage of the arena
    size_t capacity; // Total capacity of the arena
    void* data;      // Pointer to the memory block
} Region;

/**
 * Reset the region to reuse allocated memory.
 * 
 * @param r A pointer to the Region structure.
 */
void reset_region(Region* r);

/**
 * Allocate memory from the region.
 * 
 * @param r A pointer to the Region structure.
 * @param size The number of bytes to allocate.
 * @return A pointer to the allocated memory, or NULL if allocation fails.
 */
void* region_alloc(Region* r, size_t size);

/**
 * Create a new region with the specified capacity.
 * 
 * @param capacity The size of the region in bytes.
 * @return A new Region structure.
 */
Region create_region(size_t capacity);

/**
 * Free the memory associated with the region.
 * 
 * @param r A pointer to the Region structure.
 */
void free_region(Region* r);

#endif // ARENA_H

