//Cash cs50
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    
    float amount;
    int coins = 0;
    do
    {
        amount = get_float("Your change owed: ");
//          printf("%f\n", amount);
 
    }
    while (amount < 0);
    //rounds out the number
    int cents = round(amount * 100);

     
    float quarter = 25;
    float dime = 10;
    float nickle = 5;
      
    coins += cents / quarter;
    cents %= 25;
     
    coins += cents / dime;
    cents %= 10;
     
    coins += cents / nickle;
    cents %= 5;
     
    coins += cents / 1;
    cents %= 1;
    //prints the # of coins 
    printf("%i\n", coins);
}