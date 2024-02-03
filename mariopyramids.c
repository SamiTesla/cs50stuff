#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    // ask user for input for height
    do
    {
    height=get_int("what should the height be");
    }

//limit for user
    while
    ((height  < 1) || (height > 8));
    //length of row
        for (int row=0; row<height;row++)
        {
            for ( int width=0; width<height;width++)
            {
            if (row + width >= height - 1)
                printf("#");

            // adding spaces
                else
                printf(" ");
            }
            printf("\n");
    }

}
