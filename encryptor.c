#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main(int argc, string argv[1])
{

    // meant to check the arg the entire system has to take
    if (argc!=2)
    {
        printf("Usage: ./caesar k");
        return 1;
    }


        for (int key=0; key < strlen(argv[1]); key++)
        // this checks if argument 1 is alphabetical
        if (isalpha (argv [1][key]))
        {
            // prints a statement showing the intended use of arg 1
            printf("Usage: ./caesar key\n");
            return 1;

        }
        // converts the key from a string into an int
        int key= atoi(argv[1])%26;

        //asks the user for the text that needs to be encrypted
        string plaintext= get_string("plaintext:");
        printf("ciphertext: ");

    for(int i=0, length=strlen(plaintext); i<length; i++)
    {
        if(!isalpha(plaintext[i]))
        {
            printf("%c", plaintext[i]);
            continue;
        }

        //checks if its upper(thought it would be cool if it uppercased it, but it just messes with everything )
                                        //range of ascii numbers= alpha
        int offset= isupper(plaintext[i]) ? 65:97;
        int pi=plaintext[i]-offset;
        int cip=(pi+key)%26;
        //prints and just for fun also uppercases the output, but check 50 denies it
        printf("%c" , cip + offset);
    }


    printf("\n");
    return 0;

}
//overall the output is super cool and this was a ton of fun, but some parts of this were a bit hard and when i tried to do a few cool things check 50 disliked it ca
