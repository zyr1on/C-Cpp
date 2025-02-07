/*
	AUTHOR: Semih "zyr1on" Özdemir
 	unordered dynamic array implementation of C
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>

#define INITIAL_CAP 5
typedef struct {
    int* m_data;
    size_t m_size;
    size_t m_capacity;
    int m_initialized;
} vector;

int compare(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}
int validate_vector(vector* v, char* _errStr) {
    if(v == NULL || v->m_data == NULL || v->m_initialized != -1) {
        fprintf(stderr,_errStr);
        return 0;
    }
    return 1;
}

int vector_init(vector*v) {
    if(v->m_initialized == -1) {
        fprintf(stderr, "vector_init: Vector is already initialized\n");
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

// int vector_push_back(vector*v, int element) {
//     if(!validate_vector(v,"vector_push_back: Vector is NULL or not initialized\n")) return -1;
//     if(v->m_size == v->m_capacity) {
//         v->m_capacity *=2;
//         int* temp = (int*)malloc(sizeof(int) * v->m_capacity);
//         if(temp == NULL) {
//             perror("vector_push_back: Temporary Memory allocation error");
//             return -1;
//         }
//         memcpy(temp,v->m_data,sizeof(int)*v->m_size);
//         free(v->m_data);
//         v->m_data = temp;
//     }
//     v->m_data[v->m_size++] = element;
//     return 0;
// }

int vector_push_back(vector* v, int element) {
    if (!validate_vector(v, "vector_push_back: Vector is NULL or not initialized\n")) return -1;
    if (v->m_size == v->m_capacity) {
        v->m_capacity *= 2; // Kapasiteyi iki katına çıkarıyoruz
        int* temp = (int*)realloc(v->m_data, sizeof(int) * v->m_capacity);
        if (temp == NULL) {
            perror("vector_push_back: Temporary Memory allocation error");
            return -1;
        }
        v->m_data = temp;
    }
    v->m_data[v->m_size++] = element;
    return 0;
}

int vector_push_front(vector* v,int element) {
    if(!validate_vector(v,"vector_push_front: Vector is NULL or not initialized\n")) return -1;    
    if(v->m_size >= v->m_capacity) {
        v->m_capacity *=2;
        int* temp = (int*)malloc(sizeof(int) * v->m_capacity);
        if(temp == NULL) {
            perror("vector_push_back: Temporary Memory allocation error");
            return -1;
        }
        memmove(temp+1,v->m_data,sizeof(int)*v->m_size);
        free(v->m_data);
        v->m_data = temp;
    }
    else 
        memmove(v->m_data + 1,v->m_data,sizeof(int) * (v->m_size));
    v->m_data[0] = element;
    v->m_size++;
    return 0;
}

int vector_IndexAt(vector* v, int element)  {
    if(!validate_vector(v,"vector_IndexAt: Vector is empty or NULL | maybe not initialized\n")) return -1;  
    for(int i=0;i<v->m_size;i++)
        if(v->m_data[i] == element) return i;
    return -1;
}

int vector_delete(vector* v, int element) {
    if (v->m_data == NULL || v->m_size == 0 || v->m_initialized != 1) {
        fprintf(stderr, "vector_delete: Vector is empty or NULL | maybe not initialized\n");
        return -1;
    }
    if(!validate_vector(v,"vector_delete: Vector is empty or NULL | maybe not initialized\n")) return -1;  
    int index = vector_IndexAt(v,element);
    if(index == -1)
    {
        fprintf(stderr,"vector_delete: Element not found\n");
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

int vector_sort(vector* v) {
    if(!validate_vector(v,"vector_sort: Vector is empty or NULL | maybe not initialized\n")) return -1; 
    qsort(v->m_data,v->m_size,sizeof(int),compare);
    return 0;
}

int vector_pop(vector* v) {
    if(!validate_vector(v,"vector_pop: Vector is empty or NULL | maybe not initialized\n")) return -1; 
    if(v->m_size > 0) return v->m_data[v->m_size--];
}

int vector_multiply(vector* v) {
    if(!validate_vector(v,"vector_multiply: Vector is empty or NULL | maybe not initialized\n")) return -1; 
    int result = 1;
    for(int i=0;i<v->m_size;i++) result *= v->m_data[i];
    return result;
}

int vector_sum(vector* v) {
    if(!validate_vector(v,"vector_sum: Vector is empty or NULL | maybe not initialized\n")) return -1; 
    int sum = 0;
    for(int i=0;i<v->m_size;i++)
        sum += v->m_data[i];
    return sum;
}
float vector_avg(vector* v) {
    if(!validate_vector(v,"vector_avg: Vector is empty or NULL | maybe not initialized\n")) return -1; 
    int sum = 0;
    for(int i=0;i<v->m_size;i++) {
        sum += v->m_data[i];
    }
    return (float) ((float)sum/(float)v->m_size);
}

int vector_front(vector* v) {
    if(!validate_vector(v,"vector_front: Vector is empty or NULL | maybe not initialized\n")) return -1; 
    return v->m_data[0];
}
int vector_back(vector* v) {
    if(!validate_vector(v,"vector_back: Vector is empty or NULL | maybe not initialized\n")) return -1; 
    return v->m_data[v->m_size-1];
}

int vector_max(vector* v) {
    if(!validate_vector(v,"vector_max: Vector is empty or NULL | maybe not initialized\n")) return -1; 
    int max = v->m_data[0];
    for(int i=1;i<v->m_size;i++)
        if(v->m_data[i] > max) 
            max = v->m_data[i];
    return max;
}

int vector_min(vector* v) {
    if(!validate_vector(v,"vector_min: Vector is empty or NULL | maybe not initialized\n")) return -1; 
    int min = v->m_data[0];
    for(int i=1;i<v->m_size;i++)
        if(v->m_data[i] < min)
            min = v->m_data[i];
    return min;
}

int vector_m_size(vector *v) {
	if(!validate_vector(v,"vector_m_size: Vector is empty or NULL | maybe not initialized\n")) return -1; 
    return v->m_size;
}

void vector_print(vector*v) {
    if(!validate_vector(v,"vector_print: Vector is empty or NULL | maybe not initialized\n")) return; 
    printf("[");
    for(int i=0;i<v->m_size-1;i++) printf("%d,",v->m_data[i]);
    printf("%d]\n",v->m_data[v->m_size-1]);
    return;
}

void vector_shuffle(vector* v) {
    if(!validate_vector(v,"vector_shuffle: Vector is empty or NULL | maybe not initialized\n")) return; 
    srand(time(0));
    for(int i=0;i<v->m_size;i++) {
        int randNum = rand() % v->m_size;
        int temp = v->m_data[i];
        v->m_data[i] = v->m_data[randNum];
        v->m_data[randNum] = temp;
    }
}
int vector_reverse(vector* v) {
    if(!validate_vector(v,"vector_reverse: Vector is empty or NULL | maybe not initialized\n")) return -1; 
    for(int i=0;i<v->m_size/2;i++) 
    {
        int temp = v->m_data[i];
        v->m_data[i] = v->m_data[v->m_size -1-i];
        v->m_data[v->m_size-1-i] = temp;
    }
    return 0;
}

int vector_destroy(vector*v) {
    if(!validate_vector(v,"vector_destroy: Vector is NULL | maybe already destroyed or not initialized\n")) return -1;
    free(v->m_data);
    v->m_data = NULL;
    v->m_size = 0;
    v->m_capacity = 0;
    v->m_initialized = 0;
    return 0;
}

void vector_fill(vector* v, int fill_val) {
    if(!validate_vector(v,"vector_fill: Vector is empty or NULL | maybe not initialized\n")) return; 
    memset(v->m_data,fill_val,sizeof(int)*v->m_size);
}

vector vector_trim(vector* v, int _startIndex, int _endIndex) {
    vector temp;
    vector_init(&temp); 
    temp.m_size = _endIndex - _startIndex;
    memcpy(temp.m_data,v->m_data + _startIndex, sizeof(int) * temp.m_size);
    return temp;    
}
