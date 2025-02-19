/*
 * arena.h - Header file for Simple Arena Allocator Library
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

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations for the structures
typedef struct Region Region;
typedef struct Arena Arena;

// Region structure definition
struct Region {
    size_t count;
    size_t capacity;
    Region* next;
    uintptr_t data[]; // Flexible array member
};

// Arena structure definition
struct Arena {
    size_t count;
    Region* head;
    Region* current;
};

// Region-related functions
void reset_region(Region* r);
void* region_alloc(Region* r, size_t size);
void free_region(Region* r);
Region* create_region(size_t capacity);

// Arena-related functions
Arena create_arena(size_t region_capacity);
void free_arena(Arena* ar);
void* arena_alloc(Arena* ar, size_t size);
void reset_arena(Arena* ar);

#ifdef __cplusplus
}
#endif

#endif // ARENA_H

