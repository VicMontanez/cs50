//caesar cs50
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    //Check arguments
    if (argc != 2 || !isdigit(*argv[1])) 
    {
        printf("Try Again\n");
        return 1;
    } 
//     {
        
//        printf("It is a digit/n");
//     }
    //Get Text
    string s = get_string("plaintext: ");
    
    //string to int
    int key = atoi(argv[1]);
    
    //make ciphered text a variable
    char ctext [strlen(s) + 1];
    
    //loop thru every character in plaintext
    for (int i = 0, n = strlen(s) ; i < n; i++) 
    {
        if (s[i] >= 'a' && s[i] <= 'z') //lowercase value
        {
            ctext[i] = (((s[i] - 'a') + key) % 26) + 'a';
//             printf("This is the plaintext: %c\n", s[i]);
//             printf("This is the key: %i\n", key);
//             printf("This is the cipher: %c\n", ctext[i]);
                 
                 
        } 
        else if (s[i] >= 'A' && s[i] <= 'Z')//uppercase value
        {
            ctext[i] = (((s[i] - 'A') + key) % 26) + 'A';
             
//             printf("This is the plaintext: %c\n", s[i]);
//             printf("This is the key: %i\n", key);
//             printf("This is the cipher text: %c\n", ctext[i]);
            
        }
        else 
        {
            ctext[i] = s[i]; //characters that are not letters
            printf("This is the plaintext: %c\n", s[i]);
            printf("This is the key: %i\n", key);
            printf("This is the cipher text: %c\n", ctext[i]);
        }
    }


    //Prints text
    printf("ciphertext: %s\n", ctext);
    return 0;

}
