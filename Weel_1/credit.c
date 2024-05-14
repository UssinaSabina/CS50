#include <cs50.h>
#include <stdio.h>
#include <math.h>

int count_digits(long long int number);
int first_n_digits(long long int number, int n);
bool is_valid(long long int number, int length);

int main(void)
{
    // user's input
    long long int number = get_long_long("Number: ");

    // input's length
    int length = count_digits(number);

    // first digit of the number
    int first_digit = first_n_digits(number, 1);

    // first two digits of the number
    int first_two_digits = first_n_digits(number, 2);

    // check if the length is appropriate
    if (length != 13 && length != 15 && length != 16)
    {
        printf("INVALID\n");
        return 0;
    }

    // initialize variable - the type of the card or "Invalid" (if it's neither AmericanExpress / MasterCard/ Visa)
    string card;

    // AmericanExpress
    if (length == 15)
    {
        if (first_two_digits == 34 || first_two_digits == 37)
        {
            card = "AMEX\n";
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }
    else
    {
        // VISA
        if (length == 13)
        {
            if (first_digit == 4)
            {
                card = "VISA\n";
            }
            else
            {
                printf("INVALID\n");
                return 0;
            }
        }
        else
        {
            // VISA or MasterCard
            if (length == 16)
            {
                // VISA
                if (first_digit == 4)
                {
                    card = "VISA\n";
                }
                else
                {
                    // MasterCard
                    if (first_two_digits >= 51 && first_two_digits <= 55)
                    {
                        card = "MASTERCARD\n";
                    }
                    // Invalid input
                    else
                    {
                        printf("INVALID\n");
                        return 0;
                    }
                }
            }

        }
    }

    // Luhn's algo
    if (is_valid(number, length))
    {
        printf("%s", card);
    }
    else
    {
        printf("INVALID\n");
    }
}

// create function that returns the length of the long long integer
int count_digits(long long int number)
{
    int digits = 0;
    do
    {
        ++digits;
        number /= 10;
    } while (number);
    return digits;
}

// create function that returns the first N digits of the long long integer
int first_n_digits(long long int number, int n)
{
    while (number >= pow(10, n))
    {
        number /= 10;
    }
    return number;
}

//  Luhn's algorithm to check if the a card number is syntactically valid
bool is_valid(long long int number, int length)
{
    // let’s first underline every other digit, starting with the number’s second-to-last digit, and then multiply
    // each of them by 2, and then sum these product's digits (not the products themselves)
    int multiplied_nums_sum = 0;
    long long int number_copy = number;
    number_copy /= 10;   // to start with the number's second digit
    int digit;
    int twiced_digit;
    while (number_copy > 0)
    {
        digit = number_copy % 10;
        twiced_digit = digit * 2;
        while (twiced_digit > 0)
        {
            int products_digit = twiced_digit % 10;
            twiced_digit /= 10;
            multiplied_nums_sum += products_digit;
        }
        number_copy = number_copy / 100;
    }

    // let's add those numbers that weren't multiplied by 2
    int not_multiplied_nums_sum = 0;
    number_copy = number;
    while (number_copy > 0)
    {
        digit = number_copy % 10;
        number_copy /= 100;
        not_multiplied_nums_sum += digit;
    }

    // let's add those two sums
    int total = multiplied_nums_sum + not_multiplied_nums_sum;

    // If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
    int last_digit = total % 10;
    if (last_digit == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


