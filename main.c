#define _POSIX_C_SOURCE 199309L

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include "arena.h" // Include your region allocator implementation

#define NUM_ELEMENTS 1000000
#define ITERATIONS 100

// Function to measure time
uint64_t get_time_ns() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

// Benchmark function
void benchmark_allocator(const char* label, int* (*alloc_func)(size_t), void (*free_func)(void*)) {
    uint64_t start_time, end_time;
    int* arrays[NUM_ELEMENTS];

    start_time = get_time_ns();
    for (int iter = 0; iter < ITERATIONS; iter++) {
        // Allocate NUM_ELEMENTS arrays of 10 integers each
        for (size_t i = 0; i < NUM_ELEMENTS; i++) {
            arrays[i] = alloc_func(10 * sizeof(int));
            if (!arrays[i]) {
                printf("Allocation failed!\n");
                exit(1);
            }

            // Write to all elements (simulate workload)
            for (int j = 0; j < 10; j++) {
                arrays[i][j] = i + j;
            }
        }

        // Read from all elements
        for (size_t i = 0; i < NUM_ELEMENTS; i++) {
            volatile int x = arrays[i][5]; // Prevent compiler optimizations
        }

        // Free all arrays
        for (size_t i = 0; i < NUM_ELEMENTS; i++) {
            free_func(arrays[i]);
        }
    }
    end_time = get_time_ns();

    printf("%s: %lu ns\n", label, end_time - start_time);
}

// Region allocator wrapper
Region my_region;

int* region_alloc_wrapper(size_t size) {
    return (int*)region_alloc(&my_region, size);
}

void region_free_wrapper(void* ptr) {
    // Region allocators don't free individual allocations
    reset_region(&my_region);
}

// Malloc wrapper
int* malloc_wrapper(size_t size) {
    return (int*)malloc(size);
}

void free_wrapper(void* ptr) {
    free(ptr);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <benchmark>\n", argv[0]);
        printf("Available benchmarks:\n");
        printf("  malloc       Run malloc/free benchmark\n");
        printf("  region       Run region allocator benchmark\n");
        printf("  arena        Run arena allocator benchmark\n");
        return 1;
    }

    // Initialize region for region allocator
    my_region = create_region(1* NUM_ELEMENTS * sizeof(int));

    printf("Running benchmarks...\n");

    if (strcmp(argv[1], "malloc") == 0) {
        // Test with malloc/free
        benchmark_allocator("malloc/free", malloc_wrapper, free_wrapper);
    } else if (strcmp(argv[1], "region") == 0) {
        // Test with region allocator
        benchmark_allocator("region allocator", region_alloc_wrapper, region_free_wrapper);
    } else {
        printf("Unknown benchmark: %s\n", argv[1]);
        printf("Available benchmarks: malloc, region\n");

        Region r = create_region(5 * sizeof(int));
        for(int i =0;i<10;i++){
            int* place = (int*)region_alloc(&r, sizeof(int));
            *place = i;
        }
        return 1;
    }

    // Cleanup
    free_region(&my_region);

    return 0;
}
