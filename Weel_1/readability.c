#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // printf("%d words, %d sentences", W, S);
    // Compute the Coleman-Liau index
    float L = (float) letters * 100 / words;
    float S = (float) sentences * 100 / words;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Print the grade level
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
}

// create function that counts english letters in text
int count_letters(string text)
{
    int result = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            result += 1;
        }
    }
    return result;
}

// create function that counts words in text
int count_words(string text)
{
    int result = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == ' ')
        {
            result += 1;
        }
    }
    return result + 1;
}

// create function that counts sentences in text
int count_sentences(string text)
{
    int result = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            result += 1;
        }
    }
    return result;
}
