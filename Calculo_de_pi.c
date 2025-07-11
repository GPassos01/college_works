#include <stdio.h>

int main()
{
    double pi=3;
    double aux=2, consti=4;

    while (1)
    {
        pi += (consti/(aux * (aux+1) * (aux+2))) ;
        aux = (aux+2);
        consti *= -1;
        printf("%.16lf\n", pi);        
    }
}