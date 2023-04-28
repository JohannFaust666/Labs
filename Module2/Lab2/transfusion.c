#include <stdio.h>
#include <cs50.h>

int main()
{
    int a = 16, b = 0, c = 0;
    int R = 8; // target
    int K[3] = {16, 6, 11}; // K[0] = 8; K[1] = 3; K[2] = 5;

    int counter = 0; // counter for pouring outputs

    while (a != R && b != R && c != R) // if we found out target in A, B or C then break the loop
    {

        counter++;

        if (c == K[2]) // if C is full then fill A
        {
            while (c != 0 && a != K[0])
            {
                c--;
                a++;
            }
        }
        else if (a != K[0] && b != K[1] && c == 0) // if A, B are not full but C is empty then fill C from B
        {
            while (b != 0 && c != K[2])
            {
                b--;
                c++;
            }
        }
        else if (b == K[1]) // if B is full then fill the C
        {
            while (b != 0 && c != K[2])
            {
                b--;
                c++;
            }
        }
        else if ((a - K[1]) >= 0) // if A > (capacity - 1) then fill the B
        {
            while (a != 0 && b != K[1])
            {
                a--;
                b++;
            }
        }

        printf("Pouring %i: a = %i; b = %i; c = %i;\n", counter, a, b, c); // number of each pour
    }

    printf("a: %i\n", a); // A is ... when we hit our target
    printf("b: %i\n", b); // B is ... when we hit our target
    printf("c: %i\n", c); // C is ... when we hit our target

    return 0;
}
