# Garbage Collector Library

This library implements a garbage collector mechanism for easy dynamic memory management. It provides the following functions:

- **gc_malloc(size_t size)**: Allocates memory and adds it to the list of allocations.
- **gc_free(void *ptr)**: Frees a specific allocation.
- **gc_collect(void)**: Frees all registered allocations.
- **gc_realloc(void *ptr, size_t size)**: Resizes an already allocated memory block.

## Compilation

Use the provided Makefile to compile the library:

```bash
make
```

This will compile the source file `src/garbage.c` and create an archive `garbage.a`.

## Usage Examples

### Example 1: Manual Allocation and Freeing

```c
#include "garbage.h"
#include <stdio.h>

int main(void) {
    // Allocate memory for an integer
    int *number = gc_malloc(sizeof(int));
    if (number == NULL)
        return (1);
    
    *number = 42;
    printf("Value: %d\n", *number);

    // Free the allocated memory
    gc_free(number);
    return (0);
}
```

### Example 2: Reallocation and Final Collection

```c
#include "garbage.h"
#include <stdio.h>

int main(void) {
    // Allocate an array of 5 integers
    int *array = gc_malloc(5 * sizeof(int));
    if (array == NULL)
        return (1);
    
    for (int i = 0; i < 5; i++)
        array[i] = i * 2;

    // Increase the size of the array
    array = gc_realloc(array, 10 * sizeof(int));
    if (array == NULL)
        return (1);
    
    for (int i = 5; i < 10; i++)
        array[i] = i * 3;

    // Print the contents of the array
    for (int i = 0; i < 10; i++)
        printf("array[%d] = %d\n", i, array[i]);

    // Free all allocations made by the library
    gc_collect();
    return (0);
}
```

## Best Practices

- Use `gc_collect()` to free all allocations when the program terminates to avoid memory leaks.
- Always check the return value of `gc_malloc` and `gc_realloc` to ensure the allocation succeeded.
- When a specific allocation is no longer needed, use `gc_free()` to free the memory selectively.
