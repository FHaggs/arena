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
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

typedef struct Region {
    size_t count;
    size_t capacity;
    struct Region* next;
    uintptr_t data[]; // Flexible array member
} Region;

void reset_region(Region* r){
    r->count = 0;
}

void* region_alloc(Region* r, size_t size){
    if(size > r->capacity || size + r->count > r->capacity){
        return NULL;
    }
    void* data = &r->data[r->count];
    r->count = r->count + size;
    return data;
}
Region* create_region(size_t capacity){

    Region* r = (Region*)malloc(capacity + sizeof(Region));
    r->capacity = capacity;
    r->count = 0;
    r->next = NULL;
    
    return r;
}
void free_region(Region* r){
    free(r);
}

typedef struct {
    Region* head;
    Region* tail;
} Arena;

