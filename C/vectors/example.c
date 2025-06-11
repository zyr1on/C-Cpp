#include "CVector.h"

typedef struct {
    float x;
    float y;
    float z;
}vec3;

int main(void)
{
    vector(vec3) container;
    vector_init(container);

    vec3 a = {3.2,2.1, 33.59};
    vec3 b = {0.0,0.0,0.0};

    vector_push_back(container,a);
    vector_push_back(container,b);
    vector_push_back_args(container,{1,2,3},{1,2,4},{1,2,32});

    vector_foreach(container,p){
        printf("(%.2f, %.2f, %.2f)\n", p->x,p->y, p->z);
    }

    vector_destroy(container);
    
    return 0;
}
