/*
 * arena.c - Simple Arena Allocator Library
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
#include "arena.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>


// Region related functions
void reset_region(Region* r){
    r->count = 0;
}

void* region_alloc(Region* r, size_t size){
    size_t alignment = sizeof(uintptr_t);
   
    // Calculate the aligned size to the next multiple of `alignment` 
    size_t aligned_size =  (size + (alignment - 1)) & ~(alignment - 1);

    if(aligned_size + r->count > r->capacity){
        printf("REALOCING\n");
        r->capacity = r->capacity * 2;
        r->data = realloc(r->data, r->capacity);
        if(r->data == NULL){
            fprintf(stderr, "Error reallocing data\n");
        }
    }
    void* data = &r->data[r->count];
    r->count += aligned_size;
    return data;
}

Region create_region(size_t capacity){
    void* data = malloc(capacity * sizeof(uintptr_t));
    Region r = {
        .capacity = capacity,
        .data = data,
        .count = 0
    };
    return r;
}
void free_region(Region* r){
    free(r->data);
}

