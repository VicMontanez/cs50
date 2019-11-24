//vigenere cs50
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int shift(char c);

int main(int argc, string argv[])
{
    if (argc != 2) 
    {
        printf("Please try again\n");
        return 1;
    }
    else 
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Must be alphabet characters\n");
                return 1;
            }
            int word = argv[1][0];
            int key = shift(word);
//                printf("%i\n", key);
               
        }
    
    }
    
    
    //Get Key and get string length
    string key = argv[1];
    int keyLen = strlen(key);
    
    //Get text
    string s = get_string("plaintext: ");
    
    //create variable for ciphered text
    //char ctext [strlen(s) + 1];

//     int length = strlen(s);
    char ctext[strlen(s) + 1]; // +1 for the null terminator
    ctext[strlen(s)] = '\0';
    
    
    for (int i = 0, j = 0, n = strlen(s); i < n; i++) 
    {
        int letKey = tolower(key[j % keyLen]) - 'a';
        
        if (isupper(s[i]))
        {
            ctext[i] = 'A' + (s[i] - 'A' + letKey) % 26;
            
            j++;
        } 
        else if (islower(s[i]))
        {
//             printf("%c", (s[i] + letKey));
            ctext[i] = 'a' + (s[i] - 'a' + letKey) % 26;
            j++;
        }
        else 
        {
            ctext[i] = s[i];
        }

    }
    
    //Prints the ciphered text
    printf("ciphertext: %s\n", ctext);
    return 0;

} 

//Shift function
int shift(char c) 
{
    if (c >= 'A' && c <= 'Z') 
    {
        return c - 65;    
    } 
    else if (c >= 'a' && c <= 'z') 
    {
        return c - 97;  
    }
         
    return 0;
}
