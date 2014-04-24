#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

int main()
{
    double x,y;
    double resultat;
    srand(time(NULL));
    while(1)
    {
        x = rand() %5 +1;


        y = sqrt(25-(x*x));


        printf("Y: %f\n", y);
        printf("X: %f\n", x);
        sleep(1);

    }
    return 0;
}
