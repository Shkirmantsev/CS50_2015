#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void text_caesar_function(int key, string textName); // prototipe
void letter_function(int key,char letter); // prototipe

int main(int argc, string argv[])
{
    if (argc !=2)
        {
            printf("enter only one key!");
            return 1;
        }
    else 
    {        
        int marker=atoi(argv[1]);
        if (marker==0)
        {
            printf("entered key is letter o negative, must be positive number\n");
            return 1;
        }
        else
        {
            int key=marker;
            string text1=GetString();
            text_caesar_function(key,text1);
            printf("\n");
        }
        
    } 
    
}
// function of printing only letter simbols
void letter_function(int key,char letter)
{
    bool marker3=isupper(letter);
    bool marker4=islower(letter);
    int key2=key%26;
    int numletter=(letter);
    //big letter
    
    if (marker3==true)
    {
        if ((numletter+key2) > 90)
        {
            printf("%c", (numletter+key2-26));
        }
        else
        {
            printf("%c", (numletter+key2));
        }  
    }
    else if(marker4==true)
    {
        if ((numletter+key2) > 122)
        {
            printf("%c",(numletter+key2-26));
        }
        else
        {
            printf("%c", (numletter+key2));
        }  
    }
}
// function of printing all simbols
void text_caesar_function(int key, string textName)
{
    int t=strlen(textName);
    for (int i=0;i<t;i++)
    {
        char letter=textName[i];
        // printing coding letter, checking simbols
        
        bool marker2=isalpha(textName[i]);
        
        if (marker2 == true) // variant letter
        {
            letter_function(key,letter);      
        }
        else // variant simbol
        {
            printf("%c", letter);
        }
    }
}
