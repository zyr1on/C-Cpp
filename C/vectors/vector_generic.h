#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Vector magic number for double-init/destroy protection
#define VECTOR_MAGIC_INIT 0xDEADBEEF
#define VECTOR_MAGIC_DESTROYED 0xFEEDFACE

// Generic vector structure with magic number and optimized layout
#define VECTOR_DEFINE(type) \
    struct { \
        type *data; \
        size_t size; \
        size_t capacity; \
        uint32_t magic; \
    }

// Vector type declaration macro
#define vector(type) VECTOR_DEFINE(type)

// Check if vector is properly initialized
#define vector_is_valid(vec) ((vec).magic == VECTOR_MAGIC_INIT)

// Initialize vector with protection against double init
#define vector_init(vec) do { \
    if ((vec).magic == VECTOR_MAGIC_INIT) break; \
    (vec).data = NULL; \
    (vec).size = 0; \
    (vec).capacity = 0; \
    (vec).magic = VECTOR_MAGIC_INIT; \
} while(0)

// Optimized growth strategy - use bit shifts for power of 2 growth
#define VECTOR_GROW_CAPACITY(cap) ((cap) < 4 ? 4 : (cap) << 1)

// Push back element with optimized growth and branch prediction hints
#define vector_push_back(vec, value) do { \
    if (__builtin_expect((vec).magic != VECTOR_MAGIC_INIT, 0)) break; \
    if (__builtin_expect((vec).size >= (vec).capacity, 0)) { \
        size_t new_capacity = VECTOR_GROW_CAPACITY((vec).capacity); \
        typeof((vec).data) new_data = realloc((vec).data, new_capacity * sizeof(*(vec).data)); \
        if (__builtin_expect(new_data != NULL, 1)) { \
            (vec).data = new_data; \
            (vec).capacity = new_capacity; \
        } else break; \
    } \
    (vec).data[(vec).size++] = (value); \
} while(0)

// Fast element access with bounds checking in debug mode
#ifdef DEBUG
#define vector_at(vec, index) \
    (((vec).magic == VECTOR_MAGIC_INIT && (index) < (vec).size) ? \
     (vec).data[index] : \
     (abort(), (vec).data[0]))
#else
#define vector_at(vec, index) ((vec).data[index])
#endif

// Inline functions for frequently used operations
#define vector_size(vec) ((vec).size)
#define vector_capacity(vec) ((vec).capacity)
#define vector_empty(vec) ((vec).size == 0)
#define vector_back(vec) ((vec).data[(vec).size - 1])
#define vector_front(vec) ((vec).data[0])

// Optimized pop back
#define vector_pop_back(vec) do { \
    if (__builtin_expect((vec).magic == VECTOR_MAGIC_INIT && (vec).size > 0, 1)) { \
        (vec).size--; \
    } \
} while(0)

// Fast clear
#define vector_clear(vec) do { \
    if ((vec).magic == VECTOR_MAGIC_INIT) { \
        (vec).size = 0; \
    } \
} while(0)

// Destroy vector with protection against double destroy
#define vector_destroy(vec) do { \
    if ((vec).magic != VECTOR_MAGIC_INIT) break; \
    if ((vec).data) { \
        free((vec).data); \
        (vec).data = NULL; \
    } \
    (vec).size = 0; \
    (vec).capacity = 0; \
    (vec).magic = VECTOR_MAGIC_DESTROYED; \
} while(0)

// Optimized reserve with alignment
#define vector_reserve(vec, new_capacity) do { \
    if ((vec).magic != VECTOR_MAGIC_INIT || (new_capacity) <= (vec).capacity) break; \
    size_t aligned_capacity = (new_capacity); \
    if (aligned_capacity < 4) aligned_capacity = 4; \
    typeof((vec).data) new_data = realloc((vec).data, aligned_capacity * sizeof(*(vec).data)); \
    if (__builtin_expect(new_data != NULL, 1)) { \
        (vec).data = new_data; \
        (vec).capacity = aligned_capacity; \
    } \
} while(0)

// Bulk operations for better performance
#define vector_push_back_bulk(vec, values, count) do { \
    if ((vec).magic != VECTOR_MAGIC_INIT) break; \
    size_t needed_capacity = (vec).size + (count); \
    if (needed_capacity > (vec).capacity) { \
        size_t new_capacity = (vec).capacity; \
        while (new_capacity < needed_capacity) { \
            new_capacity = VECTOR_GROW_CAPACITY(new_capacity); \
        } \
        typeof((vec).data) new_data = realloc((vec).data, new_capacity * sizeof(*(vec).data)); \
        if (__builtin_expect(new_data != NULL, 1)) { \
            (vec).data = new_data; \
            (vec).capacity = new_capacity; \
        } else break; \
    } \
    memcpy((vec).data + (vec).size, (values), (count) * sizeof(*(vec).data)); \
    (vec).size += (count); \
} while(0)

// Optimized resize with bulk initialization
#define vector_resize(vec, new_size, default_value) do { \
    if ((vec).magic != VECTOR_MAGIC_INIT) break; \
    if ((new_size) > (vec).capacity) { \
        vector_reserve(vec, new_size); \
    } \
    if ((new_size) > (vec).size) { \
        for (size_t i = (vec).size; i < (new_size); i++) { \
            (vec).data[i] = (default_value); \
        } \
    } \
    (vec).size = (new_size); \
} while(0)

// Shrink to fit - remove unused capacity
#define vector_shrink_to_fit(vec) do { \
    if ((vec).magic != VECTOR_MAGIC_INIT || (vec).size == (vec).capacity) break; \
    if ((vec).size == 0) { \
        free((vec).data); \
        (vec).data = NULL; \
        (vec).capacity = 0; \
    } else { \
        typeof((vec).data) new_data = realloc((vec).data, (vec).size * sizeof(*(vec).data)); \
        if (new_data) { \
            (vec).data = new_data; \
            (vec).capacity = (vec).size; \
        } \
    } \
} while(0)

// Iterator macros for better performance
#define vector_foreach(vec, item) \
    for (typeof(*(vec).data) *item = (vec).data; \
         item < (vec).data + (vec).size; \
         ++item)

#define vector_foreach_index(vec, index) \
    for (size_t index = 0; index < (vec).size; ++index)


#endif
