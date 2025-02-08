/*
	AUTHOR: Semih "zyr1on" Özdemir
 	unordered dynamic array implementation of C

    **NOTE:** Changed index calculations to pointer arithmetic.
    **NOTE:** Changed memory allocation and copying from malloc to realloc.
    
    **WARNING:** If performance is critical, Nvector validation can be removed FROM OTHER FUNCTIOS.
        -> [DELETE IF NECESSARY] int validate_vector(vector* v, char* _errStr)
        -> [DELETE IF NECESSARY] if (v->m_size == 0)
    
    **WARNING:** m_capacity and m_size are not private; 
        modifying them directly may break the vector and cause memory issues.
	> **ERROR:**
 @todo
*/

#include <stdio.h>  // perror, printf
#include <stdlib.h> // malloc,realloc,free
#include <time.h>   // time,srand,rand
#include<string.h>  // memset, memcpy, memmove

#define INITIAL_CAP 5 // Initial capacity of the vector at the start
typedef struct {
    int* m_data;              // m_data is a pointer that stores the vector's elements (of type int)
    size_t m_size;           // m_size stores the current number of elements in the vector
    size_t m_capacity;      // m_capacity stores the total capacity of the vector (the allocated memory size)
    int m_initialized;     // m_initialized is a flag that indicates whether the vector has been properly initialized (if -1 -> already initialized)
} vector;

// used for sorting
int compare(const void* a, const void* b) { 
   return (*(int*)a - *(int*)b);
}

int validate_vector(vector* v, char* _errStr) {
    if(v == NULL || v->m_data == NULL || v->m_initialized != -1) {
        perror(_errStr);
        return 0;
    }
    return 1;
}

// initialize vector at the start ( allocate the memory block so you can use the vector) 
int vector_init(vector*v) {
    if(v->m_initialized == -1) {
        perror("vector_init: Vector is already initialized\n");
        return -1;
    }
    v->m_data = (int*)malloc(sizeof(int)*INITIAL_CAP);
    if(v->m_data == NULL) {
        perror("vector_init: Memory allocation error\n");
        return -1;
    }
    v->m_size = 0;
    v->m_capacity = INITIAL_CAP;
    v->m_initialized = -1;
    return 0;  
}

// To avoid memory leaks you must destroy the vector
int vector_destroy(vector*v) {
    if(!validate_vector(v,"vector_destroy: Vector is NULL | maybe already destroyed or not initialized\n")) return -1;
    free(v->m_data);
    v->m_data = NULL;
    v->m_size = 0;
    v->m_capacity = 0;
    v->m_initialized = 0;
    return 0;
}

int vector_reserve(vector *v, size_t new_capacity) {
    if(!validate_vector(v,"vector_reserve: Vector is NULL or not initialized\n")) return -1;
    if (new_capacity <= v->m_capacity) {
        return 0; 
    }
    int *new_data = (int*)realloc(v->m_data, new_capacity * sizeof(int));
    if (!new_data) {
        printf("vector_reserve: Memory allocation failed.\n");
        return -1; 
    }
    v->m_data = new_data;
    v->m_capacity = new_capacity;
    return 0;
}

// changed malloc to realloc
int vector_push_back(vector* v, int element) {
    if (!validate_vector(v, "vector_push_back: Vector is NULL or not initialized\n")) return -1;
    if (v->m_size == v->m_capacity) {
        if(vector_reserve(v,v->m_capacity * 2) != 0)
            return -1;
    }
    v->m_data[v->m_size++] = element;
    return 0;
}

// changed malloc to realloc
int vector_push_front(vector* v, int element) {
    if (!validate_vector(v, "vector_push_front: Vector is NULL or not initialized\n")) 
        return -1;
    if (v->m_size >= v->m_capacity) {
        if(vector_reserve(v,v->m_capacity * 2) != 0)
            return -1;
    }
    memmove(v->m_data + 1, v->m_data, sizeof(int) * v->m_size);
    v->m_data[0] = element;
    v->m_size++;
    return 0;
}

int* vector_begin(vector *v) {
    return v->m_data;
}
int* vector_rbegin(vector *v) {
    return v->m_data + v->m_size - 1;
}
int* vector_end(vector *v) {
    return v->m_data + v->m_size;
}

// linear search
int vector_IndexAt(vector* v, int element) {
    if (!validate_vector(v, "vector_IndexAt: Vector is NULL | maybe not initialized\n")) 
        return -1;
    if (v->m_size == 0) {
        perror("vector_IndexAt: Vector is empty\n");
        return -1;
    }
    int* p = v->m_data;
    int* end = v->m_data + v->m_size;  
    for (; p < end; ++p)
        if (*p == element) 
            return p - v->m_data;  // Pointer farkı ile indis hesaplanıyor
    return -1;
}

int vector_empty(vector* v) {
    if(v->m_size == 0)
        return 1;
    return 0;
}

// linear search and memory move
int vector_delete(vector* v, int element) {
    if(!validate_vector(v,"vector_delete: Vector is NULL or empty | maybe not initialized\n")) return -1;  
    if (v->m_size == 0) {
        perror("vector_delete: Vector is empty\n");
        return -1;
    }
    int index = vector_IndexAt(v, element);
    if (index == -1) {
        perror("vector_delete: Element not found\n");
        return -1;
    }
    if (index == v->m_size - 1)
        v->m_size--;
    else {
        memmove(v->m_data + index, v->m_data + index + 1, sizeof(int) * (v->m_size - index - 1));
        v->m_size--;
    }
    return 0;
}

// quick sort
int vector_sort(vector* v) {
    if(!validate_vector(v,"vector_sort: Vector is NULL maybe not initialized\n")) return -1; 
    qsort(v->m_data,v->m_size,sizeof(int),compare);
    return 0;
}

int vector_pop_back(vector* v) {
    if(!validate_vector(v,"vector_pop: Vector is NULL or empty | maybe not initialized\n")) return -1; 
    if(v->m_size > 0) return v->m_data[v->m_size--];
}

int vector_multiply(vector* v) {
    if (!validate_vector(v, "vector_multiply: Vector is NULL or empty | maybe not initialized\n")) 
        return -1;
    if (v->m_size == 0) {
        perror("vector_multiply: Vector is empty\n");
        return -1;
    }
    int result = 1;
    int* p = v->m_data;
    int* end = v->m_data + v->m_size;
    for (; p < end; ++p) {
        result *= *p;
    }
    return result;
}

int vector_sum(vector* v) {
    if(!validate_vector(v,"vector_sum: Vector is NULL or empty | maybe not initialized\n")) return -1; 
    if (v->m_size == 0) {
        perror("vector_sum: Vector is empty\n");
        return -1;
    }
    int sum = 0;
    int* p = v->m_data;
    int* end = v->m_data + v->m_size;
    for (; p < end; ++p)
        sum += *p;

    return sum;
}

float vector_avg(vector* v) {
    if(!validate_vector(v,"vector_avg: Vector is NULL or empty | maybe not initialized\n")) return -1; 
    if (v->m_size == 0) {
        perror("vector_avg: Vector is empty\n");
        return -1;
    }
    int sum = 0;
    int* p = v->m_data;
    int* end = v->m_data + v->m_size;
    for (; p < end; ++p)
        sum += *p;

    return (float) ((float)sum/(float)v->m_size);
}

int vector_front(vector* v) {
    if(!validate_vector(v,"vector_front: Vector is NULL or empty | maybe not initialized\n")) return -1; 
    return v->m_data[0];
}
int vector_back(vector* v) {
    if(!validate_vector(v,"vector_back: Vector is NULL or empty | maybe not initialized\n")) return -1; 
    return v->m_data[v->m_size-1];
}

int vector_max(vector* v) {
    if(!validate_vector(v,"vector_max: Vector is empty or NULL | maybe not initialized\n")) return -1; 
    if (v->m_size == 0) {
        perror("vector_max: Vector is empty\n");
        return -1;
    }
    int* p = v->m_data;
    int* end = v->m_data + v->m_size;
    int max = *p; 
    for (++p; p < end; p++)
        if (*p > max)
            max = *p;

    return max;
}

// Pairwise algorithm to find the maximum value in a vector
int vector_max_Pairwise(vector* v) {
    if (!validate_vector(v, "vector_max_Pairwise: Vector is NULL or empty | maybe not initialized\n")) return -1;
    if (v->m_size == 0) {
        perror("vector_max_Pairwise: Vector is empty\n");
        return -1;
    }
    int* p = v->m_data;
    int* end = v->m_data + v->m_size;
    int max = *p;
    for (p += 1; p < end; p += 2) {
        int temp_max = *p;
        if (p + 1 < end)
            temp_max = (*p > *(p + 1)) ? *p : *(p + 1);
        if (temp_max > max)
            max = temp_max;
    }

    return max;
}

int vector_min(vector* v) {
    if(!validate_vector(v,"vector_min: Vector is NULL| maybe not initialized\n")) return -1; 
    if (v->m_size == 0) {
        perror("vector_min: Vector is empty\n");
        return -1;
    }
    int* p = v->m_data;
    int* end = v->m_data + v->m_size;
    int min = *p; 
    for (++p; p < end; p++)
        if (*p < min)
            min = *p;

    return min;
}
int vector_min_Pairwise(vector* v) {
    if (!validate_vector(v, "vector_min_Pairwise: Vector is NULL | maybe not initialized\n")) 
        return -1;
    if (v->m_size == 0) {
        perror("vector_min_Pairwise: Vector is empty\n");
        return -1;
    }
    int* p = v->m_data;
    int* end = v->m_data + v->m_size;
    int min = *p;
    
    for (p += 2; p < end; p += 2) {
        int temp_min = (*p < *(p + 1)) ? *p : *(p + 1);
        if (temp_min < min)
            min = temp_min;
    }
    if (p - 1 < end && *(p - 1) < min)
        min = *(p - 1);

    return min;
}

// returns size of vector(vector.size can be used as well)
int vector_size(vector *v) {
	return v->m_size;
}

// prints vector like python
void vector_print(vector*v) {
    if (!validate_vector(v, "vector_print: Vector is NULL | maybe not initialized\n")) 
        return;
    if (v->m_size == 0) { 
        printf("[]\n"); 
        return; 
    }
    printf("[");
    int* p = v->m_data;
    int* end = v->m_data + v->m_size - 1;
    while (p < end)
        printf("%d,", *p++);
    printf("%d]\n", *p);
}

// shuffles vector elements by random index
void vector_shuffle(vector* v) {
    if(!validate_vector(v,"vector_shuffle: Vector is NULL or empty | maybe not initialized\n")) return; 
    srand((unsigned int)time(0));
    for(int i=0;i<v->m_size;i++) {
        int randNum = rand() % v->m_size;
        int temp = v->m_data[i];
        v->m_data[i] = v->m_data[randNum];
        v->m_data[randNum] = temp;
    }
}

// reverse vector
int vector_reverse(vector* v) {
    if (!validate_vector(v, "vector_reverse: Vector is NULL or empty | maybe not initialized\n")) 
        return -1;

    int* left = v->m_data;
    int* right = v->m_data + v->m_size - 1;
    while (left < right) {
        int temp = *left;
        *left++ = *right;
        *right-- = temp;
    }
    return 0;
}

// Replaces all vector elements with the fill_val parameter.
void vector_fill(vector* v, int fill_val) {
    if(!validate_vector(v,"vector_fill: Vector is NULL or empty | maybe not initialized\n")) return; 
    if (fill_val == 0)
        memset(v->m_data, 0, sizeof(int) * v->m_size);
    else {
        int* end = v->m_data + v->m_size;
        for (int* p = v->m_data; p < end; ++p)
            *p = fill_val;
    }
}

// trims vector between _startIndex and _endIndex and returns vector type. (you should destroy it as well)
vector vector_trim(vector* v, int _startIndex, int _endIndex) {
    vector temp;
    if(!validate_vector(v,"vector_trim: Vector is NULL or empty | maybe not initialized -> empty vector returned\n")) return temp;
    if (_startIndex < 0 || _endIndex > v->m_size || _startIndex >= _endIndex) {
        perror("vector_trim: Invalid start or end index | empty vector returned\n");
        return temp;
    }
    vector_init(&temp); 
    temp.m_size = _endIndex - _startIndex;
    memcpy(temp.m_data,v->m_data + _startIndex, sizeof(int) * temp.m_size);
    return temp;    
}

int vector_shrink_to_fit(vector* v) {
    if (v->m_capacity > v->m_size) {
        int* temp = (int*)realloc(v->m_data, v->m_size * sizeof(int));
        if (temp == NULL) {
            printf("vector_shrink_to_fit: Memory allocation failed.\n");
            return -1;
        }
        v->m_data = temp;
        v->m_capacity = v->m_size;
    }
    return 0;
}

void vector_swap(vector* v1, vector* v2) {
   
    vector temp;
    
    temp.m_data = v1->m_data;
    temp.m_size = v1->m_size;
    temp.m_capacity = v1->m_capacity;

    v1->m_data = v2->m_data;
    v1->m_size = v2->m_size;
    v1->m_capacity = v2->m_capacity;
    
    v2->m_data = temp.m_data;
    v2->m_size = temp.m_size;
    v2->m_capacity = temp.m_capacity;
}
