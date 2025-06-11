#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define VECTOR_MAGIC_INIT 0xDEADBEEF
#define VECTOR_MAGIC_DESTROYED 0xFEEDFACE

// Generic vector structure with magic number
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
    if ((vec).magic == VECTOR_MAGIC_INIT) { \
        fprintf(stderr, "[!] Warning: Vector already initialized: 'vector_init' at %s:%d\n", __FILE__, __LINE__); \
        break; \
    } \
    (vec).data = NULL; \
    (vec).size = 0; \
    (vec).capacity = 0; \
    (vec).magic = VECTOR_MAGIC_INIT; \
} while(0)

// Optimized growth strategy - use bit shifts for power of 2 growth
#define VECTOR_GROW_CAPACITY(cap) ((cap) < 4 ? 4 : (cap) << 1)

// Push back element with optimized growth and branch prediction hints
#define vector_push_back(vec, value) do { \
    if (__builtin_expect((vec).magic != VECTOR_MAGIC_INIT, 0)) { \
        fprintf(stderr, "[x] Error: Vector not initialized before: 'vector_push_back' at %s:%d\n", __FILE__, __LINE__); \
        break; \
    } \
    if (__builtin_expect((vec).size >= (vec).capacity, 0)) { \
        size_t new_capacity = VECTOR_GROW_CAPACITY((vec).capacity); \
        typeof((vec).data) new_data = realloc((vec).data, new_capacity * sizeof(*(vec).data)); \
        if (__builtin_expect(new_data != NULL, 1)) { \
            (vec).data = new_data; \
            (vec).capacity = new_capacity; \
        } else { \
            fprintf(stderr, "[x] Error: Memory allocation failed: 'vector_push_back': at %s:%d\n", __FILE__, __LINE__); \
            break; \
        } \
    } \
    (vec).data[(vec).size++] = (value); \
} while(0)



// Fast element access with bounds checking in debug mode
#ifdef DEBUG
#define vector_at(vec, index) \
    (((vec).magic == VECTOR_MAGIC_INIT && (index) < (vec).size) ? \
     (vec).data[index] : \
     (fprintf(stderr, "Error: Invalid vector access at %s:%d\n", __FILE__, __LINE__), abort(), (vec).data[0]))
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
    if (__builtin_expect((vec).magic != VECTOR_MAGIC_INIT, 0)) { \
        fprintf(stderr, "[x] Error: Vector not initialized before 'vector_pop_back' at %s:%d\n", __FILE__, __LINE__); \
        break; \
    } \
    if (__builtin_expect((vec).size == 0, 0)) { \
        fprintf(stderr, "[x] Error: Cannot 'vector_pop_back' from empty vector at %s:%d\n", __FILE__, __LINE__); \
        break; \
    } \
    (vec).size--; \
} while(0)

// Fast clear
#define vector_clear(vec) do { \
    if ((vec).magic != VECTOR_MAGIC_INIT) { \
        fprintf(stderr, "[x] Error: Vector not initialized before 'vector_pop_back' at %s:%d\n", __FILE__, __LINE__); \
        break; \
    } \
    (vec).size = 0; \
} while(0)

// Destroy vector with protection against double destroy and error reporting
#define vector_destroy(vec) do { \
    if ((vec).magic == VECTOR_MAGIC_DESTROYED) { \
        fprintf(stderr, "[x] Error: Vector already destroyed at %s:%d\n", __FILE__, __LINE__); \
        break; \
    } \
    if ((vec).magic != VECTOR_MAGIC_INIT) { \
        fprintf(stderr, "[x] Error: Cannot 'vector_destroy' uninitialized vector_destroy at %s:%d\n", __FILE__, __LINE__); \
        break; \
    } \
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
    if ((vec).magic != VECTOR_MAGIC_INIT) { \
        fprintf(stderr, "[x] Error: Vector not initialized before 'vector_reserve' at %s:%d\n", __FILE__, __LINE__); \
        break; \
    } \
    if ((new_capacity) <= (vec).capacity) break; \
    size_t aligned_capacity = (new_capacity); \
    if (aligned_capacity < 4) aligned_capacity = 4; \
    typeof((vec).data) new_data = realloc((vec).data, aligned_capacity * sizeof(*(vec).data)); \
    if (__builtin_expect(new_data != NULL, 1)) { \
        (vec).data = new_data; \
        (vec).capacity = aligned_capacity; \
    } else { \
        fprintf(stderr, "Error: Memory allocation failed in 'vector_reserve' at %s:%d\n", __FILE__, __LINE__); \
    } \
} while(0)

// // Bulk operations for better performance
// #define vector_push_back_bulk(vec, values, count) do { \
//     if ((vec).magic != VECTOR_MAGIC_INIT) { \
//         fprintf(stderr, "Error: Vector not initialized before push_back_bulk at %s:%d\n", __FILE__, __LINE__); \
//         break; \
//     } \
//     size_t needed_capacity = (vec).size + (count); \
//     if (needed_capacity > (vec).capacity) { \
//         size_t new_capacity = (vec).capacity; \
//         while (new_capacity < needed_capacity) { \
//             new_capacity = VECTOR_GROW_CAPACITY(new_capacity); \
//         } \
//         typeof((vec).data) new_data = realloc((vec).data, new_capacity * sizeof(*(vec).data)); \
//         if (__builtin_expect(new_data != NULL, 1)) { \
//             (vec).data = new_data; \
//             (vec).capacity = new_capacity; \
//         } else { \
//             fprintf(stderr, "Error: Memory allocation failed in push_back_bulk at %s:%d\n", __FILE__, __LINE__); \
//             break; \
//         } \
//     } \
//     memcpy((vec).data + (vec).size, (values), (count) * sizeof(*(vec).data)); \
//     (vec).size += (count); \
// } while(0)

// Optimized resize with bulk initialization
#define vector_resize(vec, new_size, default_value) do { \
    if ((vec).magic != VECTOR_MAGIC_INIT) { \
        fprintf(stderr, "[x] Error: Vector not initialized before 'vector_resize' at %s:%d\n", __FILE__, __LINE__); \
        break; \
    } \
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
    if ((vec).magic != VECTOR_MAGIC_INIT) { \
        fprintf(stderr, "[x] Error: Vector not initialized before 'vector_shrink_to_fit' at %s:%d\n", __FILE__, __LINE__); \
        break; \
    } \
    if ((vec).size == (vec).capacity) break; \
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

#define vector_foreach(vec, item) \
    for (typeof(*(vec).data) *item = (vec).data; \
         item < (vec).data + (vec).size; \
         ++item)

#define vector_find_custom(vec, value, compare_func) ({ \
    int _result = 0; \
    if ((vec).magic == VECTOR_MAGIC_INIT) { \
        for (size_t i = 0; i < (vec).size; ++i) { \
            if (compare_func((vec).data[i], (value))) { \
                _result = i; \
                break; \
            } \
        } \
    } \
    _result; \
})

#define vector_find_index(vec, value) ({ \
    int _result = 0; \
    if ((vec).magic == VECTOR_MAGIC_INIT) { \
        for (size_t i = 0; i < (vec).size; ++i) { \
            if ((vec).data[i] == (value)) { \
                _result = i; \
                break; \
            } \
        } \
    } \
    else \
        fprintf(stderr, "[x] Error: Vector not initialized before 'vector_find_index' at %s:%d\n", __FILE__, __LINE__); \
    _result; \
})

#define vector_find(vec, value) ({ \
    size_t _result = 0; \
    if ((vec).magic != VECTOR_MAGIC_INIT) \
        fprintf(stderr, "[x] Error: Vector not initialized before 'vector_find' at %s:%d\n", __FILE__, __LINE__); \
    else { \
        size_t i = 0; \
        size_t size = (vec).size; \
        for (; i + 3 < size; i += 4) { \
            if ((vec).data[i] == (value)) { _result = i; break; } \
            if ((vec).data[i+1] == (value)) { _result = i+1; break; } \
            if ((vec).data[i+2] == (value)) { _result = i+2; break; } \
            if ((vec).data[i+3] == (value)) { _result = i+3; break; } \
        } \
        if (_result == 0) { \
            for (; i < size; ++i) { \
                if ((vec).data[i] == (value)) { \
                    _result = i; \
                    break; \
                } \
            } \
        } \
    } \
    _result; \
})


static inline int vector_push_back_args_inline(void *vec_ptr, size_t element_size, 
                                               const void *elements, size_t count) {
    struct { void *data; size_t size; size_t capacity; uint32_t magic; } *vec = vec_ptr;
    if (__builtin_expect(vec->magic != VECTOR_MAGIC_INIT, 0))
        return -1; // Error
    size_t new_size = vec->size + count;
    if (__builtin_expect(new_size > vec->capacity, 0)) {
        size_t new_capacity = vec->capacity;
        if (__builtin_expect(new_capacity == 0, 0))
            new_capacity = count > 4 ? count : 4;
        else
            while (new_capacity < new_size)
                new_capacity = new_capacity * 2;
        void *new_data = realloc(vec->data, new_capacity * element_size);
        if (__builtin_expect(new_data != NULL, 1)) {
            vec->data = new_data;
            vec->capacity = new_capacity;
        } 
        else return -1; // Error
    }
    memcpy((char*)vec->data + vec->size * element_size, elements, count * element_size);
    vec->size = new_size;
    return 0;
}


#define vector_push_back_args(vec, ...) do { \
    typeof(*(vec).data) tmp[] = {__VA_ARGS__}; \
    if (vector_push_back_args_inline(&(vec), sizeof(*(vec).data), tmp, \
                                     sizeof(tmp) / sizeof(tmp[0])) != 0) { \
        fprintf(stderr, "[x] Error: vector_push_back_args failed at %s:%d\n", __FILE__, __LINE__); \
    } \
} while(0)

/*!
    
@note: OLD VERSION WITHOUT inline
#define vector_push_back_args(vec, ...) do { \
    if (__builtin_expect((vec).magic != VECTOR_MAGIC_INIT, 0)) { \
        fprintf(stderr, "[x] Error: Vector not initialized before: 'vector_push_back' at %s:%d\n", __FILE__, __LINE__); \
        break; \
    } \
    if (__builtin_expect((vec).size >= (vec).capacity, 0)) { \
        size_t new_capacity = VECTOR_GROW_CAPACITY((vec).capacity); \
        typeof((vec).data) new_data = realloc((vec).data, new_capacity * sizeof(*(vec).data)); \
        if (__builtin_expect(new_data != NULL, 1)) { \
            (vec).data = new_data; \
            (vec).capacity = new_capacity; \
        } else { \
            fprintf(stderr, "[x] Error: Memory allocation failed: 'vector_push_back': at %s:%d\n", __FILE__, __LINE__); \
            break; \
        } \
    } \
    typeof(*(vec).data) tmp[] = {__VA_ARGS__}; \
    size_t count = sizeof(tmp) / sizeof(tmp[0]); \
    for (size_t i = 0; i < count; ++i) { \
        vector_push_back(vec, tmp[i]); \
    } \
} while(0)

*/

#endif
