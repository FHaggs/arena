# Region Allocator Library

This project provides a simple **region-based memory allocator** implemented in `arena.c` with its corresponding header file `arena.h`. Region allocators are efficient for managing memory when the allocation pattern allows freeing all memory at once, making them ideal for specific use cases like parsing or batch processing.

## Features

- **Efficient memory allocation** using a pre-allocated memory block.
- **Simple API** for allocating and resetting memory.
- **Minimal design**, easy to integrate into other projects.

## Files

- `arena.c` and `arena.h`: The core library implementing the region allocator.
- `main.c`: A demo program showcasing how to use the allocator.

## Usage

Include `arena.h` in your project and link against the implementation in `arena.c`. The demo in `main.c` demonstrates basic usage.

### Example

```c
#include "arena.h"

int main() {
    Region my_region = create_region(1024);  // Create a region with 1024 bytes.
    
    int* arr = (int*)region_alloc(&my_region, 10 * sizeof(int));
    if (arr) {
        for (int i = 0; i < 10; i++) {
            arr[i] = i;
        }
        printf("Value at index 7: %d\n", arr[7]);
    } else {
        printf("Allocation failed!\n");
    }

    free_region(&my_region);  // Free the allocated region.
    return 0;
}
```

## License

This project is licensed under the **GNU General Public License v3.0**. See the `LICENSE` file for more details.

