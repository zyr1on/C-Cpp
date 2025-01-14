/*
	AUTHOR: Semih "zyron" Özdemir
 	ordered dynamic array implementation of C
*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define INITIAL_CAP 5
typedef struct {
    int* data;
    size_t size;
    size_t capacity;
    int initialized;
} ordered_vector;

int ordered_validate_vector(ordered_vector* v, char* _errStr) {
    if(v == NULL || v->data == NULL || v->initialized != 1) 
    {
        fprintf(stderr,_errStr);
        return 0;
    }
    return 1;
}

int ordered_vector_init(ordered_vector*v) {
    if(v->initialized == 1) {
        fprintf(stderr, "ordered_vector_init: Vector is already initialized\n");
        return -1;
    }
    v->data = (int*)malloc(sizeof(int)*INITIAL_CAP); // 4byte;
    if(v->data == NULL) {
        perror("ordered_vector_init: Memory allocation error\n");
        return -1;
    }
    v->size = 0;
    v->capacity = INITIAL_CAP;
    v->initialized = 1;
    return 0;
}

int ordered_vector_IndexAt(ordered_vector* v, int element, int type) {
    if(!ordered_validate_vector(v,"ordered_vector_IndexAt: Vector is NULL or not initialized\n")) return -1;
    int left = 0, right = v->size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (v->data[mid] == element) return mid;
        else if (v->data[mid] > element) right = mid - 1;
        else left = mid + 1;
    }
    if(type == 0) {
        fprintf(stderr, "ordered_vector_IndexAt: Element not found.\n");
        return -1;
    }
    else return left;
}

int ordered_vector_insert(ordered_vector* v, int element) {
    if(!ordered_validate_vector(v,"ordered_vector_insert: Vector is NULL or not initialized\n")) return -1;
    if (v->size >= v->capacity) {
        v->capacity *= 2;
        int* temp = (int*)malloc(sizeof(int) * v->capacity);
        if (temp == NULL) {
            perror("ordered_vector_insert: Temporary memory allocation error");
            return -1;
        }
        memcpy(temp,v->data,sizeof(int)*v->size);
        free(v->data);
        v->data = temp;
    }
    int index = ordered_vector_IndexAt(v, element,1);
    if (index < v->size)
        memmove(v->data + index + 1, v->data + index, sizeof(int) * (v->size - index));
    v->data[index] = element;
    v->size++;
    return 0;
}

int ordered_vector_delete(ordered_vector*v , int element) 
{
    if(!ordered_validate_vector(v,"ordered_vector_delete: Vector is NULL or not initialized\n")) return -1;
    int index = ordered_vector_IndexAt(v,element,0);
    if(index == -1) 
    {
        fprintf(stderr, "ordered_vector_delete: Element not found\n");
        return -1;
    }
    if(index == v->size -1) 
    {
        v->size--;
        return 0;
    }
    memmove(v->data + index, v->data + index + 1, sizeof(int) * (v->size - index - 1));
    v->size--;
    return 0;
}

int ordered_vector_pop(ordered_vector* v) {
    if(!ordered_validate_vector(v,"ordered_vector_pop: Vector is NULL or not initialized\n")) return -1;
    return v->data[v->size--];
}

int ordered_vector_multiply(ordered_vector* v) {
    if(!ordered_validate_vector(v,"ordered_vector_multiply: Vector is NULL or not initialized\n")) return -1;
    int result = 1;
    for(int i=0;i<v->size;i++)
        result *= v->data[i];
    return result;
}

int ordered_vector_sum(ordered_vector* v) {
    if(!ordered_validate_vector(v,"ordered_vector_sum: Vector is NULL or not initialized\n")) return -1;
    int sum = 0;
    for(int i=0;i<v->size;i++)
        sum += v->data[i];
    return sum;
}

float ordered_vector_avg(ordered_vector* v) {
    if(!ordered_validate_vector(v,"ordered_vector_avg: Vector is NULL or not initialized\n")) return -1;
    int sum = 0;
    for(int i=0;i<v->size;i++) {
        sum += v->data[i];
    }
    return (float) ((float)sum/(float)v->size);
}

int ordered_vector_back(ordered_vector* v) {
    if(!ordered_validate_vector(v,"ordered_vector_last: Vector is NULL or not initialized\n")) return -1;
    return v->data[v->size-1];   
}
int ordered_vector_front(ordered_vector* v) {
    if(!ordered_validate_vector(v,"ordered_vector_front: Vector is NULL or not initialized\n")) return -1;
    return v->data[0];   
}

int ordered_vector_size(ordered_vector *v) {
	if(!ordered_validate_vector(v,"ordered_vector_size: Vector is NULL or not initialized\n")) return -1;
    return v->size;
}

void ordered_vector_print(ordered_vector*v) {
	if(!ordered_validate_vector(v,"ordered_vector_print: Vector is NULL or not initialized\n")) return;
    printf("[");
    for(int i=0;i<v->size-1;i++) printf("%d,",v->data[i]);
    printf("%d]\n",v->data[v->size-1]);
    return;
}

int ordered_vector_destroy(ordered_vector*v){
    if(!ordered_validate_vector(v,"ordered_vector_destroy: Vector is NULL or not initialized\n")) return -1;
    free(v->data);
    v->data = NULL;
    v->size = 0;
    return 0;
}

void ordered_vector_fill(ordered_vector* v, int fill_val) 
{
    if(!ordered_validate_vector(v,"ordered_vector_fill: Vector is NULL or not initialized\n")) return;
    memset(v->data,fill_val,sizeof(int)*v->size);
}
