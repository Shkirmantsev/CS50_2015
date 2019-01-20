#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float owed;
    int owed_cent, i;
    float num_coints = 0;
    printf("Starting process ...step1... ");
    
    do
    {
        printf("How much change is owed?\n");
        owed = GetFloat();
    }
    while (owed <= 0);
    
    //     rounding owed:
    owed_cent = (int) round(owed * 100);
    
    //    this is for adjustment 25, 10, 5, 1
    
    //printf("%.25i\n", owed_cent);
    
    //    25 coins founding:
    if (owed_cent >= 25)    
    {
        i = (owed_cent - owed_cent % 25) / 25;
        num_coints = num_coints + i;
        owed_cent = owed_cent - i * 25;
    }
    
    //10 coins founding:
    if (owed_cent >= 10)
    {
        i = (owed_cent - owed_cent % 10) / 10;
        num_coints = num_coints + i;
        owed_cent = owed_cent - i * 10;
    }
    
    //5 coins founding:
    if (owed_cent >= 5)
    {
        i = (owed_cent - owed_cent % 5) / 5;
        num_coints = num_coints + i;
        owed_cent = owed_cent - i * 5;
    }
    
    //1 coins founding:
    
    if (owed_cent > 0)
    {
        num_coints = num_coints + owed_cent;
    }
    printf("%i\n", (int) num_coints);
return 0 ;
}
