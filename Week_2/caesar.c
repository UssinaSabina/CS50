#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string input);

char rotate(char c, int key);

int main(int argc, string argv[])
{
    // if program is executed without any command-line arguments or with more than 1 command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // if any of the characters of the command-line argument is not a decimal digit
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // convert argv[1] (which is a key) to an integer
    int key = atoi(argv[1]);

    // prompt the user for some plaintext
    string plaintext = get_string("plaintext: ");

    // print out ciphertext
    printf("ciphertext: ");
    for (int i = 0, l = strlen(plaintext); i < l; i++)
    {
        printf("%c", rotate(plaintext[i], key));
    }
    printf("\n");
}

bool only_digits(string input)
{
    for (int i = 0, l = strlen(input); i < l; i++)
    {
        if (input[i] < 48 || input[i] > 57)
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int key)
{

    if (isupper(c))
    {
        return ('A' + (c - 'A' + key) % 26);
    }
    else if (islower(c))
    {
        return ('a' + (c - 'a' + key) % 26);
    }
    else
    {
        return c;
    }
}
