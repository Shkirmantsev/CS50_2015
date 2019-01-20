#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
{   string s;
    do
    {
        printf("enter your full name:\n");           
        s = GetString();
    }
    while (s == NULL );
    /* printf("your name: %s\n", s);
    printf ("third letter: %c\n", s[3]);*/
    int n=strlen(s);
    
    // first check for the first letter
    if (s[0]!=' ')
    {
        printf("%c", toupper(s[0]));
    };
    
    // second check for the rest letters
    for (int i=1;i<n;i++)
    {
        int k = (i-1);
        if ((s[i] != ' ') && (s[k] == ' ')) 
        {
            printf("%c", toupper(s[i]));
        };
    };
    // print "\n" after initials
    printf("\n");
    return 0 ;
}
