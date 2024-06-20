# Credit
## Problem to Solve
In a filed called ```credit.py``` write a program that prompts the user for a credit card number and then reports (via ```print```) whether it is a valid American Express, MasterCard, or Visa card number, exactly as you did in [Problem Set 1](https://cs50.harvard.edu/x/2024/psets/1/). Your program this time should be written in ```Python```!

## Specification
- So that we can automate some tests of your code, we ask that your program’s last line of output be ```AMEX\n``` or ```MASTERCARD\n``` or ```VISA\n``` or ```INVALID\n```, nothing more, nothing less.
- For simplicity, you may assume that the user’s input will be entirely numeric (i.e., devoid of hyphens, as might be printed on an actual card).
- Best to use ```get_int``` or ```get_string``` from CS50’s library to get users’ input, depending on how you to decide to implement this one.

## How to Test
- Run your program as ```python credit.py```, and wait for a prompt for input. Type in ```378282246310005``` and press enter. Your program should output ```AMEX```.
- Run your program as ```python credit.py```, and wait for a prompt for input. Type in ```371449635398431``` and press enter. Your program should output ```AMEX```.
- Run your program as ```python credit.py```, and wait for a prompt for input. Type in ```5555555555554444``` and press enter. Your program should output ```MASTERCARD```.
- Run your program as ```python credit.py```, and wait for a prompt for input. Type in ```5105105105105100``` and press enter. Your program should output ```MASTERCARD```.
- Run your program as ```python credit.py```, and wait for a prompt for input. Type in ```4111111111111111``` and press enter. Your program should output ```VISA```.
- Run your program as ```python credit.py```, and wait for a prompt for input. Type in ```4012888888881881``` and press enter. Your program should output ```VISA```.
- Run your program as ```python credit.py```, and wait for a prompt for input. Type in ```1234567890``` and press enter. Your program should output ```INVALID```.
