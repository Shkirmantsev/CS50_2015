# include <cs50.h>
# include <stdio.h>

int main (void)
{
    int Height ;
    bool valid ;
    do
    {
        // enter the number of stages
        printf ("please give me the integer hight of pyramid (between [1] and [23]) : \n") ;
        n = GetInt () ;
        
        //validation of antered data
        if ((Height < 1) ||( Height > 23))
        {
            printf ("entered number must bebetween [1] and [23], please enter valid number,\n") ;
            valid = true ;
        }
        else if (( Height >= 1) && ( Height <= 23))
        {
            valid = false ;
        }
        else
        {
            printf ("entered number must be integer\n") ;
            valid = true ;
        } 
    }
    while ( valid );
    
    //creating height
    for ( int spaces = Height; spaces > 0 ;spaces-- )
    {
        //creating empty
        for ( int i = 1; i < spaces ;i++ )
        {
        printf(" ");
        }
        
        //creating stone
        for(int i= 0; i < (n-spaces+2);i++)
        {
            printf("#");
        }
        printf("\n");
    }
    
    return 0;
}
