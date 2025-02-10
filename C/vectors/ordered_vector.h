/*!
	AUTHOR: Semih "zyr1on" Özdemir
 	ordered dynamic array implementation of C

    @note Changed index calculations to pointer arithmetic.
    @note Changed memory allocation and copying from malloc to realloc.
    
    @warning If performance is critical, vector validation can be removed FROM OTHER FUNCTIOS.
        -> [DELETE IF NECESSARY] int validate_vector(vector* v, char* _errStr)
        -> [DELETE IF NECESSARY] if (v->m_size == 0)
    
    @warning m_capacity and m_size are not private; 
        modifying them directly may break the vector and cause memory issues.

*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define INITIAL_CAP 5
typedef struct {
    int* m_data;              // m_data is a pointer that stores the vector's elements (of type int)
    size_t m_size;           // m_size stores the current number of elements in the vector
    size_t m_capacity;      // m_capacity stores the total capacity of the vector (the allocated memory size)
    int m_initialized;     // m_initialized is a flag that indicates whether the vector has been properly initialized
} ovector;

int ordered_validate_vector(ovector* v, char* _errStr) {
    if(v == NULL || v->m_data == NULL || v->m_initialized != -1) 
    {
        fprintf(stderr,_errStr);
        return 0;
    }
    return 1;
}

int ovector_init(ovector*v) {
    if(v->m_initialized == -1) {
        fprintf(stderr, "ovector_init: Vector is already m_initialized\n");
        return -1;
    }
    v->m_data = (int*)malloc(sizeof(int)*INITIAL_CAP); // 4byte;
    if(v->m_data == NULL) {
        perror("ovector_init: Memory allocation error\n");
        return -1;
    }
    v->m_size = 0;
    v->m_capacity = INITIAL_CAP;
    v->m_initialized = -1;
    return 0;
}

int ovector_IndexAt(ovector* v, int element, int type) {
    if(!ordered_validate_vector(v,"ovector_IndexAt: Vector is NULL or not m_initialized\n")) return -1;
    int left = 0, right = v->m_size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (v->m_data[mid] == element) return mid;
        else if (v->m_data[mid] > element) right = mid - 1;
        else left = mid + 1;
    }
    return (type == 0) ? -1 : left;
}

int ovector_IndexAt_test(ovector* v, int element, int type) {
    if (!ordered_validate_vector(v, "ovector_IndexAt: Vector is NULL or not m_initialized\n"))
        return -1;

    int* left = v->m_data;
    int* right = v->m_data + v->m_size - 1;

    while (left <= right) {
        int* mid = left + (right - left) / 2;

        if (*mid == element) 
            return mid - v->m_data;
        else if (*mid > element) 
            right = mid - 1;
        else 
            left = mid + 1;
    }

    return (type == 0) ? -1 : left - v->m_data;
}


// int ovector_insert(ovector* v, int element) {
//     if(!ordered_validate_vector(v,"ovector_insert: Vector is NULL or not m_initialized\n")) return -1;
//     if (v->m_size >= v->m_capacity) {
//         v->m_capacity *= 2;
//         int* temp = (int*)malloc(sizeof(int) * v->m_capacity);
//         if (temp == NULL) {
//             perror("ovector_insert: Temporary memory allocation error");
//             return -1;
//         }
//         memcpy(temp,v->m_data,sizeof(int)*v->m_size);
//         free(v->m_data);
//         v->m_data = temp;
//     }
//     int index = ovector_IndexAt(v, element,1);
//     if (index < v->m_size)
//         memmove(v->m_data + index + 1, v->m_data + index, sizeof(int) * (v->m_size - index));
//     v->m_data[index] = element;
//     v->m_size++;
//     return 0;
// }

int ovector_insert(ovector* v, int element) {
    if (!ordered_validate_vector(v, "ovector_insert: Vector is NULL or not m_initialized\n"))
        return -1;
    if (v->m_size >= v->m_capacity) {
        int new_m_capacity = v->m_capacity ? v->m_capacity * 2 : 1;
        int* temp = (int*)realloc(v->m_data, sizeof(int) * new_m_capacity);
        if (temp == NULL) {
            perror("ovector_insert: Memory allocation error");
            return -1;
        }
        v->m_data = temp;
        v->m_capacity = new_m_capacity;
    }
    int index = ovector_IndexAt(v, element, 1);
    if (index < v->m_size) {
        memmove(v->m_data + index + 1, v->m_data + index, sizeof(int) * (v->m_size - index));
    }
    v->m_data[index] = element;
    v->m_size++;
    return 0;
}

int ovector_delete(ovector* v, int element) {
    // Validate the vector: check if it's NULL, empty, or not initialized
    if(!ordered_validate_vector(v,"ovector_delete: Vector is NULL or not m_initialized\n")) return -1;

    int index = ovector_IndexAt(v, element, 0);
    if (index == -1) {
        fprintf(stderr, "ovector_delete: Element not found\n");
        return -1;
    }

    if (index == v->m_size - 1) {
        v->m_size--; 
        return 0;
    }
    memmove(v->m_data + index, v->m_data + index + 1, sizeof(int) * (v->m_size - index - 1));
    v->m_size--;
    return 0;
}

int ovector_pop(ovector* v) {
    if(!ordered_validate_vector(v,"ovector_pop: Vector is NULL or not m_initialized\n")) return -1;
    return v->m_data[v->m_size--];
}

int ovector_multiply(ovector* v) {
    if(!ordered_validate_vector(v,"ovector_multiply: Vector is NULL or not m_initialized\n")) return -1;
    int result = 1;
    for(int i=0;i<v->m_size;i++)
        result *= v->m_data[i];
    return result;
}

int ovector_sum(ovector* v) {
    if(!ordered_validate_vector(v,"ovector_sum: Vector is NULL or not m_initialized\n")) return -1;
    int sum = 0;
    for(int i=0;i<v->m_size;i++)
        sum += v->m_data[i];
    return sum;
}

float ovector_avg(ovector* v) {
    if(!ordered_validate_vector(v,"ovector_avg: Vector is NULL or not m_initialized\n")) return -1;
    int sum = 0;
    for(int i=0;i<v->m_size;i++) {
        sum += v->m_data[i];
    }
    return (float) ((float)sum/(float)v->m_size);
}

int ovector_back(ovector* v) {
    if(!ordered_validate_vector(v,"ovector_last: Vector is NULL or not m_initialized\n")) return -1;
    return v->m_data[v->m_size-1];   
}
int ovector_front(ovector* v) {
    if(!ordered_validate_vector(v,"ovector_front: Vector is NULL or not m_initialized\n")) return -1;
    return v->m_data[0];   
}

int ovector_m_size(ovector *v) {
	if(!ordered_validate_vector(v,"ovector_m_size: Vector is NULL or not m_initialized\n")) return -1;
    return v->m_size;
}

void ovector_print(ovector*v) {
	if(!ordered_validate_vector(v,"ovector_print: Vector is NULL or not m_initialized\n")) return;
    printf("[");
    for(int i=0;i<v->m_size-1;i++) printf("%d,",v->m_data[i]);
    printf("%d]\n",v->m_data[v->m_size-1]);
    return;
}

int ovector_destroy(ovector*v){
    if(!ordered_validate_vector(v,"ovector_destroy: Vector is NULL or not m_initialized\n")) return -1;
    free(v->m_data);
    v->m_data = NULL;
    v->m_size = 0;
    return 0;
}

void ovector_fill(ovector* v, int fill_val) 
{
    if(!ordered_validate_vector(v,"ovector_fill: Vector is NULL or not m_initialized\n")) return;
    memset(v->m_data,fill_val,sizeof(int)*v->m_size);
}

ovector ovector_trim(ovector* v, int _startIndex, int _endIndex) {
    ovector temp;
    ovector_init(&temp); 
    temp.m_size = _endIndex - _startIndex;
    memcpy(temp.m_data,v->m_data + _startIndex, sizeof(int) * temp.m_size);
    return temp;    
}
