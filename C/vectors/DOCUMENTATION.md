<h1>Click Arrow For More Information</h1>

<details>
<summary style="font-size: 18px;">VECTOR.H</summary>
<h1> How to use vector.h</h1>
<h2>Vector container like C++ for C.</h2>

1. First we need to include our header file.

```c
#include "vector.h"         // for unordered vector;
```
2. Create and initialize vector struct.
```c
#include "vector.h"
int main() {
    vector v;
    vector_init(&v);
}
```
3. Introduction to Vector and Vector functions.
```c

#define INITIAL_CAP 5                         -> default initial capacity of vector.
int compare(const void* a, const void* b)     -> the comparison function that qsort uses.
v_initialized                                 -> global variable that checks whether the vector is initialized or not.

void vector_init(vector*v)                                    -> *initializes vector.
int vector_push_back(vector*v, int element)                   -> pushs an element to end of the vector. (0 succes -1 fail)
int vector_push_front(vector* v,int element)                  -> pushs an element to begining of the vector.(0 succes -1 fail)
int vector_delete(vector* v,int element)                      -> deletes an element from vector that passed to function.(0 succes -1 fail)
int vector_sort(vector* v)                                    -> sorts vector.(0 succes -1 fail)
int vector_pop(vector* v)                                     -> pops vector element (assume last element deleted)
int vector_multiply(vector* v)                                -> returns the result of multiplying all vector elements
int vector_sum(vector* v)                                     -> returns the result of summing all vector elements
float vector_avg(vector* v)                                   -> returns total average of vector elements
int vector_get_last_element(vector* v)                        -> returns vector's last element.
int vector_max(vector* v)                                     -> returns the maximum value in the vector
int vector_min(vector* v)                                     -> returns the minimum value in the vector
int vector_size(vector *v)                                    -> returns size of vector.
void vector_print(vector*v)                                   -> prints vector like python lists.
void vector_shuffle(vector* v)                                -> shuffle vector's elements.
void vector_fill(vector* v,int fill_val)                      -> fills all vectors elements to fill_val parameter.
int vector_destroy(vector*v)                                  -> *terminates vector and frees memory block. (0 succes -1 fail)
int vector_IndexAt(vector* v, int element)                    -> linear search to find the index of a given element. (Index elements index number, -1 not Found)
vector vector_trim(vector* v, int _startIndex, int _endIndex) -> Trims the vector from _startIndex to _endIndex (exclusive) and returns a new vector. The returned vector must be destroyed by the caller.

```
4. Basic instructions to start and use vector.
```c
#include "vector.h"
int main() {
    vector v;             //create vector object
    vector_init(&v);      // initialize vector object
    ...
    ...
    ...
    vector_destroy(&v);   // terminate vector object
}
```
5.Example usage:
```c
#include "vector.h"

int main() {
    vector v;
    vector_init(&v);
    
    vector_push_back(&v,5);
    vector_push_back(&v,12);
    vector_push_back(&v,13);
    vector_print(&v);
    
    vector_push_front(&v,-9);
    vector_push_front(&v,12586);
    vector_print(&v);
    
    vector_shuffle(&v);
    vector_print(&v);
    
    vector_sort(&v);
    vector_print(&v);

    vector_delete(&v,12586);
    vector_print(&v);

    printf("Maximum value in vector is:    %d\n" , vector_max(&v));
    printf("Average of vector elements is: %f\n" , vector_avg(&v));

    vector_destroy(&v);
}
OUTPUT:
[5,12,13]
[12586,-9,5,12,13]
[13,5,12,-9,12586]
[-9,5,12,13,12586]
[-9,5,12,13]
Maximum value in vector is:    13      
Average of vector elements is: 5.250000
```
6. Time
```c
vector_push_back(&vec,element)
Time taken to add 1 element: 0.001000 milliseconds
Time taken to add 1000 elements: 0.023000 milliseconds
Time taken to add 100,000 elements: 3.336000 milliseconds
Time taken to add 1 million elements: 21.871000 milliseconds

```
</details>
<details>
<summary style="font-size: 18px;">ORDERED_VECTOR.H</summary>
<h1> How to use ordered_vector.h</h1>
<h2> Ordered Vector container like C++ for C. "Elements are sorted in an orderly manner." </h2>

1. First we need to include our header file.

```c
#include "ordered_vector.h"         // for ordered vector;
```
2. Create and initialize vector struct.
```c
#include"ordered_vector.h"
int main()
{
    ordered_vector o_vec;
    ordered_vector_init(&o_vec);
}
```
3. Introduction to Vector and Vector functions.
```c
#define INITIAL_CAP 5                                          -> default initial capacity of vector.
void ordered_vector_init(vector*v)                             -> *initializes vector.
int  ordered_vector_insert(vector*v, int element)              -> inserts an element into an ordered vector while maintaining the order. (0 succes -1 fail)
int  ordered_vector_delete(vector* v,int element)              -> deletes an element from vector that passed to function.(0 succes -1 fail)
int  ordered_vector_pop(vector* v)                             -> pops vector element (assume last element deleted)
int  ordered_vector_last(vector* v)                            -> returns vector's last element.
int  ordered_vector_size(vector *v)                            -> returns size of vector.
void ordered_vector_print(vector*v)                            -> prints vector like python lists.
void ordered_vector_fill(vector* v,int fill_val)               -> fills all vectors elements to fill_val parameter.
int  ordered_vector_destroy(vector*v)                          -> *terminates vector and frees memory block. (0 succes -1 fail)
```
4. Basic instructions to start and use vector.
```c
#include"ordered_vector.h"
int main()
{
    ordered_vector o_vec;
    ordered_vector_init(&o_vec);
    ...
    ordered_vector_destroy(&o_vec);
}
```
5.Example usage:
```c
#include"ordered_vector.h"
int main()
{
    ordered_vector o_vec;
    ordered_vector_init(&o_vec);
    ordered_vector_insert(&o_vec,25);
    ordered_vector_insert(&o_vec,7);
    ordered_vector_insert(&o_vec,24);
    ordered_vector_print(&o_vec);
    printf("24 index at: %d\n",ordered_vector_IndexAt(&o_vec,24));
    ordered_vector_delete(&o_vec,7);
    ordered_vector_print(&o_vec);
    
    ordered_vector_destroy(&o_vec);
    return 0;
}
OUTPUT:
[7,24,25]
24 index at: 1
[24,25]
```
</details>
