#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
int main(void)
{
    // checks what text the user inputs
    string text = get_string("Text: ");
    //this was probably the easiest part of the assignment

    int i = strlen(text);
    int letters = 0;
    int words = 1;
    int sent = 0;

    //loop for words, letters, and sentences
    for (int x = 0; x < i; x++)
    {

        char c = text[x];
        if (isalpha(c) != 0)
        {
            letters++;
        }


        if (c == ' ')
        {
            words++;
        }


        if (c == '.' || c == '!' || c == '?')
        {
            sent++;
        }
    }


//math to apply the coleman-liau index
    float L = ((float)letters / (float)words) * 100;
    float s = ((float)sent / (float)words) * 100;
    float subindex = 0.0588 * L - 0.296 * s - 15.8;
    int index = round(subindex);
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}
//overall this assigment was hard especially reconfiguring the code
