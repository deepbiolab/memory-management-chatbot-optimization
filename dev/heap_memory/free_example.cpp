#include <stdio.h>
#include <stdlib.h>

int main()
{
    void *p = malloc(100); 
    free(p);
    
    void *p2 = p; 
    free(p2);

    return 0;
}
