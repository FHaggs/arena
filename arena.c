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
void reset_region(Region* r);
void* region_alloc(Region* r, size_t size);
void free_region(Region* r);
Region* create_region(size_t capacity);
// Arena related functions
Arena create_arena(size_t region_capacity);
void free_arena(Arena* ar);
void* arena_alloc(Arena* ar, size_t size);

Arena create_arena(size_t region_capacity){
    Region* genesis_region = create_region(region_capacity);

    Arena ar = {
        .count = 1,
        .head  = genesis_region,
        .current = genesis_region
    };
    return ar;
}
void free_arena(Arena* ar){
    Region* r = ar->head;
    while(r != NULL){
        Region* aux = r->next;
        free_region(r);
        r = aux;
    }
}
void* arena_alloc(Arena* ar, size_t size){
    void* data = region_alloc(ar->current, size);

    if(data == NULL){
        if(ar->current->next == NULL){
            Region* new_region = create_region(ar->current->capacity);
            ar->current = new_region;
            void* new_data = region_alloc(ar->current, size);
            return new_data;
        }else {
            ar->current = ar->current->next;
            void* new_data = region_alloc(ar->current, size);
            return new_data;
        }
    }
    return data;

}
void reset_arena(Arena* ar){
    Region* r = ar->head;
    while(r != NULL){
        Region* aux = r->next;
        reset_region(r);
        r = aux;
    }
    ar->current = ar->head;
}

void reset_region(Region* r){
    r->count = 0;
}

void* region_alloc(Region* r, size_t size){
    size_t alignment = sizeof(uintptr_t);
   
    // Calculate the aligned size to the next multiple of `alignment` 
    size_t aligned_size =  (size + (alignment - 1)) & ~(alignment - 1);

    if(aligned_size > r->capacity || aligned_size + r->count > r->capacity){
        return NULL;
    }
    void* data = &r->data[r->count];
    r->count = r->count + aligned_size;
    return data;
}
Region* create_region(size_t capacity){
    size_t alloc_size = (sizeof(uintptr_t) * capacity) + sizeof(Region);

    Region* r = (Region*)malloc(alloc_size);
    if(r == NULL){
        printf("Error mallocing region\n");
        return NULL;    
    }

    r->capacity = capacity;
    r->count = 0;
    r->next = NULL;
    
    return r;
}
void free_region(Region* r){
    free(r);
}

