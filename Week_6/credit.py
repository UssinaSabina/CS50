from cs50 import get_int

#  Luhn's algorithm to check if the a card number is syntactically valid
def luhns_is_valid(number):
    # let’s first underline every other digit, starting with the number’s second-to-last digit
    # and multiply each of them by 2
    number_reversed = str(number)[::-1]
    second_to_last_digits = [int(i) * 2 for i in number_reversed[1::2]]
    # then sum these product's digits (not the products themselves)
    second_to_last_digits_sum = 0
    for num in second_to_last_digits:
        while num > 0:
            second_to_last_digits_sum += num % 10
            num = num // 10
    print(second_to_last_digits_sum)
    # let's add those numbers that weren't multiplied by 2
    other_digits = [int(i) for i in number_reversed[::2]]
    other_digits_sum = sum(other_digits)
    print(other_digits_sum)
    # let's add those two sums
    total = second_to_last_digits_sum + other_digits_sum
    # If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
    last_digit = total % 10
    if last_digit == 0:
        return True
    else:
        return False


# get input card number from user
number = get_int("Number: ")

# how many digits are in card number
length = len(str(number))

# flag that describes if card number is valid
is_invalid = False

# check the length of card number
if length not in [13, 15, 16]:
    is_invalid = True

# get the 1st two digits of card number
first_two_digits = int(str(number)[:2])   # 123456789 --> 12
# get the 1st digit of card number
first_digit = int(str(number)[0])          # 123456789 --> 1


if length == 15:
    if first_two_digits == 34 or first_two_digits == 37:
        card = "AMEX\n"
    else:
        is_invalid = True

if length == 13:
    if first_digit == 4:
        card = "VISA\n"
    else:
        is_invalid = True

if length == 16:
    if first_digit == 4:
        card = "VISA\n"
    elif 51 <= first_two_digits <= 55:
        card = "MASTERCARD\n"
    else:
        is_invalid = True

# last check by Luhn's algo
if luhns_is_valid(number) == False:
    is_invalid = True

if is_invalid == True:
    card = "INVALID"

print(card)



