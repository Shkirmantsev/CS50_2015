# include <cs50.h>
# include <stdio.h>

int main (void)
{
    int Height;
    do
    {
        // enter the number of stages
        printf ("please give me the hight of pyramid (between 0 and 23) : \n") ;
        Height = GetInt () ;
        
        //validation of antered data
        
        if ((Height < 0) ||(Height > 23))
        {
            printf ("must be between 0 and 23,\n") ;
        }
    }
    while ((Height < 0)||( Height > 23));
    
    //creating height
    for ( int spaces = Height; spaces > 0 ;spaces-- )
    {
        //creating empty
        for ( int i = 1; i < spaces ;i++ )
        {
        printf(" ");
        }
        
        //creating stone
        for(int i= 0; i < (Height-spaces+2);i++)
        {
            printf("#");
        }
        printf("\n");
    }
    
    return 0;
}
