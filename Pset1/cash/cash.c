#include <stdio.h>
#include <cs50.h>
#include <math.h>
void HandleCash();

int tender[] = {25,10,5,1};
int coinsRequired = 0;
float userRequest;
// works for flat numbers, not decimals
int main(void)
{
    do
    {
        userRequest = get_float("Change Required: ");
    }
    while (userRequest <= 0);
    userRequest *= 100;
    eprintf("%f",userRequest);
    userRequest = lround(userRequest);
    while(userRequest > 0 )
    {
        HandleCash();
    }
    printf("%i \n",coinsRequired);
}

void HandleCash()
{
     for (int i = 0, l = sizeof(tender) / sizeof(tender[0]); i < 4; i++) // sizeof gets the length in bits which is 16 as there's 4 ints, then divide it by the size of its first element which is 4 bytes as its an int
    {
        if(tender[i] <= userRequest)
        {
            float priorCoins = userRequest;
            userRequest -= tender[i];
            coinsRequired++;
            eprintf(" Current Balance: %f. Took away %i coins remaing: %f coins used: %i \n", priorCoins,tender[i], userRequest, coinsRequired );
            HandleCash();
            break;
        }
        else
        {
           // printf("Not High Enough \n");
        }
    }
}
