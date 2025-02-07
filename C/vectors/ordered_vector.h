/*
	AUTHOR: Semih "zyron" Özdemir
 	ordered dynamic array implementation of C
*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define INITIAL_CAP 5
typedef struct {
    int* m_data;
    size_t m_size;
    size_t m_capacity;
    int m_initialized;
} ordered_vector;

int ordered_validate_vector(ordered_vector* v, char* _errStr) {
    if(v == NULL || v->m_data == NULL || v->m_initialized != -1) 
    {
        fprintf(stderr,_errStr);
        return 0;
    }
    return 1;
}

int ordered_vector_init(ordered_vector*v) {
    if(v->m_initialized == -1) {
        fprintf(stderr, "ordered_vector_init: Vector is already m_initialized\n");
        return -1;
    }
    v->m_data = (int*)malloc(sizeof(int)*INITIAL_CAP); // 4byte;
    if(v->m_data == NULL) {
        perror("ordered_vector_init: Memory allocation error\n");
        return -1;
    }
    v->m_size = 0;
    v->m_capacity = INITIAL_CAP;
    v->m_initialized = -1;
    return 0;
}

int ordered_vector_IndexAt(ordered_vector* v, int element, int type) {
    if(!ordered_validate_vector(v,"ordered_vector_IndexAt: Vector is NULL or not m_initialized\n")) return -1;
    int left = 0, right = v->m_size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (v->m_data[mid] == element) return mid;
        else if (v->m_data[mid] > element) right = mid - 1;
        else left = mid + 1;
    }
    if(type == 0) {
        fprintf(stderr, "ordered_vector_IndexAt: Element not found.\n");
        return -1;
    }
    else return left;
}

// int ordered_vector_insert(ordered_vector* v, int element) {
//     if(!ordered_validate_vector(v,"ordered_vector_insert: Vector is NULL or not m_initialized\n")) return -1;
//     if (v->m_size >= v->m_capacity) {
//         v->m_capacity *= 2;
//         int* temp = (int*)malloc(sizeof(int) * v->m_capacity);
//         if (temp == NULL) {
//             perror("ordered_vector_insert: Temporary memory allocation error");
//             return -1;
//         }
//         memcpy(temp,v->m_data,sizeof(int)*v->m_size);
//         free(v->m_data);
//         v->m_data = temp;
//     }
//     int index = ordered_vector_IndexAt(v, element,1);
//     if (index < v->m_size)
//         memmove(v->m_data + index + 1, v->m_data + index, sizeof(int) * (v->m_size - index));
//     v->m_data[index] = element;
//     v->m_size++;
//     return 0;
// }

int ordered_vector_insert(ordered_vector* v, int element) {
    if (!ordered_validate_vector(v, "ordered_vector_insert: Vector is NULL or not m_initialized\n"))
        return -1;
    if (v->m_size >= v->m_capacity) {
        int new_m_capacity = v->m_capacity ? v->m_capacity * 2 : 1;
        int* temp = (int*)realloc(v->m_data, sizeof(int) * new_m_capacity);
        if (temp == NULL) {
            perror("ordered_vector_insert: Memory allocation error");
            return -1;
        }
        v->m_data = temp;
        v->m_capacity = new_m_capacity;
    }
    int index = ordered_vector_IndexAt(v, element, 1);
    if (index < v->m_size) {
        memmove(v->m_data + index + 1, v->m_data + index, sizeof(int) * (v->m_size - index));
    }
    v->m_data[index] = element;
    v->m_size++;
    return 0;
}

int ordered_vector_delete(ordered_vector*v , int element) 
{
    if(!ordered_validate_vector(v,"ordered_vector_delete: Vector is NULL or not m_initialized\n")) return -1;
    int index = ordered_vector_IndexAt(v,element,0);
    if(index == -1) 
    {
        fprintf(stderr, "ordered_vector_delete: Element not found\n");
        return -1;
    }
    if(index == v->m_size -1) 
    {
        v->m_size--;
        return 0;
    }
    memmove(v->m_data + index, v->m_data + index + 1, sizeof(int) * (v->m_size - index - 1));
    v->m_size--;
    return 0;
}

int ordered_vector_pop(ordered_vector* v) {
    if(!ordered_validate_vector(v,"ordered_vector_pop: Vector is NULL or not m_initialized\n")) return -1;
    return v->m_data[v->m_size--];
}

int ordered_vector_multiply(ordered_vector* v) {
    if(!ordered_validate_vector(v,"ordered_vector_multiply: Vector is NULL or not m_initialized\n")) return -1;
    int result = 1;
    for(int i=0;i<v->m_size;i++)
        result *= v->m_data[i];
    return result;
}

int ordered_vector_sum(ordered_vector* v) {
    if(!ordered_validate_vector(v,"ordered_vector_sum: Vector is NULL or not m_initialized\n")) return -1;
    int sum = 0;
    for(int i=0;i<v->m_size;i++)
        sum += v->m_data[i];
    return sum;
}

float ordered_vector_avg(ordered_vector* v) {
    if(!ordered_validate_vector(v,"ordered_vector_avg: Vector is NULL or not m_initialized\n")) return -1;
    int sum = 0;
    for(int i=0;i<v->m_size;i++) {
        sum += v->m_data[i];
    }
    return (float) ((float)sum/(float)v->m_size);
}

int ordered_vector_back(ordered_vector* v) {
    if(!ordered_validate_vector(v,"ordered_vector_last: Vector is NULL or not m_initialized\n")) return -1;
    return v->m_data[v->m_size-1];   
}
int ordered_vector_front(ordered_vector* v) {
    if(!ordered_validate_vector(v,"ordered_vector_front: Vector is NULL or not m_initialized\n")) return -1;
    return v->m_data[0];   
}

int ordered_vector_m_size(ordered_vector *v) {
	if(!ordered_validate_vector(v,"ordered_vector_m_size: Vector is NULL or not m_initialized\n")) return -1;
    return v->m_size;
}

void ordered_vector_print(ordered_vector*v) {
	if(!ordered_validate_vector(v,"ordered_vector_print: Vector is NULL or not m_initialized\n")) return;
    printf("[");
    for(int i=0;i<v->m_size-1;i++) printf("%d,",v->m_data[i]);
    printf("%d]\n",v->m_data[v->m_size-1]);
    return;
}

int ordered_vector_destroy(ordered_vector*v){
    if(!ordered_validate_vector(v,"ordered_vector_destroy: Vector is NULL or not m_initialized\n")) return -1;
    free(v->m_data);
    v->m_data = NULL;
    v->m_size = 0;
    return 0;
}

void ordered_vector_fill(ordered_vector* v, int fill_val) 
{
    if(!ordered_validate_vector(v,"ordered_vector_fill: Vector is NULL or not m_initialized\n")) return;
    memset(v->m_data,fill_val,sizeof(int)*v->m_size);
}
